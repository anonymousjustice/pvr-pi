/******************************************************************************

 @File         PVRTPFXParserAPI.cpp

 @Title        PVRTPFXParserAPI

 @Version      

 @Copyright    Copyright (c) Imagination Technologies Limited.

 @Platform     ANSI compatible

 @Description  PFX file parser.

******************************************************************************/

/*****************************************************************************
** Includes
*****************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "PVRTContext.h"
#include "PVRTMatrix.h"
#include "PVRTFixedPoint.h"
#include "PVRTString.h"
#include "PVRTShader.h"
#include "PVRTPFXParser.h"
#include "PVRTPFXParserAPI.h"
#include "PVRTTexture.h"

/*!***************************************************************************
 @Function			CPVRTPFXEffect Constructor
 @Description		Sets the context and initialises the member variables to zero.
*****************************************************************************/
CPVRTPFXEffect::CPVRTPFXEffect():
	m_psContext(NULL), m_pParser(NULL), m_nEffect(0), m_uiProgram(0), m_pnTextureIdx(NULL), m_psTextures(NULL)
{}

/*!***************************************************************************
 @Function			CPVRTPFXEffect Constructor
 @Description		Sets the context and initialises the member variables to zero.
*****************************************************************************/
CPVRTPFXEffect::CPVRTPFXEffect(SPVRTContext &sContext):
	m_psContext(&sContext), m_pParser(NULL), m_nEffect(0), m_uiProgram(0), m_pnTextureIdx(NULL), m_psTextures(NULL)
{}

/*!***************************************************************************
 @Function			CPVRTPFXEffect Destructor
 @Description		Calls Destroy().
*****************************************************************************/
CPVRTPFXEffect::~CPVRTPFXEffect()
{
	Destroy();
}

