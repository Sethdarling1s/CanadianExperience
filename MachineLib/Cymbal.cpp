/**
 * @file Cymbal.cpp
 * @author Seth Darling
 *
 * Struck Instrument that is a cymbal
 */

#include "pch.h"
#include "Cymbal.h"

/// Cymbal base image
const std::wstring CymbalBaseImage = L"/images/cymbal-stand.png";

/// Cymbal image
const std::wstring CymbalImage = L"/images/cymbal.png";

/// Cymbal Sound
const std::wstring CymbalSound = L"/audio/cymbal.wav";

/// Cymbal Offset
const int CymbalOffset = 25;

/// How long the rocking lasts in seconds
const double RockingTime = 2.0;

/// Maximum amount to rock in unit rotations
const double RockAmount = 0.03;

/// How quickly to rock in radians per second
const double RockRate = M_PI * 4;

/**
 * Constructor for cymbal
 * @param resourcesDir directory used for image and audio files
 * @param audioEngine audio engine used to play sounds
 */
Cymbal::Cymbal(std::wstring resourcesDir, ma_engine *audioEngine) :
StruckInstrument(resourcesDir, audioEngine, CymbalSound, CymbalBaseImage)
{
	mCymbal.SetImage(resourcesDir + CymbalImage);
	mCymbal.Rectangle(-mCymbal.GetImageWidth() / 2, +mCymbal.GetImageHeight()/2);
}

/**
 * Updates Cymbal to have same time as Machine
 * Handles Cymbal movement
 * @param time current time of Machine
 */
void Cymbal::Update(double time)
{
	double adjustedRockRate = RockRate * (mShakeTime - time) /20;

	if (mShakeTime > GetTime())
	{
		if (abs(mCymbal.GetRotation() + adjustedRockRate * (time - GetTime()) * mShakeDirection) >= RockAmount)
		{
			mCymbal.SetRotation((RockAmount*mShakeDirection));
			mShakeDirection = -mShakeDirection;
		}
		else
		{
			mCymbal.SetRotation(mCymbal.GetRotation() + adjustedRockRate * (time - GetTime()) * mShakeDirection);
		}

	}
	else
	{
		double cymbalRestRotation = 0;
		mCymbal.SetRotation(cymbalRestRotation);
	}
	StruckInstrument::Update(time);
}

/**
 * Plays Sound and makes Cymbal rock
 */
void Cymbal::PlaySound()
{
	Instrument::PlaySound();
	mShakeTime = GetTime() + RockingTime;
}

/**
 * Draws Cymbal
 * @param graphics Graphics Context object used to draw Cymbal
 * @param location location of Machine
 */
void Cymbal::Draw(std::shared_ptr<wxGraphicsContext> graphics, wxPoint location)
{
	StruckInstrument::Draw(graphics, location);
	mCymbal.DrawPolygon(graphics, location.x + GetLocation().x -5, location.y + GetLocation().y + CymbalOffset);
}

/**
 * Sets location of cymbal
 * @param location location of Machine
 */
void Cymbal::SetLocation(wxPoint location)
{
	Shape::SetLocation(location);
}
