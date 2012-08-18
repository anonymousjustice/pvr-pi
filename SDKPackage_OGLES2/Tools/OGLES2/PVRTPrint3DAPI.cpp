/******************************************************************************

 @File         PVRTPrint3DAPI.cpp

 @Title        OGLES2/PVRTPrint3DAPI

 @Version      

 @Copyright    Copyright (c) Imagination Technologies Limited.

 @Platform     ANSI compatible

 @Description  Displays a text string using 3D polygons. Can be done in two ways:
               using a window defined by the user or writing straight on the
               screen.

******************************************************************************/

/****************************************************************************
** Includes
****************************************************************************/
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "PVRTContext.h"
#include "PVRTFixedPoint.h"
#include "PVRTMatrix.h"
#include "PVRTTexture.h"
#include "PVRTTextureAPI.h"
#include "PVRTPrint3D.h"
#include "PVRTString.h"
#include "PVRTShader.h"
#include "PVRTMap.h"

#include "PVRTPrint3DShaders.h"

/****************************************************************************
** Defines
****************************************************************************/
#define VERTEX_ARRAY			0
#define UV_ARRAY				1
#define COLOR_ARRAY				2

#define INIT_PRINT3D_STATE		0
#define DEINIT_PRINT3D_STATE	1

#define UNDEFINED_HANDLE 0xFAFAFAFA

const GLenum c_eMagTable[] =
{
	GL_NEAREST,
	GL_LINEAR,
};

const GLenum c_eMinTable[] =
{
	GL_NEAREST_MIPMAP_NEAREST,
	GL_LINEAR_MIPMAP_NEAREST,
	GL_NEAREST_MIPMAP_LINEAR,
	GL_LINEAR_MIPMAP_LINEAR,
	GL_NEAREST,
	GL_LINEAR,
};

/****************************************************************************
** Enums
****************************************************************************/
enum eFunction
{
	eFunc_DelProg,
	eFunc_DelShader,
	eFunc_DelTex
};

/****************************************************************************
** Auxiliary functions
****************************************************************************/
void DeleteResource(eFunction eType, GLuint& handle)
{
	if(handle == UNDEFINED_HANDLE)
		return;

	switch(eType)
	{
	case eFunc_DelProg:		glDeleteProgram(handle);		break;
	case eFunc_DelShader:	glDeleteShader(handle);			break;
	case eFunc_DelTex:		glDeleteTextures(1, &handle);	break;
	}

	handle = UNDEFINED_HANDLE;
}

/****************************************************************************
** Structures
****************************************************************************/

struct SPVRTPrint3DAPI
{
	GLuint						m_uTextureFont;
	static int					s_iRefCount;

	struct SInstanceData
	{
		GLuint				uTextureIMGLogo;

		GLuint				VertexShader; 
		GLuint				FragmentShader;
		GLuint				Program;

		SInstanceData()
		{
			uTextureIMGLogo = VertexShader = FragmentShader = Program = UNDEFINED_HANDLE;
		}
		
		void Release()
		{
			DeleteResource(eFunc_DelProg, Program);
			DeleteResource(eFunc_DelShader, FragmentShader);
			DeleteResource(eFunc_DelShader, VertexShader);
			DeleteResource(eFunc_DelTex, uTextureIMGLogo);
		}
	};

	// Optional per-instance data
	SInstanceData*				m_pInstanceData;

	// Shared data across all Print3D instances
	static SInstanceData		s_InstanceData;

/* Used to save the OpenGL state to restore them after drawing */
	GLboolean					isCullFaceEnabled;
	GLboolean					isBlendEnabled;
	GLboolean					isDepthTestEnabled;
	GLint						nArrayBufferBinding;
	GLint						eFrontFace;
	GLint						eCullFaceMode;

	SPVRTPrint3DAPI() : m_pInstanceData(NULL) {}
	~SPVRTPrint3DAPI()
	{
		if(m_pInstanceData)
		{
			delete m_pInstanceData;
			m_pInstanceData = NULL;
		}
	}
};

int SPVRTPrint3DAPI::s_iRefCount								= 0;
SPVRTPrint3DAPI::SInstanceData SPVRTPrint3DAPI::s_InstanceData;

/****************************************************************************
** Class: CPVRTPrint3D
****************************************************************************/

