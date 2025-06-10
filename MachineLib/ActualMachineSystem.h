/**
 * @file ActualMachineSystem.h
 * @author Seth Darling
 *
 * System that manages and calls functions on machines.
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_ACTUALMACHINESYSTEM_H
#define CANADIANEXPERIENCE_MACHINELIB_ACTUALMACHINESYSTEM_H

#include "MachineSystem.h"
#include "Machine.h"
#include "MachineOneFactory.h"
#include "MachineTwoFactory.h"

struct ma_engine;

/**
 * System that manages and calls functions on machines.
 */
class ActualMachineSystem : public MachineSystem
{
private:
	/// Location of current machine
	wxPoint mMachineLocation;
	/// Location of image and sound files
	std::wstring mResourcesDir;
	/// Current time of machine
	double mTime = 0;
	/// Audio engine used to play sounds
	ma_engine* mAudioEngine;
	/// Machine currently being displayed
	std::shared_ptr<Machine> mMachine;
public:
	/**
	 * Default constructor
	 */
	ActualMachineSystem(){}

	/**
	 * Sets resources directory to passed directory
	 * @param resourcesDir directory for Actual Machine System to use
	 */
	void SetDirectory(std::wstring resourcesDir) { mResourcesDir = resourcesDir; }

	/**
	 * Sets audio engine
	 * @param engine ma_engine for use by Actual Machine Sytem
	 */
	void SetAudioEngine(ma_engine *engine) { mAudioEngine = engine; }

	/**
    * Set the position for the root of the machine
    * @param location The x,y location to place the machine
    */
	void SetLocation(wxPoint location) override { mMachineLocation = location; }

	/**
	 * Get the location of hte machine
	 * @return Location x,y in pixels as a point
	 */
	wxPoint GetLocation() override { return mMachineLocation; }

	/**
	* Draw the machine at the currently specified location
	* @param graphics Graphics object to render to
	*/
	void DrawMachine(std::shared_ptr<wxGraphicsContext> graphics) override { mMachine->Draw(graphics, mMachineLocation); }

	/**
	 * Set the current machine animation frame
	 * @param frame Frame number
	 */
	void SetMachineFrame(int frame) override { mMachine->SetTime(frame/mMachine->GetFramerate()); }

	/**
	 * Set the expected frame rate in frames per second
	 * @param rate Frame rate in frames per second
	 */
	void SetFrameRate(double rate) override { mMachine->SetFramerate(rate); }


	void SetMachineNumber(int machine) override;

	/**
	 * Get the current machine number
	 * @return Machine number integer
	 */
	int GetMachineNumber() override { return mMachine->GetNumber(); }

	/**
	 * Get the current machine time.
	 * @return Machine time in seconds
	 */
	double GetMachineTime() override { return mMachine->GetTime(); }
};

#endif //CANADIANEXPERIENCE_MACHINELIB_ACTUALMACHINESYSTEM_H
