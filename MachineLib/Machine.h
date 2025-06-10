/**
 * @file Machine.h
 * @author Seth Darling
 *
 * Class that represents musical machine object
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_MACHINE_H
#define CANADIANEXPERIENCE_MACHINELIB_MACHINE_H

#include <vector>
#include "Component.h"
#include "Polygon.h"
#include "Shape.h"

struct ma_engine;


/**
 * Class that represents musical machine object
 */
class Machine
{
private:
	/// Machine Number
	int mNumber = 0;
	/// Time
	double mTime = 0;
	/// Location of machine
	wxPoint mLocation = wxPoint(0, 0);
	/// Framerate of machine
	double mFramerate =30;
	/// Number of current frame
	int mFrame = 0;
	/// Directory used to load images and sounds
	std::wstring mResourceDir;
	/// Audio engine used to play sounds
	ma_engine* mAudioEngine;
	/// Components that make up machine
	std::vector<std::shared_ptr<Component>> mComponents;

public:
	/** Default Constructor delete**/
	Machine() = delete;
	/** Constructor*/
	Machine(std::wstring resourcesDir);
	/** Copy constructor disabled */
	Machine(const Machine &) = delete;
	/** Assignment operator disabled */
	void operator=(const Machine &) = delete;

	void Draw(std::shared_ptr<wxGraphicsContext> graphics, wxPoint location);

	void AddComponent(std::shared_ptr<Component> component);

	/**
	 * Gets number of machine
	 * @return number of machine as int
	 */
	int GetNumber() { return mNumber; }

	/**
	 * Sets machine number
	 * @param number that mNumber will be set to
	 */
	void SetNumber(int number) { mNumber = number; }

	/**
	 * Gets current frame of machine
	 * @return current frame as int
	 */
	int GetFrame() { return mFrame; }

	void SetTime(double time);

	/**
	 * Sets framerate of machine
	 * @param framerate framerate to set machine to
	 */
	void SetFramerate(double framerate) { mFramerate = framerate; }

	/**
	 * Gets framerate of machine
	 * @return framerate as double, frames per second
	 */
	double GetFramerate() { return mFramerate; }

	/**
	 * Getter for time of Machine
	 * @return time of Machine
	 */
	double GetTime() { return mTime; }
};

#endif //CANADIANEXPERIENCE_MACHINELIB_MACHINE_H
