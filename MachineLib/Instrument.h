/**
 * @file Instrument.h
 * @author Seth Darling
 *
 * Shape that can play sounds
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_INSTRUMENT_H
#define CANADIANEXPERIENCE_MACHINELIB_INSTRUMENT_H

#include "Shape.h"
#include "Polygon.h"
#include <string>
#include <miniaudio.h>

struct ma_engine;

/**
 * Class that describes instruments, a type of shape
 *
 * Instruments are an abstract base class that specific
 * types of instruments derive from.
 */
class Instrument : public Shape
{
private:
	/// File for sound made by instrument
	ma_sound mSound;
	/// Audio engine used to play sounds
	ma_engine* mAudioEngine;
	/// Polygon for instrument image
	cse335::Polygon mImage;
	/// If Instrument has just played a sound
	bool mHasPlayed = false;

protected:
	Instrument(std::wstring resourcesDir, ma_engine *audioEngine, std::wstring sound);

public:
	virtual void PlaySound();

	/**
	 * Sets time of Instrument
	 * @param time current time of Machine
	 */
	virtual void Update(double time) { SetTime(time);}
	~Instrument();

	/**
	 * Gets pointer to audio engine
	 * @return mAudioEngine
	 */
	ma_engine* GetAudioEngine() { return mAudioEngine; }

	/**
	 * Setter for if instrument has just played a sound
	 * @param hasPlayed bool value to set mHasPlayed to
	 */
	void SetPlayed(bool hasPlayed) { mHasPlayed = hasPlayed; }

	/**
	 * Getter for if instrument has just made a sound
	 * @return mHasPlayed
	 */
	bool GetPlayed() { return mHasPlayed; }

	/**
	 * Sets image of polygon
	 * @param image image file to set base polygon to
	 */
	void SetImage(std::wstring image) { mImage.SetImage(image); }

	/**
	 * Sets rectangle of polygon
	 * @param x x position of rectangle
	 * @param y y position of rectangle
	 * @param width width of rectangle
	 * @param height height of rectangle
	 */
	void Rectangle(int x, int y, int width=0, int height=0) { mImage.Rectangle(x, y, width, height);}

	/**
	 * Getter for width of rectangle
	 * @return width of rectangle
	 */
	int GetWidth() { return mImage.GetImageWidth();}

	/**
	 * Getter for height of rectangle
	 * @return Height of rectangle
	 */
	int GetHeight() { return mImage.GetImageHeight();}

	/**
	 * Draws polygon of instrument
	 * @param graphics Graphics Context object used to draw instrument
	 * @param location location of machine
	 */
	void Draw(std::shared_ptr<wxGraphicsContext> graphics, wxPoint location) override { mImage.DrawPolygon(graphics, location.x + GetLocation().x, location.y + GetLocation().y);};

	/**
	 * Sets audio engine of instrument
	 * @param audioEngine pointer to ma_engine
	 */
	void SetAudioEngine(ma_engine *audioEngine) { mAudioEngine = audioEngine; }
};

#endif //CANADIANEXPERIENCE_MACHINELIB_INSTRUMENT_H
