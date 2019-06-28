#pragma once

#include <windows.h>

//Just for vector and matrix shit (im lazy)
#include <d3d9.h>
#include <d3dx9.h>

namespace LocalPlayer
{
	//Localplayer return functions
	extern DWORD			getLocalPlayer();												//Get the local player base address
	extern int				getLocalFlags();												//Get the local player flags
	extern int				getLocalHealth();												//Get the local player health
	extern int				getLocalCrossID();												//Get the local player crosshair ID
	extern int				getLocalTeam();													//Get the local player team ID
	extern D3DXVECTOR3		getLocalPos();													//Get the local player pos
	extern D3DXMATRIX		getLocalViewMatrix();											//Get the view matrix
	extern D3DXVECTOR3		getLocalViewAngles();											//Get the local player view angles
	extern D3DXVECTOR3		getLocalPunchAngles();											//Get the local player punch angles (recoil)

																							//Void functions 
	extern void				forceJump(int waitTime = 35);									//Force the local player to jump
	extern void				setLocalPlayer();												//Set the local player base address
	extern void				setLocalViewAngles(D3DXVECTOR3 angles);							//Set the local player view angles

	extern DWORD			LocalBaseaddress;												//Localplayer base address
}