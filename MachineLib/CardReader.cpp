/**
 * @file CardReader.cpp
 * @author Seth Darling
 *
 * Reads through card and sends air to appropriate Air Sinks
 * on marked beats.
 */

#include "pch.h"
#include "CardReader.h"

/// Image for the back of the card reader
const std::wstring CardReaderBackImage = L"/images/card-reader-back.png";

/// Image for the front of the card reader
const std::wstring CardReaderFrontImage = L"/images/card-reader-front.png";

// The card actual dimensions are 847 by 379 pixels,
// a size chosen to make the mCurrentColumn spacing exactly
// 10 pixels. We draw it much smaller than that on the screen

/// Width to draw the card on the screen in pixels
const int CardWidth = 132;

/// Height to draw the card on the screen in pixels
const int CardLength = 297;

/// Amount of offset the center of the card so it will
/// appear at the right place relative to the card reader.
const int CardOffsetX = 126;

/// Y dimension of the offset
const int CardOffsetY = 65;

/// Number of rows in Card
const int CardRows = 10;

/// Number of columnsin Card
const int CardColumns = 80;

// These values are all for the underlying image. They
// can be used for find the punches.

/// Width of a card mCurrentColumn in pixels
const int CardColumnWidth = 10;

/// Height of a card row in pixels
const int CardRowHeight = 29;

/// X offset for the first mCurrentColumn (left side)
const int CardColumn0X = 24;

/// Y offset to the first row (0's)
/// There are actually two rows above this that can be used
const int CardRow0Y = 78;

/// Width of a punched hole
const int CardPunchWidth = 8;

/// Height of a punched hole
const int CardPunchHit = 20;

/// Any average luminance below this level is considered a punched hole
const double CardPunchLuminance = 0.1;

/// Amount of Air to send
const double CardAir = 1;

//
// These values are for the outputs of the card reader,
// where the tubing attaches.
//

/// Y offset to the first card reader output in pixels
const int OutputOffsetY = -92;

/// X offset to the first card reader output in pixels
const int OutputOffsetX = -35;

/// X spacing for the outputs
const double OutputSpacingX = 10.7;

/**
 * Draws CardReader
 * @param graphics graphics context to be drawn to
 * @param location where to draw the card reader
 */
void CardReader::Draw(std::shared_ptr<wxGraphicsContext> graphics, wxPoint location)
{
	mBack.DrawPolygon(graphics, location.x + GetLocation().x, location.y + GetLocation().y);

	auto cardScale = (double)CardLength / mCard.GetImageWidth();

	mCard.DrawPolygon(graphics, location.x + GetLocation().x, location.y + GetLocation().y + (mCurrentColumn-1) * cardScale * CardColumnWidth);
	mFront.DrawPolygon(graphics,  location.x + GetLocation().x, location.y + GetLocation().y);
}

/**
 * Constructor for Card Reader
 * @param resourcesDir Directory used for images and audio files
 */
CardReader::CardReader(std::wstring resourcesDir)
{
	mBack.SetImage(resourcesDir + CardReaderBackImage);
	mBack.Rectangle(-mBack.GetImageWidth() / 2, 0);

	mFront.SetImage(resourcesDir + CardReaderFrontImage);
	mFront.Rectangle(-mFront.GetImageWidth() / 2, 0);

	mCard.SetImage(resourcesDir + L"/images/cards/mary.png");
	mCard.Rectangle(CardOffsetX, CardOffsetY, CardLength, CardWidth);
	mCard.SetRotation(-0.25);


}

/**
 * Determine if a hole is punched in the card.
 * @param column Column on the card, from 0 (left of first mCurrentColumn) to 80 (last mCurrentColumn)
 * @param row Row on the card, -2 to 9.
 * @return True if hole is punched at mCurrentColumn, row
*/
bool CardReader::IsPunched(int column, int row)
{
	auto luminance = mCard.AverageLuminance(CardColumn0X + (column - 1) * CardColumnWidth,
											CardRow0Y + CardRowHeight * row, CardPunchWidth, CardPunchHit);
	return luminance < CardPunchLuminance;
}

/**
 * Updates Card Reader
 * @param time current time of machine
 */
void CardReader::Update(double time)
{
	SetTime(time);

	double beat = GetTime() * mBeatsPerMinute / 60.0;
	double remainder = fmod(beat, 1);
	mCurrentColumn = (int)beat;

	if (mCurrentColumn > CardColumns)
	{
		mCurrentColumn = CardColumns;
	}

	for (int i = 0; i < mSources.size(); i++)
	{
		if (mCurrentColumn > CardColumns)
		{
			break;
		}
		if(IsPunched(mCurrentColumn, i))
		{
			if (remainder < 0.5)
			{
				mSources[i]->SendAir(CardAir);
			}
		}
	}

}
