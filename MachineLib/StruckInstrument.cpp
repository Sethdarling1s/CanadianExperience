/**
 * @file StruckInstrument.cpp
 * @author Seth Darling
 *
 * Instrument that can be struck by a cylinder
 */

#include "pch.h"
#include "StruckInstrument.h"

/**
 * Updates Struck Instrument's time
 * @param time current time of Machine
 */
void StruckInstrument::Update(double time)
{
	SetPlayed(false);
	SetTime(time);
}

/**
 * Draws Struck Instrument
 * @param graphics Graphics Context object used to draw Struck Instrument
 * @param location location of Machine
 */
void StruckInstrument::Draw(std::shared_ptr<wxGraphicsContext> graphics, wxPoint location)
{
	Instrument::Draw(graphics, location);
}

/**
 * Constructor for Struck Instrument
 * @param resourcesDir Directory used for image and audio files
 * @param audioEngine Audio Engine used to play sounds
 * @param sound Audio file for use by Struck Instrument
 * @param image image file for Struck Instrument
 */
StruckInstrument::StruckInstrument(std::wstring resourcesDir,
								   ma_engine *audioEngine,
								   std::wstring sound,
								   std::wstring image) : Instrument(resourcesDir, audioEngine, sound)
{
	SetImage(resourcesDir + image);
	Rectangle(-GetWidth() / 2, GetHeight(), GetWidth());
}
