/**
 * @file MachineOneFactory.h
 * @author Seth Darling
 *
 * Factory for machine one
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_MACHINEONEFACTORY_H
#define CANADIANEXPERIENCE_MACHINELIB_MACHINEONEFACTORY_H

#include <memory>

class Machine;
struct ma_engine;

/**
 * Factory for machine one
 */
class MachineOneFactory
{
private:
	/// The resources directory
	std::wstring mResourcesDir;

	/// The miniaudio engine
	ma_engine* mAudioEngine;

public:
	MachineOneFactory(std::wstring resourcesDir, ma_engine* audioEngine);

	// Do not change the return type for CreateMachineSystem!
	std::shared_ptr<Machine> CreateMachineOne();
};

#endif //CANADIANEXPERIENCE_MACHINELIB_MACHINEONEFACTORY_H
