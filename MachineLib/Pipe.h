/**
 * @file Pipe.h
 * @author Seth Darling
 *
 * A pipe is a type of instrument that makes sound and smoke.
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_PIPE_H
#define CANADIANEXPERIENCE_MACHINELIB_PIPE_H

#include "Instrument.h"
#include "AirAccepter.h"


/**
 * A pipe is a type of instrument that makes sound and smoke.
 *
 * Plays a sound and puffs out smoke
 */
class Pipe : public Instrument, public AirAccepter
{
private:
	/// Polygon for main body
	cse335::Polygon mPipe;
	/// Polygon for pipe base
	cse335::Polygon mBase;
	/// Polygon for top of pipe
	cse335::Polygon mTop;
	/// Polygon for puff
	cse335::Polygon mPuff;
	/// If puff should be displayed
	bool mShowSmoke = false;
	/// Time to display smoke
	double mDisplaySmoke = 0;
public:
	Pipe(std::wstring resourcesDir, ma_engine *audioEngine, std::wstring sound, double length);

	/** Copy constructor disabled */
	Pipe(const Pipe &) = delete;
	/** Assignment operator disabled */
	void operator=(const Pipe &) = delete;

	void Update(double time) override;
	void Draw(std::shared_ptr<wxGraphicsContext> graphics, wxPoint location) override;
	void PlaySound();

	void ReceiveAir(double time) override;
};

#endif //CANADIANEXPERIENCE_MACHINELIB_PIPE_H
