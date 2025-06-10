/**
 * @file Tubing.cpp
 * @author Seth Darling
 *
 * Tubing that connects an air source to air sink
 */

#include "pch.h"
#include "Tubing.h"

/// Tubing thickness
const int TubeThickness = 3;

/**
 * Sends air through tubing's air source
 * @param pressure pressure to be sent
 */
void Tubing::ReceiveAir(double pressure)
{
	mSource->SendAir(pressure);
	mPressure = pressure;
}

/**
 * Draws Tubing as a bezier curve
 * @param graphics Graphics Context object used to draw Tubing
 * @param location location of Machine
 */
void Tubing::Draw(std::shared_ptr<wxGraphicsContext> graphics, wxPoint location)
{
	double bendIncrease = 1;
	if (mBends)
	{
		bendIncrease = 1 + mPressure;
	}

	for (int i = 0; i < mClamps.size()-1; i++)
	{
		auto p2x = location.x + mClamps[i].GetLocation().x - sin(mClamps[i].GetRotation() * M_PI * 2) * (mClamps[i].GetSpeed() * bendIncrease);
		auto p2y = location.y + mClamps[i].GetLocation().y + cos(mClamps[i].GetRotation() * M_PI * 2) * (mClamps[i].GetSpeed() * bendIncrease);

		auto p3x = location.x + mClamps[i+1].GetLocation().x + sin(mClamps[i+1].GetRotation() * M_PI * 2) * mClamps[i+1].GetSpeed() * bendIncrease;
		auto p3y = location.y + mClamps[i+1].GetLocation().y - cos(mClamps[i+1].GetRotation() * M_PI * 2) * mClamps[i+1].GetSpeed() * bendIncrease;

		auto path = graphics->CreatePath();
		path.MoveToPoint(mClamps[i].GetLocation() + location);
		path.AddCurveToPoint(wxPoint(p2x, p2y), wxPoint(p3x, p3y), mClamps[i+1].GetLocation() + location);
		graphics->SetPen(wxPen(*wxBLACK, TubeThickness));
		graphics->StrokePath(path);
	}

}

/**
 * Updates time of Tubing
 * @param time current time of Machine
 */
void Tubing::Update(double time)
{
	SetTime(time);
	if (mPressure > 0)
	{
		mPressure = mPressure/2;
	}
	if (mPressure < .1)
	{
		mPressure = 0;
	}
}