/*!***************************************************************************
 @Function			ReleaseTextures
 @Description		Deallocate the memory allocated in SetTextures(...)
*****************************************************************************/
void CPVRTPrint3D::ReleaseTextures()
{
#if !defined (DISABLE_PRINT3D)

	if(m_pAPI)
	{
		// Has local copy
		if(m_pAPI->m_pInstanceData)
		{
			m_pAPI->m_pInstanceData->Release();
		}
		else
		{
			if(SPVRTPrint3DAPI::s_iRefCount != 0)
			{
				// Just decrease the reference count
				SPVRTPrint3DAPI::s_iRefCount--;
			}
			else
			{
				m_pAPI->s_InstanceData.Release();
			}
		}
	}	
	
	/* Only release textures if they've been allocated */
	if (!m_bTexturesSet) return;

	/* Release IndexBuffer */
	FREE(m_pwFacesFont);
	FREE(m_pPrint3dVtx);

	/* Delete textures */
	glDeleteTextures(1, &m_pAPI->m_uTextureFont);
	
	m_bTexturesSet = false;

	FREE(m_pVtxCache);

	APIRelease();

#endif
}

/*!***************************************************************************
 @Function			Flush
 @Description		Flushes all the print text commands
*****************************************************************************/
int CPVRTPrint3D::Flush()
{
#if !defined (DISABLE_PRINT3D)

	int		nTris, nVtx, nVtxBase, nTrisTot;

	_ASSERT((m_nVtxCache % 4) == 0);
	_ASSERT(m_nVtxCache <= m_nVtxCacheMax);

	/* Save render states */
	APIRenderStates(INIT_PRINT3D_STATE);

	/* Set font texture */
	glBindTexture(GL_TEXTURE_2D, m_pAPI->m_uTextureFont);

	unsigned int uiIndex = m_eFilterMethod[eFilterProc_Min] + (m_eFilterMethod[eFilterProc_Mip]*2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, c_eMagTable[m_eFilterMethod[eFilterProc_Mag]]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, c_eMinTable[uiIndex]);
	
	nTrisTot = m_nVtxCache >> 1;

	/*
		Render the text then. Might need several submissions.
	*/
	nVtxBase = 0;
	while(m_nVtxCache)
	{
		nVtx	= PVRT_MIN(m_nVtxCache, 0xFFFC);
		nTris	= nVtx >> 1;

		_ASSERT(nTris <= (PVRTPRINT3D_MAX_RENDERABLE_LETTERS*2));
		_ASSERT((nVtx % 4) == 0);

		/* Draw triangles */
		glVertexAttribPointer(VERTEX_ARRAY, 3, GL_FLOAT, GL_FALSE, sizeof(SPVRTPrint3DAPIVertex), (const void*)&m_pVtxCache[nVtxBase].sx);
		glVertexAttribPointer(COLOR_ARRAY, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(SPVRTPrint3DAPIVertex), (const void*)&m_pVtxCache[nVtxBase].color);
		glVertexAttribPointer(UV_ARRAY, 2, GL_FLOAT, GL_FALSE, sizeof(SPVRTPrint3DAPIVertex), (const void*)&m_pVtxCache[nVtxBase].tu);
		glDrawElements(GL_TRIANGLES, nTris * 3, GL_UNSIGNED_SHORT, m_pwFacesFont);
		if (glGetError())
		{
			_RPT0(_CRT_WARN,"glDrawElements(GL_TRIANGLES, (VertexCount/2)*3, GL_UNSIGNED_SHORT, m_pFacesFont); failed\n");
		}

		nVtxBase		+= nVtx;
		m_nVtxCache	-= nVtx;
	}

	/* Draw a logo if requested */
#if defined(FORCE_NO_LOGO)
	/* Do nothing */

#elif defined(FORCE_IMG_LOGO)
	APIDrawLogo(ePVRTPrint3DLogoIMG, 1);	/* IMG to the right */

#elif defined(FORCE_ALL_LOGOS)
	APIDrawLogo(ePVRTPrint3DLogoIMG, -1); /* IMG to the left */

#else
	/* User selected logos */
	switch (m_uLogoToDisplay)
	{
		case ePVRTPrint3DLogoNone:
			break;
		default:
		case ePVRTPrint3DLogoIMG:
			APIDrawLogo(ePVRTPrint3DLogoIMG, 1);	/* IMG to the right */
			break;
	}
#endif

	/* Restore render states */
	APIRenderStates(DEINIT_PRINT3D_STATE);

	return nTrisTot;

#else
	return 0;
#endif
}

