/**
 * @file StruckInstrument.h
 * @author Seth Darling
 *
 * Instrument that can be struck by a cylinder
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_STRUCKINSTRUMENT_H
#define CANADIANEXPERIENCE_MACHINELIB_STRUCKINSTRUMENT_H

#include <string>
#include "Instrument.h"

/**
 * Instrument that can be struck by a cylinder
 *
 * Makes a noise when struck by cylinder.
 */
class StruckInstrument : public Instrument
{
private:
	/// If instrument has just been struck
	bool mInstrumentStruck = false;

public:
	StruckInstrument(std::wstring resourcesDir,
					 ma_engine *audioEngine,
					 std::wstring sound,
					 std::wstring image);

	void Update(double time) override;
	void Draw(std::shared_ptr<wxGraphicsContext> graphics, wxPoint location) override;

	/**
	 * Gets if Struck Instrument is currently struck
	 * @return true if struck
	 */
	bool GetIsStruck() { return mInstrumentStruck; }
};

#endif //CANADIANEXPERIENCE_MACHINELIB_STRUCKINSTRUMENT_H