/*!***************************************************************************
 @Function			Load
 @Input				src					PFX Parser Object
 @Input				pszEffect			Effect name
 @Input				pszFileName			Effect file name
 @Output			pReturnError		Error string
 @Returns			EPVRTError			PVR_SUCCESS if load succeeded
 @Description		Loads the specified effect from the CPVRTPFXParser object.
					Compiles and links the shaders. Initialises texture data.
*****************************************************************************/
EPVRTError CPVRTPFXEffect::Load(CPVRTPFXParser &src, const char * const pszEffect, const char * const pszFileName, CPVRTString *pReturnError)
{
	GLuint	uiVertexShader = 0, uiFragShader = 0;
	unsigned int	uiVertIdx, uiFragIdx;
	unsigned int	 i, j;

	if(!src.GetNumberEffects())
		return PVR_FAIL;

	/*
		First find the named effect from the effect file
	*/
	if(pszEffect)
	{
		for(i = 0; i < src.GetNumberEffects(); ++i)
		{
			if(strcmp(src.GetEffect(i).pszName, pszEffect) == 0)
			{
				m_nEffect = i;
				break;
			}
		}
		if(i == src.GetNumberEffects())
		{
			return PVR_FAIL;
		}
	}
	else
	{
		m_nEffect = 0;
	}

	/*
		Now load the effect
	*/
	m_pParser = &src;
	const SPVRTPFXParserEffect &ParserEffect = src.GetEffect(m_nEffect);

	// Create room for per-texture data
	m_psTextures = new SPVRTPFXTexture[src.GetNumberTextures()];

	// Initialise each Texture
	for(i = 0; i < src.GetNumberTextures(); ++i)
	{
		m_psTextures[i].p	= src.GetTexture(i)->FileName.c_str();
		m_psTextures[i].ui	= 0xFFFFFFFF;
	}

	// Initialise the effect
	{
		// initialise attributes to default values
		char *pszVertexShader = NULL;
		char *pszFragmentShader = NULL;
		bool bFreeVertexShader = false;
		bool bFreeFragmentShader = false;

		// find shaders requested
		for(uiVertIdx = 0; uiVertIdx < src.GetNumberVertexShaders(); ++uiVertIdx)
		{
			const SPVRTPFXParserShader& VertexShader = src.GetVertexShader(uiVertIdx);
			if(strcmp(ParserEffect.pszVertexShaderName, VertexShader.pszName) == 0)
			{
                if(VertexShader.bUseFileName)
				{
					pszVertexShader = VertexShader.pszGLSLcode;
				}
				else
				{
					if(!VertexShader.pszGLSLcode)
						continue;			// No code specified.

					// offset glsl code by nFirstLineNumber
					pszVertexShader = (char *)malloc((strlen(VertexShader.pszGLSLcode) + (VertexShader.nFirstLineNumber) + 1) * sizeof(char));
					pszVertexShader[0] = '\0';
					for(unsigned int n = 0; n < VertexShader.nFirstLineNumber; n++)
						strcat(pszVertexShader, "\n");
					strcat(pszVertexShader, VertexShader.pszGLSLcode);

					bFreeVertexShader = true;
				}

				break;
			}
		}
		for(uiFragIdx = 0; uiFragIdx < src.GetNumberFragmentShaders(); ++uiFragIdx)
		{
			const SPVRTPFXParserShader& FragmentShader = src.GetFragmentShader(uiFragIdx);
			if(strcmp(ParserEffect.pszFragmentShaderName, FragmentShader.pszName) == 0)
			{
				if(FragmentShader.bUseFileName)
				{
					pszFragmentShader = FragmentShader.pszGLSLcode;
				}
				else
				{
					if(!FragmentShader.pszGLSLcode)
						continue;			// No code specified.

					// offset glsl code by nFirstLineNumber
					pszFragmentShader = (char *)malloc((strlen(FragmentShader.pszGLSLcode) + (FragmentShader.nFirstLineNumber) + 1) * sizeof(char));
					pszFragmentShader[0] = '\0';
					for(unsigned int n = 0; n < FragmentShader.nFirstLineNumber; n++)
						strcat(pszFragmentShader, "\n");
					strcat(pszFragmentShader, FragmentShader.pszGLSLcode);

					bFreeFragmentShader = true;
				}

				break;
			}
		}

		CPVRTString error;
		bool		bLoadSource = 1;

		// Try first to load from the binary block
		if (src.GetVertexShader(uiVertIdx).pbGLSLBinary!=NULL)
		{
#if defined(GL_SGX_BINARY_IMG)
			if (PVRTShaderLoadBinaryFromMemory(src.GetVertexShader(uiVertIdx).pbGLSLBinary, src.GetVertexShader(uiVertIdx).nGLSLBinarySize,
												GL_VERTEX_SHADER, GL_SGX_BINARY_IMG, &uiVertexShader, &error) == PVR_SUCCESS)
			{
				// success loading the binary block so we do not need to load the source
				bLoadSource = 0;
			}
			else
#endif
			{
				bLoadSource = 1;
			}
		}

		// If it fails, load from source
		if (bLoadSource)
		{
			if(pszVertexShader)
			{
				if (PVRTShaderLoadSourceFromMemory(pszVertexShader, GL_VERTEX_SHADER, &uiVertexShader, &error) != PVR_SUCCESS)
				{
					*pReturnError = CPVRTString("Vertex Shader compile error in file '") + pszFileName + "':\n" + error;
					if(bFreeVertexShader)	FREE(pszVertexShader);
					if(bFreeFragmentShader)	FREE(pszFragmentShader);
					return PVR_FAIL;
				}
			}
			else // Shader not found or failed binary block
			{
				if (src.GetVertexShader(uiVertIdx).pbGLSLBinary==NULL)
				{
					*pReturnError = CPVRTString("Vertex shader ") + ParserEffect.pszVertexShaderName + "  not found in " + pszFileName + ".\n";
				}
				else
				{
					*pReturnError = CPVRTString("Binary vertex shader ") + ParserEffect.pszVertexShaderName + " not supported.\n";
				}

				if(bFreeVertexShader)	FREE(pszVertexShader);
				if(bFreeFragmentShader)	FREE(pszFragmentShader);
				return PVR_FAIL;
			}
		}

		// Try first to load from the binary block
		if (src.GetFragmentShader(uiFragIdx).pbGLSLBinary!=NULL)
		{
#if defined(GL_SGX_BINARY_IMG)
			if (PVRTShaderLoadBinaryFromMemory(src.GetFragmentShader(uiFragIdx).pbGLSLBinary, src.GetFragmentShader(uiFragIdx).nGLSLBinarySize,
													GL_FRAGMENT_SHADER, GL_SGX_BINARY_IMG, &uiFragShader, &error) == PVR_SUCCESS)
			{
				// success loading the binary block so we do not need to load the source
				bLoadSource = 0;
			}
			else
#endif
			{
				bLoadSource = 1;
			}
		}

		// If it fails, load from source
		if (bLoadSource)
		{
			if(pszFragmentShader)
			{
				if (PVRTShaderLoadSourceFromMemory(pszFragmentShader, GL_FRAGMENT_SHADER, &uiFragShader, &error) != PVR_SUCCESS)
				{
					*pReturnError = CPVRTString("Fragment Shader compile error in file '") + pszFileName + "':\n" + error;
					if(bFreeVertexShader)	FREE(pszVertexShader);
					if(bFreeFragmentShader)	FREE(pszFragmentShader);
					return PVR_FAIL;
				}
			}
			else // Shader not found or failed binary block
			{
				if (src.GetFragmentShader(uiFragIdx).pbGLSLBinary==NULL)
				{
					*pReturnError = CPVRTString("Fragment shader ") + ParserEffect.pszFragmentShaderName + "  not found in " + pszFileName + ".\n";
				}
				else
				{
					*pReturnError = CPVRTString("Binary Fragment shader ") + ParserEffect.pszFragmentShaderName + " not supported.\n";
				}

				if(bFreeVertexShader)
					FREE(pszVertexShader);
				if(bFreeFragmentShader)
					FREE(pszFragmentShader);

				return PVR_FAIL;
			}
		}

		if(bFreeVertexShader)
			FREE(pszVertexShader);

		if(bFreeFragmentShader)
			FREE(pszFragmentShader);

		// Create the shader program
		m_uiProgram = glCreateProgram();


		// Attach the fragment and vertex shaders to it
		glAttachShader(m_uiProgram, uiFragShader);
		glAttachShader(m_uiProgram, uiVertexShader);

		glDeleteShader(uiVertexShader);
		glDeleteShader(uiFragShader);

		// Bind vertex attributes
		for(i = 0; i < ParserEffect.nNumAttributes; ++i)
		{
			glBindAttribLocation(m_uiProgram, i, ParserEffect.psAttribute[i].pszName);
		}

		//	Link the program.
		glLinkProgram(m_uiProgram);
		GLint Linked;
		glGetProgramiv(m_uiProgram, GL_LINK_STATUS, &Linked);
		if (!Linked)
		{
			int i32InfoLogLength, i32CharsWritten;
			glGetProgramiv(m_uiProgram, GL_INFO_LOG_LENGTH, &i32InfoLogLength);
			char* pszInfoLog = new char[i32InfoLogLength];
			glGetProgramInfoLog(m_uiProgram, i32InfoLogLength, &i32CharsWritten, pszInfoLog);
			*pReturnError = CPVRTString("Error Linking shaders in file '") + pszFileName + "':\n\n"
							+ CPVRTString("Failed to link: ") + pszInfoLog + "\n";
			delete [] pszInfoLog;
			return PVR_FAIL;
		}

		/*
			Textures
		*/
		m_pnTextureIdx = new unsigned int[ParserEffect.nNumTextures];
		for(i = 0; i < ParserEffect.nNumTextures; ++i)
		{
			for(j = 0; j < src.GetNumberTextures(); ++j)
			{
				if(src.GetTexture(j)->Name == ParserEffect.psTextures[i].Name)
				{
					m_pnTextureIdx[i] = j;
					break;
				}
			}
			if(j == src.GetNumberTextures())
			{
				*pReturnError =  PVRTStringFromFormattedStr("Effect \"%s\" requested non-existent texture: \"%s\"\n", ParserEffect.pszName, ParserEffect.psTextures[i].Name.c_str());
				m_pnTextureIdx[i] = 0;
			}
		}
	}

	return PVR_SUCCESS;
}