/*************************************************************
*					 PRIVATE FUNCTIONS						 *
**************************************************************/

/*!***************************************************************************
 @Function			APIInit
 @Description		Initialisation and texture upload. Should be called only once
					for a given context.
*****************************************************************************/
bool CPVRTPrint3D::APIInit(const SPVRTContext	* const pContext, bool bMakeCopy)
{
	PVRT_UNREFERENCED_PARAMETER(pContext);

	m_pAPI = new SPVRTPrint3DAPI;
	if(!m_pAPI)
		return false;

	if(bMakeCopy)
		m_pAPI->m_pInstanceData = new SPVRTPrint3DAPI::SInstanceData();

	SPVRTPrint3DAPI::SInstanceData& Data = (m_pAPI->m_pInstanceData ? *m_pAPI->m_pInstanceData : SPVRTPrint3DAPI::s_InstanceData);

	// Check to see if these shaders have already been loaded previously. Optimisation as we don't want to load many of the same shader!
	if(	Data.FragmentShader != UNDEFINED_HANDLE && Data.VertexShader != UNDEFINED_HANDLE && Data.Program != UNDEFINED_HANDLE)
	{
		SPVRTPrint3DAPI::s_iRefCount++;
		return true;
	}

	/* Compiles the shaders. For a more detailed explanation, see IntroducingPVRTools */
	CPVRTString error;
	GLint Linked;
	bool bRes = true;

	bRes &= (PVRTShaderLoadSourceFromMemory(_Print3DFragShader_fsh, GL_FRAGMENT_SHADER, &Data.FragmentShader, &error) == PVR_SUCCESS);
	bRes &= (PVRTShaderLoadSourceFromMemory(_Print3DVertShader_vsh, GL_VERTEX_SHADER, &Data.VertexShader, &error)  == PVR_SUCCESS);

	_ASSERT(bRes);

	// Create the 'text' program
    Data.Program = glCreateProgram();
    glAttachShader(Data.Program, Data.VertexShader);
    glAttachShader(Data.Program, Data.FragmentShader);
    glBindAttribLocation(Data.Program, VERTEX_ARRAY, "myVertex");
    glBindAttribLocation(Data.Program, UV_ARRAY, "myUV");
    glBindAttribLocation(Data.Program, COLOR_ARRAY, "myColour");

	glLinkProgram(Data.Program);
	glGetProgramiv(Data.Program, GL_LINK_STATUS, &Linked);

	if (!Linked)
		bRes = false;

	_ASSERT(bRes);

	return true;
}

/*!***************************************************************************
 @Function			APIRelease
 @Description		Deinitialization.
*****************************************************************************/
void CPVRTPrint3D::APIRelease()
{
	delete m_pAPI;
	m_pAPI = 0;
}

/*!***************************************************************************
 @Function			APIUpLoadIcons
 @Description		Initialisation and texture upload. Should be called only once
					for a given context.
*****************************************************************************/
bool CPVRTPrint3D::APIUpLoadIcons(const PVRTuint8 * const pIMG)
{
	SPVRTPrint3DAPI::SInstanceData& Data = (m_pAPI->m_pInstanceData ? *m_pAPI->m_pInstanceData : SPVRTPrint3DAPI::s_InstanceData);

	/* Load Icon texture */
	if(Data.uTextureIMGLogo == UNDEFINED_HANDLE)		// Static, so might already be initialized.
		if(PVRTTextureLoadFromPointer((unsigned char*)pIMG, &Data.uTextureIMGLogo) != PVR_SUCCESS)
			return false;

	return true;
}

/*!***************************************************************************
@Function		APIUpLoadTexture
@Input			pSource
@Output			header
@Return			bool	true if successful.
@Description	Loads and uploads the font texture from a PVR file.
*****************************************************************************/
bool CPVRTPrint3D::APIUpLoadTexture( const PVRTuint8* pSource, const PVRTextureHeaderV3* header, CPVRTMap<PVRTuint32, CPVRTMap<PVRTuint32, MetaDataBlock> >& MetaDataMap)
{
	if(PVRTTextureLoadFromPointer(pSource, &m_pAPI->m_uTextureFont, header, true, 0U, NULL, &MetaDataMap) != PVR_SUCCESS)
		return false;

	/* Return status : OK */
	return true;
}

