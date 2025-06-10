/**
 * @file MachineDrawable.h
 * @author Seth Darling
 *
 * Adapter class for machine system
 */

#ifndef CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINEDRAWABLE_H
#define CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINEDRAWABLE_H

#include <machine-api.h>
#include <string>
#include <memory>
#include "Drawable.h"

class ma_engine;

/**
 * Adapter class for Machine System
 *
 * Allows for machine to be drawn in Canadian Experience
 */
class MachineDrawable : public Drawable
{
private:
	/// Machine system object being adapted
	std::shared_ptr<MachineSystem> mMachineSystem;
	/// Directory used for images and audio
	std::wstring mResourcesDir;
	/// Audio engine used for sound
	ma_engine *mAudioEngine;
	/// Timeline for machine drawable
	Timeline *mTimeline;
	/// Frame to start playing machine
	int mStartFrame = 0;
public:
	MachineDrawable(std::wstring name, std::wstring resourcesDir, ma_engine *audioEngine);
	/**
	 * Sets machine in machine system to passed number
	 * @param number machine number to set machine to
	 */
	void SetMachineNumber(int number) { mMachineSystem->SetMachineNumber(number);}

	/**
	 * Set the location of machine
	 * @param location New location
	 */
	void SetCenter(wxPoint location) { mMachineSystem->SetLocation(location); }

	/**
	 * Get the location of machine
	 * @return location
	 */
	wxPoint GetCenter() { return mMachineSystem->GetLocation(); }

	/**
	 * Sets frame for Machine to start playing
	 * @param frame new start frame
	 */
	void SetStartFrame(int frame) { mStartFrame = frame; }

	/**
	 * Getter for Machine Drawable start frame
	 * @return frame that Machine starts playing
	 */
	int GetStartFrame() { return mStartFrame; }

	void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

	bool HitTest(wxPoint pos) override;
	void SetTimeline(Timeline *timeline);
	std::shared_ptr<MachineDialog> CreateDialog(wxWindow *parent);

	void XmlSave(wxXmlNode* root);
	void XmlLoad(wxXmlNode* node);

	/**
	 * Override SetKeyframe to avoid crash
	 */
	void SetKeyframe() override {}
	/**
	 * Override GetKeyframe to avoid crash
	 */
	void GetKeyframe() override {}
};

#endif //CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINEDRAWABLE_H