/*!***************************************************************************
 @Function			Destroy
 @Description		Deletes the gl program object and texture data.
*****************************************************************************/
void CPVRTPFXEffect::Destroy()
{
	{
		if(m_uiProgram != 0)
		{
			glDeleteProgram(m_uiProgram);
			m_uiProgram = 0;
		}

		delete [] m_pnTextureIdx;
		m_pnTextureIdx = 0;
	}

	delete [] m_psTextures;
	m_psTextures = 0;
}

/*!***************************************************************************
 @Function			Activate
 @Returns			PVR_SUCCESS if activate succeeded
 @Description		Selects the gl program object and binds the textures.
*****************************************************************************/
EPVRTError CPVRTPFXEffect::Activate(const int i32RenderTextureId, const unsigned int ui32ReplacementTexture)
{
	unsigned int i;
	GLuint uiTextureId, uiTextureUnit;
	GLenum eTarget;
	const SPVRTPFXParserEffect& ParserEffect = m_pParser->GetEffect(m_nEffect);

	// Set the program
	glUseProgram(m_uiProgram);

	// Set the textures
	for(i = 0; i < ParserEffect.nNumTextures; ++i)
	{
		uiTextureId   = ParserEffect.psTextures[i].uTextureHandle;
		uiTextureUnit = ParserEffect.psTextures[i].nNumber;

		if(i32RenderTextureId != -1 && (uiTextureId == (unsigned int)i32RenderTextureId))
			uiTextureId = ui32ReplacementTexture;

		// Set active texture unit.
		glActiveTexture(GL_TEXTURE0 + uiTextureUnit);

		// Bind texture
		eTarget = (ParserEffect.psTextures[i].u32Type & PVRTEX_CUBEMAP ? GL_TEXTURE_CUBE_MAP : GL_TEXTURE_2D);
		glBindTexture(eTarget, uiTextureId);
	}

	return PVR_SUCCESS;
}

