/**
 * @file MachineSystemFactory.cpp
 *
 * @author Charles Owen
 *
 * You are allowed to change this file.
 */

#include "pch.h"
#include "MachineSystemFactory.h"
#include "MachineSystem.h"
#include "ActualMachineSystem.h"
#include <string>
#include <wx/stdpaths.h>

using namespace std;

/**
 * Constructor
 * @param resourcesDir Directory to load resources from
 * @param audioEngine The miniaudio engine to use
 */
MachineSystemFactory::MachineSystemFactory(std::wstring resourcesDir, ma_engine* audioEngine) :
    mResourcesDir(resourcesDir), mAudioEngine(audioEngine)
{
}


/**
 * Create a machine system object
 *
 * Do not change the return type of this function!
 *
 * @return Object of type MachineSystem
 */
std::shared_ptr<MachineSystem> MachineSystemFactory::CreateMachineSystem()
{
    std::shared_ptr<ActualMachineSystem> machineSystem = std::make_shared<ActualMachineSystem>();
	machineSystem->SetDirectory(mResourcesDir);
	machineSystem->SetAudioEngine(mAudioEngine);
	machineSystem->SetMachineNumber(1);
	return machineSystem;
}


