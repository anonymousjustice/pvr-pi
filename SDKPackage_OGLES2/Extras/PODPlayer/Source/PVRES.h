/******************************************************************************

 @File         PVRES.h

 @Title        A simple script class for use with PVREngine

 @Version      

 @Copyright    Copyright (c) Imagination Technologies Limited.

 @Platform     Independent - OGL/OGLES/OGLES2 Specific at the moment

 @Description  A class for holding the information from a .pvres script file in a
               more useful form for the PODPlayer to use.

******************************************************************************/

#ifndef PVRES_H
#define PVRES_H

/******************************************************************************
Includes
******************************************************************************/
#include "PVREngine.h"

enum EPVRESBoolValueName
{
	ebFullScreen =0,ebShowFPS,ebVertSync,ebLogToFile,ebPowerSaving,ebDefaultLight,ebFrustumCull,
	eNumPVRESBoolValues
};
enum EPVRESStringValueName
{
	estrScriptFileName=eNumPVRESBoolValues , 
	estrPFXPath, estrTexturePath, estrTitle, estrSubTitle,
	eNumPVRESStringValues
};
enum EPVRESFloat32ValueName
{
	ef32StartFrame=eNumPVRESStringValues, ef32AnimationSpeed, ef32QuitAfterTime,
	eNumPVRESFloatValues
};
enum EPVRESInt32ValueName
{
	ei32FSAA=eNumPVRESFloatValues, ei32Height, ei32Width, ei32PosX, ei32PosY, ei32QuitAfterFrame, ei32DrawMode,
	eNumPVRESInt32Values
};

/*!****************************************************************************
Class
******************************************************************************/
/*!***************************************************************************
* @Class PVRES
* @Brief 	A simple data class for use with PODPlayer.
* @Description 	A simple data class for use with PODPlayer.
*****************************************************************************/
class PVRES
{
public:
	/*!***************************************************************************
	@Function			PVRES
	@Description		blank constructor.
	*****************************************************************************/
	PVRES();
	/*!***************************************************************************
	@Function			~PVRES
	@Description		destructor.
	*****************************************************************************/
	~PVRES();

	/*!***************************************************************************
	@Function			Init
	@Description		sets some defaut values.
	*****************************************************************************/
	void Init();

	void setPODFileName(const CPVRTString& strPODFileName);
	CPVRTString getPODFileName();


	enum EPVRESValueType
	{
		eBool = 0,
		eString,
		eFloat32,
		eInt32,
		eNumPVRESTypes
	};
 
	void set(const EPVRESBoolValueName eValueName, const bool tValue)
	{
		_ASSERT(m_PVRESValues[eValueName]->getType()==eBool);
		((PVRESValue<bool>*)(m_PVRESValues[eValueName]))->setValue(tValue);
	}
	void set(const EPVRESStringValueName eValueName, const CPVRTString tValue)
	{
		_ASSERT(m_PVRESValues[eValueName]->getType()==eString);
		((PVRESValue<CPVRTString>*)(m_PVRESValues[eValueName]))->setValue(tValue);
	}
	void set(const EPVRESFloat32ValueName eValueName, const float tValue)
	{
		_ASSERT(m_PVRESValues[eValueName]->getType()==eFloat32);
		((PVRESValue<float>*)(m_PVRESValues[eValueName]))->setValue(tValue);
	}
	void set(const EPVRESInt32ValueName eValueName, const int tValue)
	{
		_ASSERT(m_PVRESValues[eValueName]->getType()==eInt32);
		((PVRESValue<int>*)(m_PVRESValues[eValueName]))->setValue(tValue);
	}

	bool get(const EPVRESBoolValueName eValueName) const
	{
		_ASSERT(m_PVRESValues[eValueName]->getType()==eBool);
		return ((PVRESValue<bool>*)(m_PVRESValues[eValueName]))->getValue();
	}
	CPVRTString get(const EPVRESStringValueName eValueName) const
	{
		_ASSERT(m_PVRESValues[eValueName]->getType()==eString);
		return ((PVRESValue<CPVRTString>*)(m_PVRESValues[eValueName]))->getValue();
	}
	float get(const EPVRESFloat32ValueName eValueName) const
	{
		_ASSERT(m_PVRESValues[eValueName]->getType()==eFloat32);
		return ((PVRESValue<float>*)(m_PVRESValues[eValueName]))->getValue();
	}
	int get(const EPVRESInt32ValueName eValueName) const
	{
		_ASSERT(m_PVRESValues[eValueName]->getType()==eInt32);
		return ((PVRESValue<int>*)(m_PVRESValues[eValueName]))->getValue();
	}

