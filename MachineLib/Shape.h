/**
 * @file Shape.h
 * @author Seth Darling
 *
 * Most basic typed of component that contains a Poylgon and location
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_SHAPE_H
#define CANADIANEXPERIENCE_MACHINELIB_SHAPE_H

#include "Component.h"
#include "Polygon.h"

/**
 * Most basic typed of component that contains a Poylgon and location
 *
 * Supports functions of a Polygon
 */
class Shape : public Component
{
private:
	/// Location of shape
	wxPoint mLocation = wxPoint(0, 0);
	/// Base polygon of shape
	cse335::Polygon mBase;
public:
	/// Default constructor
	Shape() {}

	/**
	 * Getter for location of shape
	 * @return wxPoint for location
	 */
	wxPoint GetLocation() { return mLocation; }

	/**
	 * Updates time of shape
	 * @param time time to set shape to
	 */
	void Update(double time) { SetTime(time); }

	/**
	 * Draws shape
	 * @param graphics Graphics Context object used to draw shape
	 * @param location location of Machine
	 */
	virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics, wxPoint location) {mBase.DrawPolygon(graphics, location.x + GetLocation().x, location.y + GetLocation().y);}

	/**
	 * Setter for image of shape
	 * @param image image file to be used for shape
	 */
	void SetImage(std::wstring image) { mBase.SetImage(image);}

	/**
	 * Sets Shape's polygon to a rectangle
	 * @param x x position of rectangle
	 * @param y y position of rectangle
	 * @param width width of rectangle
	 * @param height height of rectangle
	 */
	void Rectangle(double x, double y, double width=0, double height=0) {mBase.Rectangle(x, y, width, height);}

	/**
	 * Sets color of Shape
	 * @param color wxColor object
	 */
	void SetColor(wxColor color) { mBase.SetColor(color); }

	virtual /**
	 * Sets location of Shape
	 * @param location wxPoint of location
	 */
	void SetLocation(wxPoint location) { mLocation = location; }

	/**
	 * Get Width of Shape's image
	 * @return width in pixels
	 */
	double GetImageWidth() { return mBase.GetImageWidth(); }

	/**
	 * Get Height of Shape's image
	 * @return height in pixels
	 */
	double GetImageHeight() { return mBase.GetImageHeight(); }
};

#endif //CANADIANEXPERIENCE_MACHINELIB_SHAPE_H
