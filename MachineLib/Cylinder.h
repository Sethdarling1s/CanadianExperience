/**
 * @file Cylinder.h
 * @author Seth Darling
 *
 * Cylinder that is connected to an air sink and strikes a struck instrument.
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_CYLINDER_H
#define CANADIANEXPERIENCE_MACHINELIB_CYLINDER_H

#include "Component.h"
#include "AirAccepter.h"
#include "Polygon.h"
#include "StruckInstrument.h"
#include <memory>

/**
 * Cylinder that is connected to an air sink and strikes a struck instrument.
 */
class Cylinder : public Shape, public AirAccepter
{
private:
	/// Polygon for base of cylinder
	cse335::Polygon mBase;
	/// Polygon for ram of cylinder
	cse335::Polygon mRam;
	/// Polygon for body of cylinder
	cse335::Polygon mCylinder;
	/// If cylinder is extended
	bool mIsExtended = false;
	/// Length to extend
	int mExtensionLength = 44;
	/// Struck instrument that cylinder is associated with
	std::shared_ptr<StruckInstrument> mStruckInstrument;
	/// Time to extend till
	double mExtensionTime = 0;
	/// Angle of cylinder in radians
	double mAngle = 0;

public:
	/** Copy constructor disabled */
	Cylinder(const Cylinder &) = delete;
	/** Assignment operator disabled */
	void operator=(const Cylinder &) = delete;

	Cylinder(std::wstring resourcesDir, int extensionLength=44, double angle=0);

	/**
	 * Sets Struck Instrument that this cylinder hits
	 * @param struckInstrument Struck Instrument associated with Cylinder
	 */
	void SetStruckInstrument(std::shared_ptr<StruckInstrument> struckInstrument) { mStruckInstrument = struckInstrument;}
	void ReceiveAir(double air);
	void Update(double time) override;
	void Draw(std::shared_ptr<wxGraphicsContext> graphics, wxPoint location) override;
};

#endif //CANADIANEXPERIENCE_MACHINELIB_CYLINDER_H
