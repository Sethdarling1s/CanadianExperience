/**
 * @file AirAccepter.h
 * @author Seth Darling
 *
 * Interface class for objects connected to by Air Sink
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_AIRACCEPTER_H
#define CANADIANEXPERIENCE_MACHINELIB_AIRACCEPTER_H

/**
 * Interface class for objects connected to by Air Sink
 */
class AirAccepter
{
public:
	/**
	 * Pure virtual function called when associated Air Sink gets air
	 * @param pressure pressure of air
	 */
	virtual void ReceiveAir(double pressure) = 0;
};

#endif //CANADIANEXPERIENCE_MACHINELIB_AIRACCEPTER_H