/*!***************************************************************************
 @Function			APIRenderStates
 @Description		Stores, writes and restores Render States
*****************************************************************************/
void CPVRTPrint3D::APIRenderStates(int nAction)
{
	SPVRTPrint3DAPI::SInstanceData& Data = (m_pAPI->m_pInstanceData ? *m_pAPI->m_pInstanceData : SPVRTPrint3DAPI::s_InstanceData);

	/* Saving or restoring states ? */
	switch (nAction)
	{
	case INIT_PRINT3D_STATE:
	{
		/* Get previous render states */
		m_pAPI->isCullFaceEnabled = glIsEnabled(GL_CULL_FACE);
		m_pAPI->isBlendEnabled = glIsEnabled(GL_BLEND);
		m_pAPI->isDepthTestEnabled = glIsEnabled(GL_DEPTH_TEST);
		glGetIntegerv(GL_FRONT_FACE, &m_pAPI->eFrontFace); 
		glGetIntegerv(GL_CULL_FACE_MODE, &m_pAPI->eCullFaceMode); 
		glGetIntegerv(GL_ARRAY_BUFFER_BINDING,&m_pAPI->nArrayBufferBinding);

		/******************************
		** SET PRINT3D RENDER STATES **
		******************************/

		/* Set the default GL_ARRAY_BUFFER */
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		float fW = m_fScreenScale[0]*640.0f;
		float fH = m_fScreenScale[1]*480.0f;
        
		PVRTMat4 mxOrtho = PVRTMat4::Ortho(0.0f, 0.0f, fW, -fH, -1.0f, 1.0f, PVRTMat4::OGL, m_bRotate);
		if(m_bRotate)
		{
			PVRTMat4 mxTrans = PVRTMat4::Translation(-fH,fW,0.0f);
			mxOrtho = mxOrtho * mxTrans;
		}

		/* Use the shader */
		_ASSERT(Data.Program != UNDEFINED_HANDLE);
		glUseProgram(Data.Program);

		/* Bind the projection and modelview matrices to the shader */
		int location = glGetUniformLocation(Data.Program, "myMVPMatrix");
		
		PVRTMat4& mProj = (m_bUsingProjection ? m_mProj : mxOrtho);	
		PVRTMat4 mMVP = mProj * m_mModelView;
		glUniformMatrix4fv( location, 1, GL_FALSE, mMVP.f);

		// Reset
		m_bUsingProjection = false;
		PVRTMatrixIdentity(m_mModelView);
			
		/* Culling */
		glFrontFace(GL_CCW);
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);

		/* Set blending mode */
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		/* Set Z compare properties */
		glDisable(GL_DEPTH_TEST);

		/* Set client states */
		glEnableVertexAttribArray(VERTEX_ARRAY);
		glEnableVertexAttribArray(COLOR_ARRAY);
		glEnableVertexAttribArray(UV_ARRAY);

		/* texture 	*/
		glActiveTexture(GL_TEXTURE1);
		glActiveTexture(GL_TEXTURE0);
		break;
	}
	case DEINIT_PRINT3D_STATE:
		/* Restore render states */
		glDisableVertexAttribArray(VERTEX_ARRAY);
		glDisableVertexAttribArray(COLOR_ARRAY);
		glDisableVertexAttribArray(UV_ARRAY);

		/* Restore some values */
		if (!m_pAPI->isCullFaceEnabled) glDisable(GL_CULL_FACE);
		if (!m_pAPI->isBlendEnabled) glDisable(GL_BLEND);
		if (m_pAPI->isDepthTestEnabled) glEnable(GL_DEPTH_TEST);
		glCullFace((GLenum)m_pAPI->eCullFaceMode);
		glFrontFace((GLenum)m_pAPI->eFrontFace);
		glBindBuffer(GL_ARRAY_BUFFER,m_pAPI->nArrayBufferBinding);

		break;
	}
}

/****************************************************************************
** Local code
****************************************************************************/

/*!***************************************************************************
 @Function			APIDrawLogo
 @Description		nPos = -1 to the left
					nPos = +1 to the right
*****************************************************************************/
#define LOGO_SIZE 0.3f
#define LOGO_SHIFT 0.05f

