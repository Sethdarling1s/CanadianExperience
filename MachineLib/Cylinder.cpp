/**
 * @file Cylinder.cpp
 * @author Seth Darling
 *
 * Cylinder that is connected to an air sink and strikes a struck instrument.
 */

#include "pch.h"
#include "Cylinder.h"

/// Cylinder base image
const std::wstring CylinderBaseImage = L"/images/cylinder-base.png";

/// Cylinder body image
const std::wstring CylinderBodyImage = L"/images/cylinder.png";

/// Cylinder ram image
const std::wstring CylinderRamImage = L"/images/cylinder-ram.png";

/// Angle from bottom center of the cylinder to the tubing connector
const double ConnectorAngle = -0.17;

/// Distance from bottom center of the cylinder to the tubing connector
const double ConnectorDistance = 24.5;

/// Time for Cylinder to extend
const double ExtensionTime = .25;

/**
 * Called by air sink causing cylinder to strike.
 * @param air pressure sent from air sink
 */
void Cylinder::ReceiveAir(double air)
{
	if (mExtensionTime < GetTime())
	{
		mStruckInstrument->PlaySound();
		mExtensionTime = GetTime() + ExtensionTime;
		mIsExtended = true;
	}

	double airX = GetLocation().x + cos(ConnectorAngle * M_PI * 2) * ConnectorDistance;
	double airY = GetLocation().x + sin(ConnectorAngle * M_PI * 2) * ConnectorDistance;
}

/**
 * Constructor for Cylinder
 * @param resourcesDir directory used for image and audio files
 * @param extensionLength Amount of length Cylinder extends to
 * @param angle rotation of Cylinder
 */
Cylinder::Cylinder(std::wstring resourcesDir, int extensionLength, double angle) : mExtensionLength(extensionLength), mAngle(angle*2*3.14159)
{

	mBase.SetImage(resourcesDir + CylinderBaseImage);
	mBase.Rectangle(-mBase.GetImageWidth() / 2, 0);
	mBase.SetRotation(mAngle/(2*3.14159));

	mCylinder.SetImage(resourcesDir + CylinderBodyImage);
	mCylinder.Rectangle(-mCylinder.GetImageWidth() / 2, 0);
	mCylinder.SetRotation(mAngle/(2*3.14159));

	mRam.SetImage(resourcesDir + CylinderRamImage);
	mRam.Rectangle(-mCylinder.GetImageWidth() / 2, 0);
	mRam.SetRotation(mAngle/(2*3.14159));
}

/**
 * Updates Cylinder to be extended or not and sets time
 * @param time current time of machine
 */
void Cylinder::Update(double time)
{
	SetTime(time);
	if (mExtensionTime <= GetTime())
	{
		mIsExtended = false;
	}

}

/**
 * Draws Cylinder
 * @param graphics Graphics Context used to draw Cylinder
 * @param location Location of machine
 */
void Cylinder::Draw(std::shared_ptr<wxGraphicsContext> graphics, wxPoint location)
{
	mBase.DrawPolygon(graphics, location.x + GetLocation().x, location.y + GetLocation().y);
	if(mIsExtended)
	{
		mRam.DrawPolygon(graphics, location.x + GetLocation().x + sin(mAngle)*mExtensionLength, location.y + GetLocation().y - cos(mAngle)*mExtensionLength);
	}
	else
	{
		mRam.DrawPolygon(graphics, location.x +GetLocation().x, location.y + GetLocation().y);
	}
	mCylinder.DrawPolygon(graphics, location.x + GetLocation().x, location.y + GetLocation().y);

}

