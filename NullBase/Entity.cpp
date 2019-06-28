#include <windows.h>
#include "NullMemory.h"
#include "Entity.h"
#include "Offsets.hpp"

DWORD Entity::getEntBase(int index)
{
	return rpm<DWORD>(baseAddress + offs::dwEntityList + (index * 0x10));
}

int	Entity::getEntHp(DWORD playerBase)
{
	return rpm<int>(playerBase + netvars::m_iHealth);
}

bool Entity::isAlive(DWORD playerBase)
{
	if (getEntHp(playerBase) > 0 && getEntHp(playerBase) <= 100)
		return true;
	return false;
}

int	Entity::getEntTeam(DWORD playerBase)
{
	return rpm<int>(playerBase + netvars::m_iTeamNum);
}

int Entity::getGlowIndex(DWORD playerBase)
{
	return rpm<int>(playerBase + netvars::m_iGlowIndex);
}

DWORD Entity::getGlowObj()
{
	return rpm<DWORD>(baseAddress + offs::dwGlowObjectManager);
}

bool Entity::isValid(DWORD playerBase)
{
	auto dormant = rpm<bool>(playerBase + offs::m_bDormant);
	if ((Entity::isAlive(playerBase) && Entity::getEntTeam(playerBase) != 0) && !dormant)
		return true;
	return false;
}

//TODO: MINIMISE WPM CALLS HERE BY USING A GLOW STRUCT 
void Entity::glowEsp(DWORD glowObj, int glowInd, float r, float g, float b, float a)
{
	wpm<float>(r / 255, (glowObj + ((glowInd * 0x38) + 0x4)));
	wpm<float>(g / 255, (glowObj + ((glowInd * 0x38) + 0x8)));
	wpm<float>(b / 255, (glowObj + ((glowInd * 0x38) + 0xC)));
	wpm<float>(a / 255, (glowObj + ((glowInd * 0x38) + 0x10)));
	wpm<bool>(true, (glowObj + ((glowInd * 0x38) + 0x24)));
	wpm<bool>(false, (glowObj + ((glowInd * 0x38) + 0x25)));
}

bool Entity::getSpotted(DWORD playerBase)
{
	return rpm<bool>(playerBase + netvars::m_bSpotted);
}

void Entity::setSpotted(DWORD playerBase, bool val)
{
	wpm<bool>(val, playerBase + netvars::m_bSpotted);
}

D3DXVECTOR3	Entity::getEntPos(DWORD playerBase)
{
	return rpm<D3DXVECTOR3>(playerBase + netvars::m_vecOrigin);
}

char* Entity::getEntName(DWORD playerBase)
{
	return rpm<char*>(playerBase + netvars::m_szCustomName);
}

DWORD Entity::getEntBoneMatrix(DWORD playerBase)
{
	return rpm<DWORD>(playerBase + netvars::m_dwBoneMatrix);
}

D3DXVECTOR3 Entity::getEntEyePos(DWORD playerBase)
{
	return ((Entity::getEntPos(playerBase)) + (rpm<D3DXVECTOR3>(playerBase + netvars::m_vecViewOffset)));
}

bool Entity::getEntScoped(DWORD playerBase)
{
	return rpm<bool>(playerBase + netvars::m_bIsScoped);
}

bool Entity::getEntDefusing(DWORD playerBase)
{
	return rpm<bool>(playerBase + netvars::m_bIsDefusing);
}

bool Entity::getEntReloading(DWORD playerBase)
{
	return rpm<bool>(playerBase + netvars::m_bInReload);
}

bool Entity::getEntHelmet(DWORD playerBase)
{
	return rpm<bool>(playerBase + netvars::m_bHasHelmet);
}

bool Entity::getEntDefuser(DWORD playerBase)
{
	return rpm<bool>(playerBase + netvars::m_bHasDefuser);
}

bool Entity::getEntImmunity(DWORD playerBase)
{
	return rpm<bool>(playerBase + netvars::m_bGunGameImmunity);
}

DWORD Entity::getActiveWeapon(DWORD playerBase)
{
	DWORD WeaponIndex = rpm<DWORD>(playerBase + netvars::m_hActiveWeapon) & 0xFFF;
	return rpm<DWORD>((baseAddress + offs::dwEntityList + WeaponIndex * 0x10) - 0x10);
}

//Uses ClassID
bool Entity::isWeaponNonAim(int classID)
{
	if (classID == CKnife || classID == CKnifeGG || classID == CFlashbang || classID == CHEGrenade || classID == CSmokeGrenade
		|| classID == CMolotovGrenade || classID == CDecoyGrenade || classID == CIncendiaryGrenade || classID == CC4)
		return true;
	return false;
}

//Uses iItemDefinitionIndex
bool Entity::isWeaponNonAim2(int iWeaponID)
{
	if (iWeaponID == weapon_knife || iWeaponID == weapon_knifegg || iWeaponID == weapon_flashbang || iWeaponID == weapon_hegrenade || iWeaponID == weapon_smokegrenade
		|| iWeaponID == weapon_molotov || iWeaponID == weapon_decoy || iWeaponID == weapon_c4 || iWeaponID == weapon_incgrenade)
		return true;
	return false;
}

//Uses ClassID
bool Entity::isWeaponPistol(int classID)
{
	if (classID == CDEagle || classID == CWeaponElite || classID == CWeaponFiveSeven || classID == CWeaponGlock
		|| classID == CWeaponP228 || classID == CWeaponUSP || classID == CWeaponTec9 || classID == CWeaponTaser || classID == CWeaponHKP2000 || classID == CWeaponP250)
		return true;

	return false;
}

//Uses ClassID
bool Entity::isWeaponSniper(int classID)
{
	if (classID == CWeaponAWP || classID == CWeaponSSG08 || classID == CWeaponG3SG1 || classID == CWeaponSCAR20)
		return true;

	return false;
}

int	Entity::getEntClassID(DWORD entity)
{
	int one = rpm<int>(entity + 0x8);
	int two = rpm<int>(one + 2 * 0x4);
	int three = rpm<int>(two + 0x1);
	return rpm<int>(three + 0x14);
}

D3DXVECTOR3	Entity::getEntBonePos(DWORD playerBase, int boneID)
{
	Matrix3x4_t boneMatrix = rpm<Matrix3x4_t>(Entity::getEntBoneMatrix(playerBase) + boneID * 0x30);

	return{
		boneMatrix.Matrix[0][3],
		boneMatrix.Matrix[1][3],
		boneMatrix.Matrix[2][3]
	};
}

int Entity::getEntAmmo(DWORD playerBase)
{
	auto weapon = Entity::getActiveWeapon(playerBase);
	return rpm<int>(weapon + netvars::m_iClip1);
}