	bool isDefault(const EPVRESBoolValueName eValueName) const
	{
		return m_PVRESValues[eValueName]->isDefault();
	}
	bool isDefault(const EPVRESStringValueName eValueName) const
	{
		return m_PVRESValues[eValueName]->isDefault();
	}
	bool isDefault(const EPVRESFloat32ValueName eValueName) const
	{
		return m_PVRESValues[eValueName]->isDefault();
	}
	bool isDefault(const EPVRESInt32ValueName eValueName) const
	{
		return m_PVRESValues[eValueName]->isDefault();
	}

private:



	enum EPVRESPrivateValueType
	{
		eBoolPrivate = eNumPVRESTypes,
		eStringPrivate,
		eFloat32Private,
		eInt32Private,
		eNumPrivatePVRESTypes
	};
	enum EPVRESBoolPrivateValueName
	{
		eNumPVRESBoolPrivateValueNames=eNumPVRESInt32Values
	};
	enum EPVRESStringPrivateValueName
	{
		estrPODFileName = eNumPVRESBoolPrivateValueNames,
		eNumPVRESStringPrivateValueName
	};
	enum EPVRESFloat32PrivateValueName
	{
		eNumPVRESFloat32PrivateValueNames = eNumPVRESStringPrivateValueName
	};
	enum EPVRESInt32PrivateValueName
	{
		eNumPVRESInt32PrivateValueNames = eNumPVRESFloat32PrivateValueNames
	};

	static const int kiNumPVRESValues = eNumPVRESInt32PrivateValueNames;

	void set(const EPVRESBoolPrivateValueName eValueName, const bool tValue)
	{
		((PVRESValue<bool>*)(m_PVRESValues[eValueName]))->setValue(tValue);
	}
	void set(const EPVRESStringPrivateValueName eValueName, const CPVRTString tValue)
	{
		((PVRESValue<CPVRTString>*)(m_PVRESValues[eValueName]))->setValue(tValue);
	}
	void set(const EPVRESFloat32PrivateValueName eValueName, const float tValue)
	{
		((PVRESValue<float>*)(m_PVRESValues[eValueName]))->setValue(tValue);
	}
	void set(const EPVRESInt32PrivateValueName eValueName, const int tValue)
	{
		((PVRESValue<int>*)(m_PVRESValues[eValueName]))->setValue(tValue);
	}

	bool get(const EPVRESBoolPrivateValueName eValueName) const
	{
		return ((PVRESValue<bool>*)(m_PVRESValues[eValueName]))->getValue();
	}
	CPVRTString get(const EPVRESStringPrivateValueName eValueName) const
	{
		return ((PVRESValue<CPVRTString>*)(m_PVRESValues[eValueName]))->getValue();
	}
	float get(const EPVRESFloat32PrivateValueName eValueName) const
	{
		return ((PVRESValue<float>*)(m_PVRESValues[eValueName]))->getValue();
	}
	int get(const EPVRESInt32PrivateValueName eValueName) const
	{
		return ((PVRESValue<int>*)(m_PVRESValues[eValueName]))->getValue();
	}

	bool isDefault(const EPVRESBoolPrivateValueName eValueName) const
	{
		return m_PVRESValues[eValueName]->isDefault();
	}
	bool isDefault(const EPVRESStringPrivateValueName eValueName) const
	{
		return m_PVRESValues[eValueName]->isDefault();
	}
	bool isDefault(const EPVRESFloat32PrivateValueName eValueName) const
	{
		return m_PVRESValues[eValueName]->isDefault();
	}
	bool isDefault(const EPVRESInt32PrivateValueName eValueName) const
	{
		return m_PVRESValues[eValueName]->isDefault();
	}

	class PVRESValueBase
	{
		EPVRESValueType	m_eType;
		union
		{
			EPVRESBoolValueName m_eBoolValueName;
			EPVRESStringValueName m_eStringValueName;
			EPVRESFloat32ValueName m_eFloat32ValueName;
			EPVRESInt32ValueName m_eInt32ValueName;
		};
	protected:
		bool m_bDefault;
	public:
		PVRESValueBase(){}
		virtual ~PVRESValueBase(){}
		PVRESValueBase(EPVRESValueType eType):m_eType(eType),m_bDefault(true){}
		EPVRESValueType getType() const { return m_eType;}
		bool isDefault() const { return m_bDefault;}
	};

	template<typename T>
	class PVRESValue : public PVRESValueBase
	{
		T m_tValue;
	public:
		virtual ~PVRESValue(){}
		PVRESValue(const EPVRESValueType eType, const T tValue):
		  PVRESValueBase(eType),m_tValue(tValue){}
		  T getValue() const { return m_tValue; }	// slow for strings - use reference?
		  virtual void setValue(const T tValue){ m_tValue=tValue; m_bDefault=false;}
	};


	// actual data store

	PVRESValueBase* m_PVRESValues[kiNumPVRESValues];

};

#endif // PVRES_H

/******************************************************************************
End of file (PVRES.h)
******************************************************************************/

