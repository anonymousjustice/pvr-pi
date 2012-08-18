/******************************************************************************

 @File         ConsoleLog.cpp

 @Title        Console Log

 @Version      

 @Copyright    Copyright (c) Imagination Technologies Limited.

 @Platform     Independent

 @Description  A Class for storing output from the PVREngine and apps that use
               the engine. Main features are the ability to output a file of the
               log's contents, whether this is written to constantly or not. The
               primary function is log() which takes formatted input and logs to
               the console.

******************************************************************************/

#include "ConsoleLog.h"
#include <string.h>

#if defined(_WIN32) && !defined(__BADA__)
#define vsnprintf _vsnprintf
#endif

namespace pvrengine
{


	/******************************************************************************/

	ConsoleLog::ConsoleLog():
		m_bStraightToFile(false),
			m_LogFile(NULL)
	{}

	/******************************************************************************/

	ConsoleLog::~ConsoleLog()
	{
		if(m_LogFile)
		{
			fflush(m_LogFile);
			fclose(m_LogFile);
		}
	}

	/******************************************************************************/


#if defined(__SYMBIAN32__) || defined(UITRON) || defined(_UITRON_)

	// these platforms don't support snprintf or vsnprintf so hope 4096 is good enough...
	void ConsoleLog::log(const char* pszFormat, ...)
	{
		va_list args;
		va_start(args,pszFormat);
		char pszString[4096];
		if (strlen(pszFormat)>4095)
		{
			sprintf(pszString, "Line too long for console.");
		}
		else
		{
			vsprintf(pszString, pszFormat, args);
		}
		va_end(args);
		m_daLog.append(CPVRTString(pszString));
		if(m_LogFile)
		{
			fwrite(pszString,1,strlen(pszString),m_LogFile);
			fflush(m_LogFile);
		}
		PVRTERROR_OUTPUT_DEBUG(pszString);
	}


#else
	// do something a bit more intelligent for other platforms

	// reasonable default buffer size to avoid allocating every log line
	const int iDefaultBufferSize = 1024;

	void ConsoleLog::vlogFixedSize(CPVRTString &strLogString, const char* pszFormat,  va_list args)
	{
		char pszString[iDefaultBufferSize];

		vsnprintf(pszString,iDefaultBufferSize-1,pszFormat,args);
		strLogString = pszString;
		m_daLog.append(strLogString);
	}

	void ConsoleLog::log(const char* pszFormat, ...)
	{
		va_list args;
		va_start(args,pszFormat);
		CPVRTString strLogString;
		int iStrSize = vsnprintf(NULL,0,pszFormat,args)+1;
		if(iStrSize>iDefaultBufferSize)
		{	// longer line so use dynamic buffer
			char* pszString = new char[iStrSize+1];
			if(pszString)
			{
				vsnprintf(pszString, iStrSize+1, pszFormat, args);
				va_end(args);
				strLogString = pszString;
				m_daLog.append(strLogString);
				delete[](pszString);
			}
			else
			{	// fall back to fixed size
				vlogFixedSize(strLogString, pszFormat,args);
			}
		}
		else
		{
			vlogFixedSize(strLogString,pszFormat,args);
		}

		if(m_LogFile)
		{
			fwrite(strLogString.c_str(),1,strLogString.length(),m_LogFile);
			fflush(m_LogFile);
		}
		PVRTERROR_OUTPUT_DEBUG(strLogString.c_str());
	}
#endif

	/******************************************************************************/

	void ConsoleLog::log(const CPVRTString& sString)
	{
		m_daLog.append(sString);
		if(m_LogFile)
		{
			fwrite(sString.c_str(),1,sString.length(),m_LogFile);
			fflush(m_LogFile);
		}
		PVRTERROR_OUTPUT_DEBUG(sString.c_str());
	}

	/******************************************************************************/

	bool ConsoleLog::setOutputFile(const CPVRTString strLogFile)
	{
		bool bClose=true;
		m_strLogFile = strLogFile;
		if(m_LogFile)
		{	// writing straight out set
			bClose=false;
			fclose(m_LogFile);
			m_LogFile=NULL;
		}
		// open new file and continue
		m_LogFile = fopen(m_strLogFile.c_str(),"w");
		if(!m_LogFile)
		{
			return false;
		}
		if(bClose)
		{
			fclose(m_LogFile);
			m_LogFile = NULL;
		}
		return true;
	}

	/******************************************************************************/

	void ConsoleLog::setStraightToFile(bool bStraightToFile)
	{
		if(bStraightToFile)
		{	// check if valid file set
			if(m_LogFile)
			{	// file is already open
				fclose(m_LogFile);
				m_LogFile=NULL;
			}
			m_LogFile = fopen(m_strLogFile.c_str(),"w");
		}
		else
		{
			if(m_LogFile)
			{
				fclose(m_LogFile);
				m_LogFile=NULL;
			}
		}
	}

	/******************************************************************************/

	bool ConsoleLog::getStraightToFile()
	{
		return(m_LogFile==NULL);
	}

	/******************************************************************************/

	dynamicArray<CPVRTString> ConsoleLog::getLog()
	{
		return m_daLog;
	}

	/******************************************************************************/

	CPVRTString ConsoleLog::getLastLogLine()
	{
		if(m_daLog.getSize())
		{
			return m_daLog[m_daLog.getSize()-1];
		}
		return CPVRTString("");
	}

	/******************************************************************************/

	bool ConsoleLog::writeToFile()
	{
		bool bCloseFile=true;
		if(m_LogFile)
		{	// already open and writing to
			// so replace the file with the entire log
			bCloseFile = false;
			fclose(m_LogFile);
			m_LogFile = NULL;
		}
		m_LogFile = fopen(m_strLogFile.c_str(),"w");
		if(m_LogFile)
		{
			for(int i=0;i<m_daLog.getSize();i++)
				fwrite(m_daLog[i].c_str(),1,m_daLog[i].size(),m_LogFile);
		}
		else
		{
			return false;
		}
		if(bCloseFile)
		{
			fclose(m_LogFile);
			m_LogFile=NULL;
		}
		return true;
	}

	/******************************************************************************/

	bool ConsoleLog::appendToFile()
	{
		bool bCloseFile=false;
		if(!m_LogFile)
		{ // need to open file
			m_LogFile = fopen(m_strLogFile.c_str(),"a");
			if(!m_LogFile)
			{
				return false;
			}
			bCloseFile=true;
		}
		for(int i=0;i<m_daLog.getSize();i++)
			fwrite(m_daLog[i].c_str(),1,strlen(m_daLog[i].c_str()),m_LogFile);

		if(bCloseFile)
		{
			fclose(m_LogFile);
			m_LogFile = NULL;
		}
		return true;
	}

	/******************************************************************************/

	void ConsoleLog::clearLog()
	{
		m_daLog = dynamicArray<CPVRTString>();
	}


}

/******************************************************************************
End of file (ConsoleLog.cpp)
******************************************************************************/