/*!***************************************************************************
 @Function			GetSemantics
 @Output			psUniforms				pointer to application uniform data array
 @Output			pnUnknownUniformCount	unknown uniform count
 @Input				psParams				pointer to semantic data array
 @Input				nParamCount				number of samantic items
 @Input				psUniformSemantics		pointer to uniform semantics array
 @Input				nUniformSemantics		number of uniform semantic items
 @Input				pglesExt				opengl extensions object
 @Input				uiProgram				program object index
 @Input				bIsAttribue				true if getting attribute semantics
 @Output			errorMsg				error string
 @Returns			unsigned int			number of successful semantics
 @Description		Get the data array for the semantics.
*****************************************************************************/
static unsigned int GetSemantics(
	SPVRTPFXUniform					* const psUniforms,
	unsigned int					* const pnUnknownUniformCount,
	const SPVRTPFXParserSemantic	* const psParams,
	const unsigned int				nParamCount,
	const SPVRTPFXUniformSemantic	* const psUniformSemantics,
	const unsigned int				nUniformSemantics,
	const GLuint					uiProgram,
	bool							bIsAttribue,
	CPVRTString						* const errorMsg)
{
	unsigned int	i, j, nCount, nCountUnused;
	int				nLocation;

	/*
		Loop over the parameters searching for their semantics. If
		found/recognised, it should be placed in the output array.
	*/
	nCount = 0;
	nCountUnused = 0;

	for(j = 0; j < nParamCount; ++j)
	{
		for(i = 0; i < nUniformSemantics; ++i)
		{
			if(strcmp(psParams[j].pszValue, psUniformSemantics[i].p) != 0)
			{
				continue;
			}

			// Semantic found for this parameter
			if(bIsAttribue)
			{
				nLocation = glGetAttribLocation(uiProgram, psParams[j].pszName);
			}
			else
			{
				nLocation = glGetUniformLocation(uiProgram, psParams[j].pszName);
			}

			if(nLocation != -1)
			{
				if(psUniforms)
				{
					psUniforms[nCount].nSemantic	= psUniformSemantics[i].n;
					psUniforms[nCount].nLocation	= nLocation;
					psUniforms[nCount].nIdx			= psParams[j].nIdx;
				}
				++nCount;
			}
			else
			{
				*errorMsg += "WARNING: Variable not used by GLSL code: ";
				*errorMsg += CPVRTString(psParams[j].pszName) + " ";
				*errorMsg += CPVRTString(psParams[j].pszValue) + "\n";
				++nCountUnused;
			}

			// Skip to the next parameter
			break;
		}
		if(i == nUniformSemantics)
		{
			*errorMsg += "WARNING: Semantic unknown to application: ";
			*errorMsg += CPVRTString(psParams[j].pszName) + " ";
			*errorMsg += CPVRTString(psParams[j].pszValue) + "\n";
		}
	}

	*pnUnknownUniformCount	= nParamCount - nCount - nCountUnused;
	return nCount;
}

