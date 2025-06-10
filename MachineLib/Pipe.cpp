/**
 * @file Pipe.cpp
 * @author Seth Darling
 *
 * A pipe is a type of instrument that makes sound and smoke.
 */

#include "pch.h"
#include "Pipe.h"

/// The pipe base image
const std::wstring PipeBaseImage = L"/images/pipe-base.png";

/// The pipe image
const std::wstring PipeImage = L"/images/pipe.png";

/// The pipe top image
const std::wstring PipeTopImage = L"/images/pipe-top.png";

/// The pipe puff image
const std::wstring PuffImage = L"/images/puff.png";

/// Pipe images width in pixels
const int PipeWidth = 20;

/// Pipe base height
const int PipeBaseHeight = 20;

/// Puff image width in pixels
const int PuffWidth = 65;

/// Time to display Smoke
const double PuffTime = .3333;

/**
 * Draws Pipe
 * @param graphics Graphics Context object used to draw pipe
 * @param location location of Machine
 */
void Pipe::Draw(std::shared_ptr<wxGraphicsContext> graphics, wxPoint location)
{
	mBase.DrawPolygon(graphics, location.x + GetLocation().x, location.y + GetLocation().y);
	mPipe.DrawPolygon(graphics, location.x + GetLocation().x, location.y + GetLocation().y);
	if (mShowSmoke)
	{
		mPuff.DrawPolygon(graphics, location.x + GetLocation().x, location.y + GetLocation().y);
	}
	mTop.DrawPolygon(graphics, location.x + GetLocation().x, location.y + GetLocation().y);

}

/**
 * Updates time of Pipe and if it should display smoke
 * @param time time of machine
 */
void Pipe::Update(double time)
{

	if (time < GetTime())
	{
		mDisplaySmoke = 0;
		SetPlayed(false);
		mShowSmoke = false;
	}
	SetTime(time);
	if (mDisplaySmoke < GetTime())
	{
		mShowSmoke = false;
		SetPlayed(false);
	}

	//SetTime(time);
}

/**
 * Plays sound associated with this pipe
 */
void Pipe::PlaySound()
{
	Instrument::PlaySound();
}

/**
 * Constructor for Pipe
 * @param resourcesDir directory used for image and audio files
 * @param audioEngine audio engine used to play sound
 * @param sound audio file used for Pipe's sound
 * @param length Length of pipe in pixels
 */
Pipe::Pipe(std::wstring resourcesDir, ma_engine *audioEngine, std::wstring sound, double length) :
Instrument(resourcesDir, audioEngine, sound)
{
	mBase.SetImage(resourcesDir + PipeBaseImage);
	mBase. Rectangle(-PipeWidth / 2, 0, PipeWidth, PipeWidth);

	// Polygons for the other components
	mPipe.SetImage(resourcesDir + PipeImage);
	mPipe.Rectangle(-PipeWidth / 2, -PipeBaseHeight, PipeWidth, length);

	mTop.SetImage(resourcesDir + PipeTopImage);
	mTop.Rectangle(-PipeWidth / 2, -PipeBaseHeight - length, PipeWidth);

	mPuff.SetImage(resourcesDir + PuffImage);
	mPuff.Rectangle(-PuffWidth / 2, -PipeBaseHeight - length, PuffWidth);
}

/**
 * Plays sound when called by Air Sink connected to Pipe
 * @param air Pressure of air received
 */
void Pipe::ReceiveAir(double air)
{
	if(!GetPlayed())
	{
		PlaySound();
		mShowSmoke = true;
		mDisplaySmoke = GetTime() + PuffTime;
	}
	SetPlayed(true);
}
