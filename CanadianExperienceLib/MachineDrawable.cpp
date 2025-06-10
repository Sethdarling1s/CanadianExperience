/**
 * @file MachineDrawable.cpp
 * @author Seth Darling
 *
 * Adapter class for machine system
 */

#include "pch.h"
#include "MachineDrawable.h"
#include "Timeline.h"

/**
 * Constructor for Machine Drawable
 * @param name name of Machine Drawable
 * @param resourcesDir directory for images and audio
 * @param audioEngine engine used to play sounds
 */
MachineDrawable::MachineDrawable(std::wstring name, std::wstring resourcesDir, ma_engine *audioEngine) : Drawable(name)
{
	mResourcesDir = resourcesDir;
	mAudioEngine = audioEngine;
	MachineSystemFactory factory(resourcesDir, audioEngine);
	std::shared_ptr<MachineSystem> machine = factory.CreateMachineSystem();
	machine->SetMachineNumber(1);
	machine->SetLocation(wxPoint(500, 400));
	mMachineSystem = machine;
}

/**
 * Draws machine at location of Machine Drawable
 * @param graphics graphics context object used to draw machine
 */
void MachineDrawable::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
	if (mTimeline->GetCurrentFrame() - mStartFrame >= 0)
	{
		mMachineSystem->SetMachineFrame(mTimeline->GetCurrentFrame() - mStartFrame);
	}

	double scale = 0.7f;

	graphics->PushState();
	graphics->Translate(mMachineSystem->GetLocation().x, mMachineSystem->GetLocation().y);
	graphics->Scale(scale, scale);
	mMachineSystem->SetLocation(wxPoint(mMachineSystem->GetLocation().x, mMachineSystem->GetLocation().y));
	mMachineSystem->DrawMachine(graphics);
	graphics->PopState();

	//mMachineSystem->DrawMachine(graphics);
}

/**
 * Hit test for Machine Drawable
 * @param pos position to test
 * @return false
 */
bool MachineDrawable::HitTest(wxPoint pos)
{
	return false;
}

/**
 * Sets mTimeline to passed timeline
 * @param timeline timeline associated with Machine Drawable
 */
void MachineDrawable::SetTimeline(Timeline *timeline)
{
	Drawable::SetTimeline(timeline);
	mTimeline = timeline;
}

/**
 * Creates Machine Dialog box
 * @param parent Mainframe to draw dialog box
 * @return Pointer to Machine Dialog
 */
std::shared_ptr<MachineDialog> MachineDrawable::CreateDialog(wxWindow *parent)
{
	std::shared_ptr<MachineDialog> dlg = std::make_shared<MachineDialog>(parent, mMachineSystem);
	return dlg;
}

/**
 * Saves Machine Drawable to Xml node
 * @param root node to save Machine Drawable at
 */
void MachineDrawable::XmlSave(wxXmlNode *root)
{
	auto node = new wxXmlNode(wxXML_ELEMENT_NODE, L"machine");
	node->AddAttribute(L"startframe", wxString::Format(wxT("%i"), mStartFrame));
	node->AddAttribute(L"number", wxString::Format(wxT("%i"), mMachineSystem->GetMachineNumber()));
	root->AddChild(node);
}

/**
 * Loads MachineDrawable from Xml node
 * @param node Xml load to load Machine Drawable from
 */
void MachineDrawable::XmlLoad(wxXmlNode *node)
{
	// Get the attributes
	mStartFrame = wxAtoi(node->GetAttribute(L"startframe", L"0"));
	mMachineSystem->SetMachineNumber(wxAtoi(node->GetAttribute(L"number", L"1")));

}

