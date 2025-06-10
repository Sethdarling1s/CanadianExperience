/**
 * @file CardReader.h
 * @author Seth Darling
 *
 * Reads through card and sends air to appropriate Air Sinks
 * on marked beats.
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_CARDREADER_H
#define CANADIANEXPERIENCE_MACHINELIB_CARDREADER_H

#include <memory>
#include <vector>
#include "Shape.h"
#include "Polygon.h"
#include "AirSource.h"

/**
 * Reads through card and sends air to appropriate Air Sinks
 * on marked beats.
 */
class CardReader : public Shape
{
private:
	/// Polygon used for front of Card Reader
	cse335::Polygon mFront;
	/// Polygon used for Card
	cse335::Polygon mCard;
	/// Polygon used for Back of Card Reader
	cse335::Polygon mBack;
	/// Current column of Card Reader
	int mCurrentColumn = 0;
	/// Beats per minute of Card
	double mBeatsPerMinute = 180.0;

	/// Container of Air Sources associated with Card Reader
	std::vector<std::shared_ptr<AirSource>> mSources;


public:
	void Draw(std::shared_ptr<wxGraphicsContext> graphics, wxPoint location) override;
	CardReader(std::wstring resourcesDir);
	bool IsPunched(int column, int row);
	void Update(double time) override;

	/**
	 * Sets card of Card Reader
	 * @param card card image to be used
	 */
	void SetCard(std::wstring card) { mCard.SetImage(card); }

	/**
	 * Adds Air Source to collection of Air Sources
	 * @param source Air Source to be added
	 */
	void AddSource(std::shared_ptr<AirSource> source) { mSources.push_back(source); }

	/**
     * Get an air source.
     * @param index Source index 0-9
     * @return Pointer to AirSource object.
    */
	std::shared_ptr<AirSource> GetSource(int index) { return mSources[index]; }
};

#endif //CANADIANEXPERIENCE_MACHINELIB_CARDREADER_H
