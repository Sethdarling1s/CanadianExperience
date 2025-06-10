/**
 * @file ActualMachineSystem.cpp
 * @author Seth Darling
 *
 * System that manages and calls functions on machines.
 */

#include "pch.h"
#include "ActualMachineSystem.h"

/**
* Set the machine number
* @param machine An integer number. Each number makes a different machine
*/
void ActualMachineSystem::SetMachineNumber(int machine)
{
	if (mMachine != nullptr)
	{
		mMachine->SetNumber(machine);
	}

	switch (machine)
	{
		case 1:
		{
			MachineOneFactory factory = MachineOneFactory(mResourcesDir, mAudioEngine);
			mMachine = factory.CreateMachineOne();
			mMachine->SetNumber(1);
			break;
		}

		case 2:
		{
			MachineTwoFactory factory = MachineTwoFactory(mResourcesDir, mAudioEngine);
			mMachine = factory.CreateMachineTwo();
			mMachine->SetNumber(2);
			break;
		}
	}
}
