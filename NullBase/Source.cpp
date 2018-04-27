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

#include "NullMemory.h"

//Vars for our cheat :D
DWORD plrBase;
int plrFlags;

int main()
{
	//Constructing nullbase object to access the functions/vars inside
	nullbase null;

	//if we successfully attach to csgo
	if (null.attatchProc("csgo.exe"))
	{
		//if we successfully get the base address of client.dll and assign it to baseAddress
		if (null.baseAddress = null.getModule("client.dll"))
		{
			//While F10 isn't pressed (F10 = Panic key :D)
			while (!GetAsyncKeyState(VK_F10))
			{
				//if we're on the ground and the spacebar is pressed (want to bhop)
				if (null.getLocalFlags() == FL_ON_GROUND && GetAsyncKeyState(VK_SPACE))
				{
					//JUMP
					null.forceJump();
				}
			}
		}
	}

}