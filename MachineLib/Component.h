/**
 * @file Component.h
 * @author Seth Darling
 *
 * Most basic type of object that makes up a machine
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_COMPONENT_H
#define CANADIANEXPERIENCE_MACHINELIB_COMPONENT_H

class Machine;

/**
 * Most basic type of object that makes up a machine
 *
 * Abstract Class
 */
class Component
{

private:
	/// Time of component
	double mTime = 0;
	/// Current frame of component
	//int mFrame = 0;
	/// The resources directory
	std::wstring mResourcesDir;
	/// Machine this component belongs to
	Machine *mMachine = nullptr;

public:
	/**
	 * Getter for time of component
	 * @return mTime
	 */
	double GetTime() { return mTime; }

	/**
	 * Setter for time of component
	 * @param time time to set mTime to
	 */
	void SetTime(double time) { mTime = time; }

	/**
	 * Pure virtual function to draw component
	 * @param graphics Graphics Context object used to draw Component
	 * @param location location of Machine
	 */
	virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics, wxPoint location)=0;

	/**
	 * Sets machine this component belongs to
	 * @param machine machine that owns component
	 */
	void SetMachine(Machine *machine) { mMachine = machine; }

	/**
	 * Pure virtual function to update time of component
	 * @param time current time of Machine
	 */
	virtual void Update(double time)=0;

	/**
	 * Sets directory used for resources
	 * @param resourcesDir
	 */
	void SetDirectory(std::wstring resourcesDir) { mResourcesDir = resourcesDir; }
};

#endif //CANADIANEXPERIENCE_MACHINELIB_COMPONENT_H
