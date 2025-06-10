/**
 * @file AirSink.h
 * @author Seth Darling
 *
 * Object that recieves air from air source
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_AIRSINK_H
#define CANADIANEXPERIENCE_MACHINELIB_AIRSINK_H

#include <memory>
#include "AirAccepter.h"

class AirSource;

/**
 * Object that recieves air from Air Source
 */
class AirSink
{
private:
	/// Air Accepter component associated with this air sink
	std::shared_ptr<AirAccepter> mAccepter;
	/// Air Source of this air sink
	AirSource *mSource;
public:
	void AcceptAirPressure(double air);

	/**
	 * Sets Air Source
	 * Should only be called by an Air Source
	 * @param source Air Source to set mSource to
	 */
	void SetSource(AirSource *source) { mSource = source; }

	/**
	 * Sets Air Accepter
	 * @param accepter Air Accepter for Air Sink to act on
	 */
	void SetAccepter(std::shared_ptr<AirAccepter> accepter) { mAccepter = accepter; }
};

#endif //CANADIANEXPERIENCE_MACHINELIB_AIRSINK_H
