/**
 * @file AirSink.cpp
 * @author Seth Darling
 *
 * Object that recieves air from air source
 */

#include "pch.h"
#include "AirSink.h"

/**
 * Calls receive air on air acceptor associated with this air sink
 * @param air pressure of air passed to sink
 */
void AirSink::AcceptAirPressure(double air)
{
	mAccepter->ReceiveAir(air);
}
