/**
 * @file AirSource.h
 * @author Seth Darling
 *
 * Object that sends air to an air sink
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_AIRSOURCE_H
#define CANADIANEXPERIENCE_MACHINELIB_AIRSOURCE_H

#include <memory>
#include "AirSink.h"

/**
 * Object that sends air to an Air Sink
 *
 * Communicates with an Air Sink by sending air
 */
class AirSource
{
private:
	/// AirSink associated with this AirSource
	std::shared_ptr<AirSink> mSink;
public:
	/// Default constructor
	AirSource() = default;
	/// Copy constructor (disabled)
	AirSource(const AirSource &) = delete;
	/// Assignment operator (disabled)
	void operator=(const AirSource &) = delete;

	void SendAir(double air);

	void SetSink(std::shared_ptr<AirSink> sink);

	/**
	 * Gets sink of air source
	 * @return mSink
	 */
	std::shared_ptr<AirSink> GetSink() { return mSink; }

};

#endif //CANADIANEXPERIENCE_MACHINELIB_AIRSOURCE_H
