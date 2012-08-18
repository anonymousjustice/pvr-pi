/******************************************************************************

 @File         SimpleCamera.cpp

 @Title        Simple Camera

 @Version      

 @Copyright    Copyright (c) Imagination Technologies Limited.

 @Platform     Independent

 @Description  A simple yaw, pitch camera with fixed up vector

******************************************************************************/

#include "SimpleCamera.h"
#include "TimeController.h"
#include <math.h>


namespace pvrengine
{


	/******************************************************************************/

	SimpleCamera::SimpleCamera(TimeController *pTimeController)
	{
		m_vPosition.x = m_vVelocity.x = f2vt(0.0f);
		m_vPosition.y = m_vVelocity.y = f2vt(0.0f);
		m_vPosition.z = m_vVelocity.z = f2vt(0.0f);
		m_fHeading = f2vt(0.0f);
		m_fElevation = f2vt(0.0f);
		m_fMoveSpeed = f2vt(5.0f);
		m_fRotSpeed = f2vt(0.01f);
		m_fFOV = f2vt(0.7f);
		m_bInverted = false;
		m_pTimeController = pTimeController;
	}

	/******************************************************************************/

	void SimpleCamera::updatePosition()
	{	
	// Most of this stuff is to try and smooth movement when controlled by the primitive keyboard input available

		PVRTVec3 vDec = m_vVelocity * f2vt(m_pTimeController->getDeltaTime()) * m_fMoveSpeed * f2vt(0.1f);

		while(vDec.lenSqr()>m_vVelocity.lenSqr())
		{
			vDec /= f2vt(2.0f);
		}

		m_vVelocity -= vDec;

		if(m_vVelocity.lenSqr()>m_fMoveSpeed*m_fMoveSpeed)
		{
			m_vVelocity = m_vVelocity.normalized()*m_fMoveSpeed;
		}
 		m_vPosition += m_vVelocity * f2vt(m_pTimeController->getDeltaTime());
	}

	/******************************************************************************/

	void SimpleCamera::setTarget(const PVRTVec3& vec)
	{
		PVRTVec3 vActual = m_vPosition - vec;
		setTo(vActual);
	}

	/******************************************************************************/

	void SimpleCamera::setTo(const PVRTVec3& vec)
	{

		// find angle from horizontal
		m_fElevation = f2vt((float) atan(VERTTYPEDIV(vec.y,f2vt(sqrt(vt2f(vec.z*vec.z+vec.x*vec.x))))));

		// find principle angle from straight ahead
		m_fHeading = f2vt((float) atan2(vt2f(vec.x),vt2f(vec.z)));

		m_fHeading -= PVRT_PI;

		while(m_fHeading < 0.0f)
			m_fHeading+=PVRT_TWO_PI;

	}

	/******************************************************************************/

	void SimpleCamera::getToAndUp(PVRTVec3& vTo, PVRTVec3& vUp) const
	{
		vTo = PVRTVec3(f2vt(0.0f),f2vt(0.0f),f2vt(1.0f));
		vUp = PVRTVec3(f2vt(0.0f),f2vt(1.0f),f2vt(0.0f));

		PVRTMat3 mRotY = PVRTMat3::RotationY(m_fHeading);
		PVRTMat3 mRotX = PVRTMat3::RotationX(m_fElevation);

		vTo = (vTo*mRotX)*mRotY;
		vUp = (vUp*mRotX)*mRotY;

	}

	/******************************************************************************/

	void SimpleCamera::getTargetAndUp(PVRTVec3& vTarget, PVRTVec3& vUp) const
	{
		vTarget = PVRTVec3(f2vt(0.0f),f2vt(0.0f),f2vt(1.0f));
		vUp = PVRTVec3(f2vt(0.0f),f2vt(1.0f),f2vt(0.0f));

		PVRTMat3 mRotY = PVRTMat3::RotationY(m_fHeading);
		PVRTMat3 mRotX = PVRTMat3::RotationX(m_fElevation);

		vTarget = (vTarget*mRotX)*mRotY;
		vUp = (vUp*mRotX)*mRotY;

		vTarget +=m_vPosition;
	}

	/******************************************************************************/

	PVRTVec3 SimpleCamera::getTo() const
	{
		PVRTVec3 vTo(f2vt(0.0f),f2vt(0.0f),f2vt(1.0f));

		PVRTMat3 mRotY = PVRTMat3::RotationY(m_fHeading);
		PVRTMat3 mRotX = PVRTMat3::RotationX(m_fElevation);

		vTo = (vTo*mRotX)*mRotY;

		return vTo;
	}

	/******************************************************************************/

	PVRTVec3 SimpleCamera::getUp() const
	{
		PVRTVec3 vUp(f2vt(0.0f),f2vt(1.0f),f2vt(0.0f));

		PVRTMat3 mRotY = PVRTMat3::RotationY(m_fHeading);
		PVRTMat3 mRotX = PVRTMat3::RotationX(m_fElevation);
		vUp = (vUp*mRotX)*mRotY;

		return vUp;
	}

	/******************************************************************************/

	PVRTVec3 SimpleCamera::getTarget() const
	{
		PVRTVec3 vTarget = getTo();
		vTarget.x += m_vPosition.x;
		vTarget.y += m_vPosition.y;
		vTarget.z += m_vPosition.z;

		return vTarget;
	}

	/******************************************************************************/

	void SimpleCamera::YawRight()
	{
		m_fHeading-=m_fRotSpeed;
		if(m_fHeading>=PVRT_TWO_PI)
			m_fHeading-=PVRT_TWO_PI;
	}

	/******************************************************************************/

	void SimpleCamera::YawLeft()
	{
		m_fHeading+=m_fRotSpeed;
		if(m_fHeading<0)
			m_fHeading+=PVRT_TWO_PI;
	}

	/******************************************************************************/

	void SimpleCamera::PitchUp()
	{
		if(m_bInverted)
		{
			m_fElevation+=m_fRotSpeed;
			if(m_fElevation>=PVRT_PI_OVER_TWO)
				m_fElevation=PVRT_PI_OVER_TWO - f2vt(0.001f);
		}
		else
		{
			m_fElevation-=m_fRotSpeed;
			if(m_fElevation<=-PVRT_PI_OVER_TWO)
				m_fElevation=-PVRT_PI_OVER_TWO + f2vt(0.001f);
		}
	}

	/******************************************************************************/

	void SimpleCamera::PitchDown()
	{
		if(m_bInverted)
		{
			m_fElevation-=m_fRotSpeed;
			if(m_fElevation<=-PVRT_PI_OVER_TWO)
				m_fElevation=-PVRT_PI_OVER_TWO + f2vt(0.001f);
		}
		else
		{
			m_fElevation+=m_fRotSpeed;
			if(m_fElevation>=PVRT_PI_OVER_TWO)
				m_fElevation=PVRT_PI_OVER_TWO - f2vt(0.001f);
		}
	}

	/******************************************************************************/

	void SimpleCamera::MoveForward()
	{
		PVRTVec3 vTo = getTo().normalized();
		m_vVelocity +=vTo*m_fMoveSpeed;
	}

	/******************************************************************************/

	void SimpleCamera::MoveBack()
	{
		PVRTVec3 vTo = getTo().normalized();
		m_vVelocity -=vTo*m_fMoveSpeed;
	}

}

/******************************************************************************
End of file (SimpleCamera.cpp)
******************************************************************************/

