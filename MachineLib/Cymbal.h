/**
 * @file Cymbal.h
 * @author Seth Darling
 *
 * Struck Instrument that is a cymbal
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_CYMBAL_H
#define CANADIANEXPERIENCE_MACHINELIB_CYMBAL_H

#include "StruckInstrument.h"
#include <string>
#include "Polygon.h"

/**
 * Struck Instrument that is a cymbal
 */
class Cymbal : public StruckInstrument
{
private:
	/// Polygon for Cymbal
	cse335::Polygon mCymbal;
	/// Time to shake for
	double mShakeTime = 0;
	/// Direction Cymbal Shakes
	int mShakeDirection = 1;


public:
	Cymbal(std::wstring resourcesDir, ma_engine *audioEngine);

	void Update(double time) override;
	void PlaySound() override;
	void Draw(std::shared_ptr<wxGraphicsContext> graphics, wxPoint location) override;
	void SetLocation(wxPoint location) override;
};

#endif //CANADIANEXPERIENCE_MACHINELIB_CYMBAL_H
