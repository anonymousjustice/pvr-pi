/******************************************************************************

 @File         MeshManager.cpp

 @Title        Introducing the POD 3d file format

 @Version      

 @Copyright    Copyright (c) Imagination Technologies Limited.

 @Platform     Independent

 @Description  Shows how to use the pfx format

******************************************************************************/

#include "MeshManager.h"

namespace pvrengine
{
	


	/******************************************************************************/

	void MeshManager::setDrawMode(const EDrawMode eDrawMode)
	{
		for(int i=0;i<m_daElements.getSize();i++)
		{
			m_daElements[i]->setDrawMode(eDrawMode);
		}
	}


}

/******************************************************************************
End of file (MeshManager.cpp)
******************************************************************************/