/*!***************************************************************************
 @Function			BuildUniformTable
 @Output			ppsUniforms					pointer to uniform data array
 @Output			pnUniformCount				pointer to number of uniforms
 @Output			pnUnknownUniformCount		pointer to number of unknown uniforms
 @Input				psUniformSemantics			pointer to uniform semantic data array
 @Input				nSemantics					number of uniform semantics
 @Output			pReturnError				error string
 @Returns			EPVRTError					PVR_SUCCESS if succeeded
 @Description		Builds the uniform table from the semantics.
*****************************************************************************/
EPVRTError CPVRTPFXEffect::BuildUniformTable(
	SPVRTPFXUniform					** const ppsUniforms,
	unsigned int					* const pnUniformCount,
	unsigned int					* const pnUnknownUniformCount,
	const SPVRTPFXUniformSemantic	* const psUniformSemantics,
	const unsigned int				nSemantics,
	CPVRTString							*pReturnError)
{
	unsigned int			nCount, nUnknownCount;
	SPVRTPFXUniform			*psUniforms;
	const SPVRTPFXParserEffect&	ParserEffect = m_pParser->GetEffect(m_nEffect);

	nCount = 0;
	nCount += GetSemantics(NULL, &nUnknownCount, ParserEffect.psUniform, ParserEffect.nNumUniforms, psUniformSemantics, nSemantics, m_uiProgram, false, pReturnError);
	nCount += GetSemantics(NULL, &nUnknownCount, ParserEffect.psAttribute, ParserEffect.nNumAttributes, psUniformSemantics, nSemantics, m_uiProgram, true, pReturnError);

	psUniforms = (SPVRTPFXUniform*)malloc(nCount * sizeof(*psUniforms));
	if(!psUniforms)
		return PVR_FAIL;

	*pReturnError = "";

	nCount = 0;
	nCount += GetSemantics(&psUniforms[nCount], &nUnknownCount, ParserEffect.psUniform, ParserEffect.nNumUniforms, psUniformSemantics, nSemantics, m_uiProgram, false, pReturnError);
	*pnUnknownUniformCount	= nUnknownCount;

	nCount += GetSemantics(&psUniforms[nCount], &nUnknownCount, ParserEffect.psAttribute, ParserEffect.nNumAttributes, psUniformSemantics, nSemantics, m_uiProgram, true, pReturnError);
	*pnUnknownUniformCount	+= nUnknownCount;

	*ppsUniforms			= psUniforms;
	*pnUniformCount			= nCount;
	return PVR_SUCCESS;
}

