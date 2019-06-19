#pragma once

#include <windows.h>

//Just for vector and matrix shit (im lazy)
#include <d3d9.h>
#include <d3dx9.h>

namespace LocalPlayer
{
	//Localplayer return functions
	extern DWORD			getLocalPlayer();												//Get the local player base address
	extern void				setLocalPlayer();												//Set the local player base address
	extern int				getLocalFlags();												//Get the local player flags
	extern int				getLocalHealth();												//Get the local player health
	extern int				getLocalCrossID();												//Get the local player crosshair ID
	extern int				getLocalTeam();													//Get the local player team ID
	extern D3DXVECTOR3		getLocalPos();													//Get the local player pos
	extern D3DXMATRIX		getViewMatrix();												//Get the view matrix

																							//Void functions 
	extern void				forceJump();													//Force the local player to jump
	extern bool				isScoped();														//Check if local player is in scoped mode

	extern DWORD			LocalBaseaddress;												//Localplayer base address
}