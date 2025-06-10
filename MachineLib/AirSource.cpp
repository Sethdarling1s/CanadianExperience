/**
 * @file AirSource.cpp
 * @author Seth Darling
 *
 * Object that sends air to an air sink
 */

#include "pch.h"
#include "AirSource.h"

/**
 * Sends air to associated Air Sink
 * @param air pressure of air to be sent
 */
void AirSource::SendAir(double air)
{
	mSink->AcceptAirPressure(air);
}

/**
 * Sets Air Sink associated with this Air Source
 * Also sets relation on Air Sink's end
 * @param sink Air Sink to be associated with
 */
void AirSource::SetSink(std::shared_ptr<AirSink> sink)
{
	mSink = sink;
	sink->SetSource(this);
}
