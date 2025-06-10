/**
 * @file Tubing.h
 * @author Seth Darling
 *
 * Tubing that connects an air source to air sink
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_TUBING_H
#define CANADIANEXPERIENCE_MACHINELIB_TUBING_H

#include "AirAccepter.h"
#include "Component.h"
#include "AirSource.h"
#include <vector>
#include <memory>


/**
 * Connects air source to air sink
 *
 * Is both an air source and an air sink itself
 */
class Tubing : public AirAccepter, public Component
{
private:
	/// Starting point of tubing
	wxPoint mStartPoint;
	/// End point of tubing
	wxPoint mEndPoint;
	/// Air source of tubing
	std::shared_ptr<AirSource> mSource;
	/// Pressure of air in tubing
	double mPressure = 0;
	/// If Tubing changes due to pressure
	bool mBends = false;

	/**
	 * Class that describes clamps that are used to draw tubing
	 */
	class Clamp
	{
	private:
		/// Location of clamp
		wxPoint mLocation;
		/// Speed of clamp
		double mSpeed;
		/// Rotation of clamp
		double mRotation;
	public:
		/**
		 * Constructor for clamp
		 * @param location location for clamp
		 * @param speed speed for clamp
		 * @param rotation rotation for clamp
		 */
		Clamp(wxPoint location, double speed, double rotation) : mLocation(location), mSpeed(speed), mRotation(rotation) {}

		/**
		 * Get location of clamp
		 * @return mLocation wxPoint of location
		 */
		wxPoint GetLocation() { return mLocation; }

		/**
		 * Get speed of clamp
		 * @return mSpeed speed of clamp
		 */
		double GetSpeed() { return mSpeed;}

		/**
		 * Get rotation of clamp in radians
		 * @return rotation of clamp
		 */
		double GetRotation() { return mRotation; }


	};

	/// Collection of Clamps
	std::vector<Clamp> mClamps;

public:
	/// Default Constructor
	Tubing() {}
	void ReceiveAir(double pressure) override;
	void Draw(std::shared_ptr<wxGraphicsContext> graphics, wxPoint location) override;
	void Update(double time) override;

	/**
	 * Sets if Tubing bends due to pressure
	 * @param bend true if Tubing bends
	 */
	void SetBend(bool bend) { mBends = bend; }

	/**
	 * Add Clamp to tubing object
	 * @param location location of clamp
	 * @param speed speed of clamp
	 * @param rotation rotation of clamp
	 */
	void AddClamp(wxPoint location, double speed, double rotation) {mClamps.emplace_back(location, speed, rotation); }

	/**
	 * Sets air source for tubing
	 * @param source air source that belongs to tubing
	 */
	void SetSource(std::shared_ptr<AirSource> source) { mSource = source; }

	/**
	 * Gets air source of tubing
	 * @return mSource
	 */
	std::shared_ptr<AirSource> GetSource() { return mSource; }

	/** Copy constructor disabled */
	Tubing(const Tubing &) = delete;

	/** Assignment operator disabled */
	void operator=(const Tubing &) = delete;

};

#endif //CANADIANEXPERIENCE_MACHINELIB_TUBING_H