void CPVRTPrint3D::APIDrawLogo(unsigned int uLogoToDisplay, int nPos)
{
	//If the logo isn't valid, return.
	if (uLogoToDisplay == ePVRTPrint3DLogoNone)
		return;

	SPVRTPrint3DAPI::SInstanceData& Data = (m_pAPI->m_pInstanceData ? *m_pAPI->m_pInstanceData : SPVRTPrint3DAPI::s_InstanceData);
	const float fLogoSizeHalf = 0.15f;
	const float fLogoShift = 0.05f;
	const float fLogoSizeHalfShifted = fLogoSizeHalf + fLogoShift;
	const float fLogoYScale = 45.0f/64.0f;

	static VERTTYPE	Vertices[] =
		{
			-fLogoSizeHalf, fLogoSizeHalf , 0.5f,
			-fLogoSizeHalf, -fLogoSizeHalf, 0.5f,
			fLogoSizeHalf , fLogoSizeHalf , 0.5f,
	 		fLogoSizeHalf , -fLogoSizeHalf, 0.5f
		};

	static float	Colours[] = {
			(1.0f), (1.0f), (1.0f), (0.75f),
			(1.0f), (1.0f), (1.0f), (0.75f),
			(1.0f), (1.0f), (1.0f), (0.75f),
	 		(1.0f), (1.0f), (1.0f), (0.75f)
		};

	static float	UVs[] = {
			(0.0f), (0.0f),
			(0.0f), (1.0f),
			(1.0f), (0.0f),
	 		(1.0f), (1.0f)
		};

	float *pVertices = ( (float*)&Vertices );
	float *pColours  = ( (float*)&Colours );
	float *pUV       = ( (float*)&UVs );

	GLuint	tex = Data.uTextureIMGLogo;

	// Matrices
	PVRTMATRIX matModelView;
	PVRTMATRIX matTransform;
	PVRTMatrixIdentity(matModelView);

	float fScreenScale = PVRT_MIN(m_ui32ScreenDim[0], m_ui32ScreenDim[1]) / 480.0f;
	float fScaleX = (640.0f / m_ui32ScreenDim[0]) * fScreenScale;
	float fScaleY = (480.0f / m_ui32ScreenDim[1]) * fScreenScale * fLogoYScale;

	PVRTMatrixScaling(matTransform, f2vt(fScaleX), f2vt(fScaleY), f2vt(1.0f));
	PVRTMatrixMultiply(matModelView, matModelView, matTransform);

	PVRTMatrixTranslation(matTransform, nPos - (fLogoSizeHalfShifted * fScaleX * nPos), -1.0f + (fLogoSizeHalfShifted * fScaleY), 0.0f);
	PVRTMatrixMultiply(matModelView, matModelView, matTransform);

	if(m_bRotate)
	{
		PVRTMatrixRotationZ(matTransform, -90.0f*PVRT_PI/180.0f);
		PVRTMatrixMultiply(matModelView, matModelView, matTransform);
	}

	_ASSERT(Data.Program != UNDEFINED_HANDLE);
	glUseProgram(Data.Program);

	// Bind the projection and modelview matrices to the shader
	int location = glGetUniformLocation(Data.Program, "myMVPMatrix");
	glUniformMatrix4fv( location, 1, GL_FALSE, matModelView.f);

	// Render states
	glActiveTexture(GL_TEXTURE0);

	_ASSERT(tex != UNDEFINED_HANDLE);
	glBindTexture(GL_TEXTURE_2D, tex);

	// Vertices
	glEnableVertexAttribArray(VERTEX_ARRAY);
	glEnableVertexAttribArray(UV_ARRAY);
	glEnableVertexAttribArray(COLOR_ARRAY);
	glVertexAttribPointer(VERTEX_ARRAY, 3, GL_FLOAT, GL_FALSE, 0, (const void*)pVertices);
	glVertexAttribPointer(UV_ARRAY, 2, GL_FLOAT, GL_FALSE, 0, (const void*)pUV);
	glVertexAttribPointer(COLOR_ARRAY, 4, GL_FLOAT, GL_FALSE, 0, (const void*)pColours);

	glDrawArrays(GL_TRIANGLE_STRIP,0,4);

	glDisableVertexAttribArray(VERTEX_ARRAY);
	glDisableVertexAttribArray(UV_ARRAY);
	glDisableVertexAttribArray(COLOR_ARRAY);
}

/*****************************************************************************
 End of file (PVRTPrint3DAPI.cpp)
*****************************************************************************/

