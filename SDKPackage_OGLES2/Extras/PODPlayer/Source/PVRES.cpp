/******************************************************************************

 @File         PVRES.cpp

 @Title        Simple parser for PVRES files

 @Version      

 @Copyright    Copyright (c) Imagination Technologies Limited.

 @Platform     Independent

 @Description  Shows how to use the pfx format

******************************************************************************/

#include "PVRES.h"

using namespace pvrengine;

/******************************************************************************/

PVRES::PVRES()
{
	Init();
}

/******************************************************************************/

void PVRES::Init()
{
	for (int i=0;i<kiNumPVRESValues;i++)
	{

		m_PVRESValues[i]=NULL;
	}

	m_PVRESValues[ebFullScreen] = new PVRESValue<bool>(eBool,false);
	m_PVRESValues[ebShowFPS] = new PVRESValue<bool>(eBool, false);
	m_PVRESValues[ebVertSync] = new PVRESValue<bool>(eBool, false);
	m_PVRESValues[ebLogToFile] = new PVRESValue<bool>(eBool, true);
	m_PVRESValues[ebPowerSaving] = new PVRESValue<bool>(eBool, true);
	m_PVRESValues[ebDefaultLight] = new PVRESValue<bool>(eBool, false);
	m_PVRESValues[ebFrustumCull] = new PVRESValue<bool>(eBool, false);
	m_PVRESValues[estrScriptFileName] = new PVRESValue<CPVRTString>(eString,"");
	m_PVRESValues[estrPFXPath] = new PVRESValue<CPVRTString>(eString,"");
	m_PVRESValues[estrTexturePath] = new PVRESValue<CPVRTString>(eString,"");
	m_PVRESValues[estrTitle] = new PVRESValue<CPVRTString>(eString,"");
	m_PVRESValues[estrSubTitle] = new PVRESValue<CPVRTString>(eString,"");
	m_PVRESValues[ef32StartFrame] = new PVRESValue<float>(eFloat32,0.f);
	m_PVRESValues[ef32AnimationSpeed] = new PVRESValue<float>(eFloat32,1.f);
	m_PVRESValues[ei32FSAA] = new PVRESValue<int>(eInt32, 0);
	m_PVRESValues[ef32QuitAfterTime] = new PVRESValue<float>(eFloat32,-1.f);
	m_PVRESValues[ei32QuitAfterFrame] = new PVRESValue<int>(eInt32, -1);
	m_PVRESValues[ei32Height] = new PVRESValue<int>(eInt32, 0);
	m_PVRESValues[ei32Width] = new PVRESValue<int>(eInt32, 0);
	m_PVRESValues[ei32PosX] = new PVRESValue<int>(eInt32, 0);
	m_PVRESValues[ei32PosY] = new PVRESValue<int>(eInt32, 0);
	m_PVRESValues[ei32DrawMode] = new PVRESValue<int>(eInt32, eNormal);

	// private values
	m_PVRESValues[estrPODFileName] = new PVRESValue<CPVRTString>(eString,"");

}

/******************************************************************************/

PVRES::~PVRES()
{
	for (int i=0;i<kiNumPVRESValues;i++)
	{
		if(m_PVRESValues[i])
		{
			PVRDELETE(m_PVRESValues[i]);
		}
	}
}

/******************************************************************************/

// special value that requires more than just being set, hence specialised function
void PVRES::setPODFileName(const CPVRTString& strPODFileName)
{
	if(isDefault(estrScriptFileName))
		set(estrPODFileName,strPODFileName);	// note private value
	else
	{
		CPVRTString path = PVRTStringGetContainingDirectoryPath(get(estrScriptFileName));
		set(estrPODFileName, path.length() ? path+"/"+strPODFileName : strPODFileName);
	}
	// check if texture or pfx paths have been set separately
	// otherwise use pod path
	if(isDefault(estrPFXPath))
	{	// set pod path
		set(estrPFXPath,PVRTStringGetContainingDirectoryPath(get(estrPODFileName)));
	}
	if(isDefault(estrTexturePath))
	{	// set pod path
		set(estrTexturePath,PVRTStringGetContainingDirectoryPath(get(estrPODFileName)));
	}
	if(isDefault(estrTitle))
	{	// set pod path
		set(estrTitle,PVRTStringGetFileName(get(estrPODFileName)));
	}
}

// downside is this needs to be special too
CPVRTString PVRES::getPODFileName()
{
	return get(estrPODFileName);
}


/******************************************************************************
End of file (PVRES.cpp)
******************************************************************************/

