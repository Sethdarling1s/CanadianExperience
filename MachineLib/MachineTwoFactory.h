/**
 * @file MachineTwoFactory.h
 * @author Seth Darling
 *
 * Factory used to create Machine Two
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_MACHINETWOFACTORY_H
#define CANADIANEXPERIENCE_MACHINELIB_MACHINETWOFACTORY_H

#include <memory>

class Machine;
struct ma_engine;

/**
 * Factory used to create Machine Two
 */
class MachineTwoFactory
{
private:
	/// The resources directory
	std::wstring mResourcesDir;

	/// The miniaudio engine
	ma_engine* mAudioEngine;
public:
	MachineTwoFactory(std::wstring resourcesDir, ma_engine* audioEngine);

	// Do not change the return type for CreateMachineSystem!
	std::shared_ptr<Machine> CreateMachineTwo();
};

#endif //CANADIANEXPERIENCE_MACHINELIB_MACHINETWOFACTORY_H
