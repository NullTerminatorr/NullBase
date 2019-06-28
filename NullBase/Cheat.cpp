////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* Copyright 2018 Null Terminator																								  //
//
Permission is hereby granted, free of charge, to any person																		  //
obtaining a copy of this software and associated documentation                                                                    //
files(the "Software"), to deal in the Software without restriction,                                                               //
including without limitation the rights to use, copy, modify, merge,                                                              //
publish, distribute, sublicense, and/or sell copies of the Software,                                                              //
and to permit persons to whom the Software is furnished to do so,                                                                 //
subject to the following conditions :                                                                                             //
																																  //
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.    //
																																  //
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,																	  //
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF																  //
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.                                                            //
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,                                                       //
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR                                                             //
OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR                                                             //
THE USE OR OTHER DEALINGS IN THE SOFTWARE.																						  //
*/																																  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
NEED SOME HELP? FULL TUTORIALS ON HOW TO USE THIS BASE AND CODE CHEATS ON MY YOUTUBE CHANNEL:
Null Terminator
https://www.youtube.com/channel/UCZF93Qrt6yMAabRnlND4YsQ

STAY UPDATED ON THIS PROJECT AS IT IS A WORK IN PROGRESS
GITHUB LINK:
https://github.com/NullTerminatorr/NullBase
*/

#include "Includes.h"

//Flags
#define FL_ON_GROUND                     257
#define FL_ON_GROUND_CROUCHED             263
#define FL_IN_AIR_STAND                    256
#define FL_IN_AIR_MOVING_TO_STAND         258
#define FL_ON_GROUND_MOVING_TO_STAND     259
#define FL_IN_AIR_MOVING_TO_CROUCH         260
#define FL_ON_GROUND_MOVING_TO_CROUCH     261
#define FL_IN_AIR_CROUCHED                 262
#define FL_IN_WATER                     1280
#define FL_IN_PUDDLE                     1281
#define FL_IN_WATER_CROUCHED             1286
#define FL_IN_PUDDLE_CROUCHED             1287
#define FL_PARTIALGROUND (1 << 18)

//Team IDs
#define TEAM_ID_GOTV 1
#define TEAM_ID_T 2
#define TEAM_ID_CT 3


DWORD findPlayer()
{
	D3DXVECTOR3 w2sHead;

	DWORD plrToAim = NULL;
	double lowestDist = 9999;

	for (int i = 1; i < 32; i++)
	{
		auto base = Entity::getEntBase(i);


		/*AIMBOT*/
		if (Entity::getEntTeam(base) != LocalPlayer::getLocalTeam() && Entity::isValid(base))
		{
			if (!Entity::getEntImmunity(base))
			{
				WorldToScreen(Entity::getEntBonePos(base, 8), w2sHead, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));

				double dist = sqrt(pow((GetSystemMetrics(SM_CXSCREEN) / 2) - w2sHead.x, 2) + pow((GetSystemMetrics(SM_CYSCREEN) / 2) - w2sHead.y, 2));

				if (dist < lowestDist)
				{
					lowestDist = dist;
					plrToAim = base;
				}
			}
		}
	}

	return plrToAim;
}

void aimbot(DWORD playerToAimAt)
{
	if (playerToAimAt != NULL)
	{
		//If the player is spotted (visible) and left click is pressed (Can be changed to whatever button you want!)
		if (Entity::getSpotted(playerToAimAt) == 1 && GetAsyncKeyState(VK_LBUTTON))
		{
			D3DXVECTOR3 aimAngles = CalcAngle(LocalPlayer::getLocalPos(), Entity::getEntPos(playerToAimAt));

			aimAngles -= LocalPlayer::getLocalPunchAngles() * 2.0;

			LocalPlayer::setLocalViewAngles(aimAngles);
		}
	}
}

void bhop()
{
	//If we're holding space and the we're on the ground
	if (GetAsyncKeyState(VK_SPACE) && LocalPlayer::getLocalFlags() == FL_ON_GROUND)
	{
		//Jump!
		LocalPlayer::forceJump();
	}
}

int main()
{
	init();
	LocalPlayer::setLocalPlayer();
	
	while (!GetAsyncKeyState(VK_F10))
	{
		aimbot(findPlayer());

		bhop();

		Sleep(1);
	}

	//Close handle to csgo.exe to prevent memory leaks
	CloseHandle(hProc);
}
