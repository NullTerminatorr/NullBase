#include "includes.h"

DWORD LocalPlayer::LocalBaseaddress = 0;

DWORD LocalPlayer::getLocalPlayer()
{
	return LocalPlayer::LocalBaseaddress;
}

void LocalPlayer::setLocalPlayer()
{
	LocalPlayer::LocalBaseaddress = rpm<DWORD>(baseAddress + offs::dwLocalPlayer);
}

int LocalPlayer::getLocalFlags()
{
	return rpm<int>(LocalPlayer::getLocalPlayer() + netvars::m_fFlags);
}

int LocalPlayer::getLocalHealth()
{
	return rpm<int>(LocalPlayer::getLocalPlayer() + netvars::m_iHealth);
}

int LocalPlayer::getLocalTeam()
{
	return rpm<int>(LocalPlayer::getLocalPlayer() + netvars::m_iTeamNum);
}

void LocalPlayer::forceJump(int waitTime)
{
	wpm<int>(1, baseAddress + offs::dwForceJump);
	Sleep(waitTime);
	wpm<int>(0, baseAddress + offs::dwForceJump);
}

int LocalPlayer::getLocalCrossID()
{
	auto temp = rpm<int>(LocalPlayer::getLocalPlayer() + netvars::m_iCrosshairId);
	if (temp <= 0 || temp > 32)
		return -1;
	return temp;
}

D3DXVECTOR3 LocalPlayer::getLocalPos()
{
	return rpm<D3DXVECTOR3>(LocalPlayer::getLocalPlayer() + netvars::m_vecOrigin);
}

D3DXMATRIX	LocalPlayer::getLocalViewMatrix()
{
	return rpm<D3DXMATRIX>(baseAddress + offs::dwViewMatrix);
}

D3DXVECTOR3 LocalPlayer::getLocalViewAngles()
{
	return rpm<D3DXVECTOR3>(clientState + offs::dwClientState_ViewAngles);
}

void LocalPlayer::setLocalViewAngles(D3DXVECTOR3 angles)
{
	wpm<D3DXVECTOR3>(angles, clientState + offs::dwClientState_ViewAngles);
}

D3DXVECTOR3 LocalPlayer::getLocalPunchAngles()
{
	return rpm<D3DXVECTOR3>(LocalPlayer::getLocalPlayer() + netvars::m_aimPunchAngle);
}