/*!***************************************************************************
 @Function			GetTextureArray
 @Output			nCount					number of textures
 @Returns			SPVRTPFXTexture*		pointer to the texture data array
 @Description		Gets the texture data array.
*****************************************************************************/
const SPVRTPFXTexture *CPVRTPFXEffect::GetTextureArray(unsigned int &nCount) const
{
	nCount = m_pParser->GetNumberTextures();
	return m_psTextures;
}

/*!***************************************************************************
 @Function			SetTexture
 @Input				nIdx				texture number
 @Input				ui					opengl texture handle
 @Input				u32flags			texture flags
 @Description		Sets the textrue and applys the filtering.
*****************************************************************************/
void CPVRTPFXEffect::SetTexture(const unsigned int nIdx, const GLuint ui, const unsigned int u32flags)
{
	if(nIdx < (unsigned int) m_pParser->GetNumberTextures())
	{
		GLenum u32Target = GL_TEXTURE_2D;

		// Check if texture is a cubemap
		if((u32flags & PVRTEX_CUBEMAP) != 0)
			u32Target = GL_TEXTURE_CUBE_MAP;

		const SPVRTPFXParserTexture* pPFXTex = m_pParser->GetTexture(nIdx);
			
		// Only change parameters if ui (handle is > 0)
		if(ui > 0)
		{
			glBindTexture(u32Target, ui);

			// Set default filter from PFX file

			// --- Mipmapping/Minification
			switch(pPFXTex->nMIP)
			{
			case eFilter_None:			// No mipmapping
				switch(pPFXTex->nMin)
				{
				case eFilter_Nearest:
					glTexParameteri(u32Target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);					// Off
					break;
				case eFilter_Linear:
					glTexParameteri(u32Target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);					// Bilinear - no Mipmap
					break;
				}
				break;
			case eFilter_Nearest:		// Standard mipmapping
				switch(pPFXTex->nMin)
				{
				case eFilter_Nearest:
					glTexParameteri(u32Target, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);		// Nearest	- std. Mipmap
					break;
				case eFilter_Linear:
					glTexParameteri(u32Target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);		// Bilinear - std. Mipmap
					break;
				}
				break;
			case eFilter_Linear:		// Trilinear mipmapping
				switch(pPFXTex->nMin)
				{
				case eFilter_Nearest:
					glTexParameteri(u32Target, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);		// Nearest - Trilinear
					break;
				case eFilter_Linear:
					glTexParameteri(u32Target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);			// Bilinear - Trilinear
					break;
				}
				break;
			}

			// --- Magnification
			switch(pPFXTex->nMag)
			{
			case eFilter_Nearest:
				glTexParameteri(u32Target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				break;
			case eFilter_Linear:
				glTexParameteri(u32Target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				break;
			}

			// --- Wrapping S
			switch(pPFXTex->nWrapS)
			{
			case eWrap_Clamp:
				glTexParameteri(u32Target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				break;
			case eWrap_Repeat:
				glTexParameteri(u32Target, GL_TEXTURE_WRAP_S, GL_REPEAT);
				break;
			}

			// --- Wrapping T
			switch(pPFXTex->nWrapT)
			{
			case eWrap_Clamp:
				glTexParameteri(u32Target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				break;
			case eWrap_Repeat:
				glTexParameteri(u32Target, GL_TEXTURE_WRAP_T, GL_REPEAT);
				break;
			}

			// --- Wrapping R
	#ifdef GL_TEXTURE_WRAP_R
			switch(pPFXTex->nWrapR)
			{
			case eWrap_Clamp:
				glTexParameteri(u32Target, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				break;
			case eWrap_Repeat:
				glTexParameteri(u32Target, GL_TEXTURE_WRAP_R, GL_REPEAT);
				break;
			}
	#endif
		}

		m_psTextures[nIdx].ui = ui;

		// store flags
		unsigned int uiIndex = m_pParser->FindTextureIndex(pPFXTex->Name, m_nEffect);
		if(uiIndex != 0xFFFFFFFF)
		{
			m_pParser->GetEffect(m_nEffect).psTextures[uiIndex].u32Type = u32flags;
			m_pParser->GetEffect(m_nEffect).psTextures[uiIndex].uTextureHandle = ui;
		}
	}
}


/*!***************************************************************************
 @Function			SetDefaultSemanticValue
 @Input				pszName				name of uniform
 @Input				psDefaultValue      pointer to default value
 @Description		Sets the default value for the uniform semantic.
*****************************************************************************/
void CPVRTPFXEffect::SetDefaultUniformValue(const char *const pszName, const SPVRTSemanticDefaultData *psDefaultValue)
{
	GLint nLocation = glGetUniformLocation(m_uiProgram, pszName);

	switch(psDefaultValue->eType)
	{
		case eDataTypeMat2:
			glUniformMatrix2fv(nLocation, 1, GL_FALSE, psDefaultValue->pfData);
			break;
		case eDataTypeMat3:
			glUniformMatrix3fv(nLocation, 1, GL_FALSE, psDefaultValue->pfData);
			break;
		case eDataTypeMat4:
			glUniformMatrix4fv(nLocation, 1, GL_FALSE, psDefaultValue->pfData);
			break;
		case eDataTypeVec2:
			glUniform2fv(nLocation, 1, psDefaultValue->pfData);
			break;
		case eDataTypeVec3:
			glUniform3fv(nLocation, 1, psDefaultValue->pfData);
			break;
		case eDataTypeVec4:
			glUniform4fv(nLocation, 1, psDefaultValue->pfData);
			break;
		case eDataTypeIvec2:
			glUniform2iv(nLocation, 1, psDefaultValue->pnData);
			break;
		case eDataTypeIvec3:
			glUniform3iv(nLocation, 1, psDefaultValue->pnData);
			break;
		case eDataTypeIvec4:
			glUniform4iv(nLocation, 1, psDefaultValue->pnData);
			break;
		case eDataTypeBvec2:
			glUniform2i(nLocation, psDefaultValue->pbData[0] ? 1 : 0, psDefaultValue->pbData[1] ? 1 : 0);
			break;
		case eDataTypeBvec3:
			glUniform3i(nLocation, psDefaultValue->pbData[0] ? 1 : 0, psDefaultValue->pbData[1] ? 1 : 0, psDefaultValue->pbData[2] ? 1 : 0);
			break;
		case eDataTypeBvec4:
			glUniform4i(nLocation, psDefaultValue->pbData[0] ? 1 : 0, psDefaultValue->pbData[1] ? 1 : 0, psDefaultValue->pbData[2] ? 1 : 0, psDefaultValue->pbData[3] ? 1 : 0);
			break;
		case eDataTypeFloat:
			glUniform1f(nLocation, psDefaultValue->pfData[0]);
			break;
		case eDataTypeInt:
			glUniform1i(nLocation, psDefaultValue->pnData[0]);
			break;
		case eDataTypeBool:
			glUniform1i(nLocation, psDefaultValue->pbData[0] ? 1 : 0);
			break;

		case eNumDefaultDataTypes:
		case eDataTypeNone:
		default:
			break;
	}
}

void CPVRTPFXEffect::SetContext(SPVRTContext *const pContext)
{
	m_psContext = pContext;
}

/*!***************************************************************************
@Function		GetProgramHandle
@Return			unsigned int	
@Description	Returns the OGL program handle.
*****************************************************************************/
unsigned int CPVRTPFXEffect::GetProgramHandle() const
{
	return m_uiProgram;
}

/*!***************************************************************************
@Function		GetEffectIndex
@Return			unsigned int	
@Description	Gets the active effect index within the PFX file.
*****************************************************************************/
unsigned int CPVRTPFXEffect::GetEffectIndex() const
{
	return m_nEffect;
}


/*****************************************************************************
 End of file (PVRTPFXParserAPI.cpp)
*****************************************************************************/

