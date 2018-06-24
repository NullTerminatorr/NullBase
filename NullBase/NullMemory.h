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

#pragma  once
#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <string>
#include "Offsets.hpp"

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

class nullbase
{
public:

	nullbase();
	~nullbase();

	//Vars to use
	DWORD baseAddress;

	//Vars for process snapshot
	HANDLE hProcSnap;
	HANDLE hProc;
	PROCESSENTRY32 procEntry32;

	//Vars for module snapshot
	HANDLE hModuleSnap;
	MODULEENTRY32 modEntry32;

	//Process ID of attached proc
	DWORD pID;

	//Attaches to process and gives ALL_ACCESS so you can rpm/wpm for your hack
	bool attatchProc(char* procName);

	//Gets the base address of a desired module within the process you've attached to, so you can offset from it
	DWORD getModule(char* moduleName);

	uintptr_t patternScan(char* base, size_t size, char* pattern);

	//WPM wrapper - Lets us call WriteProcessMemory MUCH more easily (with less args)
	template <class dataType>
	void wpm(dataType valToWrite, DWORD addressToWrite)
	{
		WriteProcessMemory(hProc, (PVOID)addressToWrite, &valToWrite, sizeof(dataType), 0);
	}

	//RPM wrapper - Lets us call ReadProcessMemory MUCH more easily (with less args)
	template <class dataType>
	dataType rpm(DWORD addressToRead)
	{
		//Stores the value of the address being read
		dataType rpmBuffer;

		//RPM
		ReadProcessMemory(hProc, (PVOID)addressToRead, &rpmBuffer, sizeof(dataType), 0);

		//Return the value that was read
		return rpmBuffer;
	}

	//Localplayer return functions
	DWORD	getLocalPlayer();												//Get the local player base address
	int		getLocalFlags();												//Get the local player flags
	int		getLocalHealth();												//Get the local player health
	int		getLocalCrossID();												//Get the local player crosshair ID
	int		getLocalTeam();													//Get the local player team ID

	//Void functions 
	void	forceJump();													//Force the local player to jump
	void	setSpotted(DWORD playerBase, bool val);							//Set the spotted bool (Red dot on radar, its a bool so True (1) = Spotted and False (0) = Not spotted)
	///WIP
	void	glowEsp(DWORD glowObj, int glowInd, 
					float r, float g, float b, float a);				    //Sets the glow on desired object with given colour

	//Entity return functions
	DWORD	getEntBase(int index);											//Get the base address of the entity at provided index
	bool	isAlive(DWORD playerBase);										//Check if entity is alive 
	bool	isValid(DWORD playerBase);										//Checks if entity is a player
	int		getEntHp(DWORD playerBase);										//Return the health of the entity
	int		getEntTeam(DWORD playerBase);										//Get the team ID of the entity
	bool	getSpotted(DWORD playerBase);									//Get the spotted bool (Red dot on radar, its a bool so 1 = Spotted and 0 = Not spotted)
	/// WIP
	int		getGlowIndex(DWORD playerBase);									//Get the glow index of the entity
	DWORD	getGlowObj();													//Get the pointer to glow object

};
