/******************************************************************************

 @File         PVRESParser.cpp

 @Title        Simple parser for PVRES files

 @Version      

 @Copyright    Copyright (c) Imagination Technologies Limited.

 @Platform     Independent

 @Description  A simple script parser for use with PVREngine

******************************************************************************/
#include "PVRESParser.h"
#include "PVREngine.h"
#include <string.h>


using namespace pvrengine;

/******************************************************************************/

PVRESParser::PVRESParser()
{
	m_strError = "";
	m_bScriptFileSpecified=true;
}

/******************************************************************************/

PVRESParser::~PVRESParser()
{
}

/******************************************************************************/

bool getline(CPVRTString& strSrc, CPVRTString& strLine, const char delimiter)
{
	if(strSrc.size()>0)
	{
		size_t i32LineLength = strSrc.find_first_of(delimiter);
		if(!i32LineLength || i32LineLength==CPVRTString::npos)
		{
			strLine = strSrc;
			strSrc.clear();
		}
		else
		{
			strLine = strSrc.substr(0,i32LineLength-1);
			strSrc = strSrc.substr(i32LineLength+1);
		}
		return true;
	}
	return false;
}

/******************************************************************************/

bool PVRESParser::Parse(PVRES *pPVRES)
{
	if(m_bScriptFileSpecified)
	{	// file has been specified
		// read script file
		CPVRTResourceFile script(pPVRES->get(estrScriptFileName).c_str());

		if(!script.Size())
		{
			m_strError = CPVRTString("Failed to read the script.");
			return false;
		}

		m_strScript = CPVRTString((char*) script.DataPtr());
	}
	else
	{
		return true;	// use default PVRES that should outlive the PVRESParser class
	}

	// parse the script file
	CPVRTString strLine;

	char cBool;
	int i32Int;


	// deal with different commands
	while(getline(m_strScript, strLine, '\n'))
	{
		if (strLine.substr(0,strlen("fullscreen:")).compare("fullscreen:")==0)
		{
			cBool = strLine[strlen("fullscreen:")];
			pPVRES->set(ebFullScreen,cBool=='Y' || cBool=='y');
		}
		else if (strLine.substr(0,strlen("title:")).compare("title:")==0)
		{
			pPVRES->set(estrTitle,strLine.substr(strlen("title:")));
		}
		else if (strLine.substr(0,strlen("subtitle:")).compare("subtitle:")==0)
		{
			pPVRES->set(estrSubTitle,strLine.substr(strlen("subtitle:")));
		}
		else if (strLine.substr(0,strlen("pod:")).compare("pod:")==0)
		{
			pPVRES->setPODFileName(strLine.substr(strlen("pod:")));
		}
		else if (strLine.substr(0,strlen("startframe:")).compare("startframe:")==0)
		{
			pPVRES->set(ef32StartFrame,(float)atof(strLine.c_str() + strlen("startframe:")));
		}
		else if (strLine.substr(0,strlen("showfps:")).compare("showfps:")==0)
		{
			cBool = strLine[strlen("showfps:")];
			pPVRES->set(ebShowFPS,cBool=='Y' || cBool=='y');
		}
		else if (strLine.substr(0,strlen("animspeed:")).compare("animspeed:")==0)
		{
			float fAnimationSpeed;
			fAnimationSpeed = (float) atof(strLine.c_str() + strlen("animspeed:"));
			pPVRES->set(ef32AnimationSpeed,fAnimationSpeed);
		}
		else if (strLine.substr(0,strlen("vertsync:")).compare("vertsync:")==0)
		{
			cBool = strLine[strlen("vertsync:")];
			pPVRES->set(ebVertSync,cBool=='Y' || cBool=='y');
		}
		else if (strLine.substr(0,strlen("logtofile:")).compare("logtofile:")==0)
		{
			cBool = strLine[strlen("logtofile:")];
			pPVRES->set(ebLogToFile,cBool=='Y' || cBool=='y');
		}
		else if (strLine.substr(0,strlen("defaultlight:")).compare("defaultlight:")==0)
		{
			cBool = strLine[strlen("defaultlight:")];
			pPVRES->set(ebDefaultLight,cBool=='Y' || cBool=='y');
		}
		else if (strLine.substr(0,strlen("frustumcull:")).compare("frustumcull:")==0)
		{
			cBool = strLine[strlen("frustumcull:")];
			pPVRES->set(ebFrustumCull,cBool=='Y' || cBool=='y');
		}
		else if (strLine.substr(0,strlen("powersaving:")).compare("powersaving:")==0)
		{
			cBool = strLine[strlen("powersaving:")];
			pPVRES->set(ebPowerSaving,cBool=='Y' || cBool=='y');
		}
		else if (strLine.substr(0,strlen("fsaa:")).compare("fsaa:")==0)
		{
			i32Int = atoi(strLine.c_str() +  strlen("fsaa:"));
			pPVRES->set(ei32FSAA,i32Int);
		}
		else if (strLine.substr(0,strlen("height:")).compare("height:")==0)
		{
			i32Int = atoi(strLine.c_str() + strlen("height:"));
			pPVRES->set(ei32Height,i32Int);
		}
		else if (strLine.substr(0,strlen("width:")).compare("width:")==0)
		{
			i32Int = atoi(strLine.c_str() + strlen("width:"));
			pPVRES->set(ei32Width,i32Int);
		}
		else if (strLine.substr(0,strlen("posx:")).compare("posx:")==0)
		{
			i32Int = atoi(strLine.c_str() + strlen("posx:"));
			pPVRES->set(ei32PosX,i32Int);
		}
		else if (strLine.substr(0,strlen("posy:")).compare("posy:")==0)
		{
			i32Int = atoi(strLine.c_str() + strlen("posy:"));
			pPVRES->set(ei32PosY,i32Int);
		}
		else if (strLine.substr(0,strlen("quitaftertime:")).compare("quitaftertime:")==0)
		{
			pPVRES->set(ef32QuitAfterTime,(float)atof(strLine.c_str() + strlen("quitaftertime:")));
		}
		else if (strLine.substr(0,strlen("quitafterframe:")).compare("quitafterframe:")==0)
		{
			i32Int = atoi(strLine.c_str() + strlen("quitafterframe:"));
			pPVRES->set(ei32QuitAfterFrame,i32Int);
		}
		else if (strLine.substr(0,strlen("drawmode:")).compare("drawmode:")==0)
		{
			i32Int = atoi(strLine.c_str() + strlen("drawmode:"));
			pPVRES->set(ei32DrawMode,i32Int);
		}
	}

	return true;	//PVRES should outlive the PVRESParser class
}

/******************************************************************************/

void PVRESParser::setScript(const CPVRTString& strScript)
{
	m_strScript = strScript;
	m_bScriptFileSpecified = false;
}

/******************************************************************************/

void PVRESParser::clearScript()
{
	m_strScript = "";
}

/******************************************************************************
End of file (PVRESParser.cpp)
******************************************************************************/

