/******************************************************************************

 @File         Uniform.cpp

 @Title        Texture

 @Version      

 @Copyright    Copyright (c) Imagination Technologies Limited.

 @Platform     Independent

 @Description  Texture container for OGLES2

******************************************************************************/

#include "Uniform.h"

namespace pvrengine
{
	/*!****************************************************************************
	@Function		Uniform
	@Description	Blank constructor from PFX
	******************************************************************************/
	Uniform::Uniform()
	{

	}

	/*!****************************************************************************
	@Function		Uniform
	@Input			sUniform - a PFX uniform struct
	@Description	Constructor from PFX uniform
	******************************************************************************/
	Uniform::Uniform(const SPVRTPFXUniform sUniform) : m_u32Location(sUniform.nLocation),
													   m_eSemantic((EUniformSemantic)sUniform.nSemantic),
													   m_u32Idx(sUniform.nIdx)
	{

	}
}

/******************************************************************************
End of file (Uniform.cpp)
******************************************************************************/

