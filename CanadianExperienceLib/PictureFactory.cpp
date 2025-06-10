/**
 * @file PictureFactory.cpp
 * @author Charles Owen
 */

#include "pch.h"
#include "PictureFactory.h"
#include "Picture.h"
#include "HaroldFactory.h"
#include "SpartyFactory.h"
#include "Actor.h"
#include "ImageDrawable.h"
#include "MachineDrawable.h"

using namespace std;

/// Directory within resources that contains the images.
const std::wstring ImagesDirectory = L"/images";


/**
 * Factory method to create a new picture.
 * @param resourcesDir Directory that contains the resources for this application
 * @param audioEngine The audio engine to use in this application
 * @return The created picture
 */
std::shared_ptr<Picture> PictureFactory::Create(std::wstring resourcesDir, ma_engine* audioEngine)
{
    auto imagesDir = resourcesDir + ImagesDirectory;

    shared_ptr<Picture> picture = make_shared<Picture>();

    // Create the background and add it
    auto background = make_shared<Actor>(L"Background");
    background->SetClickable(false);
    background->SetPosition(wxPoint(0, 0));
    auto backgroundI =
            make_shared<ImageDrawable>(L"Background", imagesDir + L"/Background.jpg");
    background->AddDrawable(backgroundI);
    background->SetRoot(backgroundI);
    picture->AddActor(background);


	auto machineActor1 = make_shared<Actor>(L"Machine1");
	machineActor1->SetClickable(false);
	machineActor1->SetPosition(wxPoint(100, 0));
	auto machine1Drawable = make_shared<MachineDrawable>( L"machine1", resourcesDir, audioEngine);
	machine1Drawable->SetCenter(wxPoint(150, 200));
	machineActor1->AddDrawable(machine1Drawable);
	picture->AddActor(machineActor1);
	picture->SetMachineOne(machine1Drawable);

	auto machineActor2 = make_shared<Actor>(L"Machine2");
	machineActor2->SetClickable(false);
	machineActor2->SetPosition(wxPoint(300, 0));
	auto machine2Drawable = make_shared<MachineDrawable>( L"machine2", resourcesDir, audioEngine);
	machine2Drawable->SetCenter(wxPoint(450, 200));
	machineActor2->AddDrawable(machine2Drawable);
	picture->AddActor(machineActor2);
	machine2Drawable->SetMachineNumber(2);
	picture->SetMachineTwo(machine2Drawable);

    // Create and add Harold
    HaroldFactory haroldFactory;
    auto harold = haroldFactory.Create(imagesDir);

    // This is where Harold will start out.
    harold->SetPosition(wxPoint(600, 610));
    picture->AddActor(harold);

    // Create and add Sparty
    SpartyFactory spartyFactory;
    auto sparty = spartyFactory.Create(imagesDir);

    sparty->SetPosition(wxPoint(900, 620));
    picture->AddActor(sparty);




    return picture;
}

