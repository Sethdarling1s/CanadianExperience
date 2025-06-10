/**
 * @file Machine.cpp
 * @author Seth Darling
 *
 * Class that represents musical machine object
 */

#include "pch.h"
#include "Machine.h"



/**
 * Draws all components of machine at location
 * @param graphics graphics context used to draw machine
 * @param location where to draw the machine
 */
void Machine::Draw(std::shared_ptr<wxGraphicsContext> graphics, wxPoint location)
{
	//graphics->DrawText("Hi", 100, 100);

	for(auto component : mComponents)
	{
		component->Draw(graphics, location);
	}
}

/**
 * Adds Component to Machine
 * @param component Component to be added to Machine
 */
void Machine::AddComponent(std::shared_ptr<Component> component)
{
	mComponents.push_back(component);
	component->SetMachine(this);
}

/**
 * Constructor for Machine
 * @param resourcesDir directory used for image and audio files
 */
Machine::Machine(std::wstring resourcesDir)
{

}

/**
 * Sets current time of machine
 * @param time to set mTime to
 */
void Machine::SetTime(double time)
{

	for (auto component : mComponents)
	{
		component->Update(time);
	}
	mTime = time;
}
