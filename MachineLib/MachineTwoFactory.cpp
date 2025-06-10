/**
 * @file MachineTwoFactory.cpp
 * @author Seth Darling
 *
 * Factory used to create Machine Two
 */

#include "pch.h"
#include "Shape.h"
#include "Machine.h"
#include "MachineTwoFactory.h"
#include "Pipe.h"
#include "AirSource.h"
#include "AirSink.h"
#include "CardReader.h"
#include "StruckInstrument.h"
#include "Cylinder.h"
#include "Tubing.h"
#include "Cymbal.h"
#include <string>

/**
 * Constructor
 * @param resourcesDir Directory to load resources from
 * @param audioEngine The miniaudio engine to use
 */
MachineTwoFactory::MachineTwoFactory(std::wstring resourcesDir, ma_engine* audioEngine) :
	mResourcesDir(resourcesDir), mAudioEngine(audioEngine)
{
}

/**
 * Create a machine system object
 *
 * Do not change the return type of this function!
 *
 * @return Object of type MachineSystem
 */
std::shared_ptr<Machine> MachineTwoFactory::CreateMachineTwo()
{
	// Sizes
	const int BackgroundWidth = 550;

	// Locations of stuff
	const int BaseWidth = 700;
	const int BaseHeight = 10;
	// All of the centers (X)
	const int BackgroundCenter = 80;
	const int CardReaderCenter = -275;
	const int CymbalAndDrumCenter = 295;
	const int ClampingPostCenter = -182;
	const int NumPipes = 5;
	const int PipesCenter = 100;
	const int PipeSpacing = 50;
	const int PipeY = -80;

	std::shared_ptr<Machine> machine = std::make_shared<Machine>(mResourcesDir);
	machine->SetNumber(2);

	// The base, just a flat to sit things on
	auto base = std::make_shared<Shape>();
	base->Rectangle(-BaseWidth /2, BaseHeight, BaseWidth, BaseHeight);
	base->SetColor(wxColour(100, 0, 0));
	machine->AddComponent(base);

	//
	// The background image
	//
	auto background = std::make_shared<Shape>();
	background->SetImage(mResourcesDir + L"/images/mortier.png");
	background->Rectangle(-BackgroundWidth /2, 0, BackgroundWidth, 0);
	background->SetLocation(wxPoint(BackgroundCenter, 0));
	machine->AddComponent(background);


	// Make Card Reader
	std::shared_ptr<CardReader> cardReader = std::make_shared<CardReader>(mResourcesDir);
	cardReader->SetCard(mResourcesDir + L"/images/cards/uptown.png");
	cardReader->SetLocation(wxPoint(CardReaderCenter, 0));
	machine->AddComponent(cardReader);


	//
	// Pipes
	//
	int PipeLength[] = { 40, 105, 300, 120, 55 };
	const wchar_t* sounds[] = {L"/audio/organC4.wav",
		L"/audio/organD4.wav",
		L"/audio/organE4.wav",
		L"/audio/organG4.wav",
		L"/audio/organA4.wav"};

	// Vector to collect the pipes so we can
	// run hoses to them later.
	std::vector<std::shared_ptr<Pipe>> pipes;

	//
	// The pipes
	//
	int pipeX = -PipeSpacing * NumPipes / 2 + PipesCenter;
	for (int i = 0; i < NumPipes; i++) {
		//
		// The pipes
		//
		auto pipe = std::make_shared<Pipe>(mResourcesDir, mAudioEngine, sounds[i], PipeLength[i]);
		pipe->SetLocation(wxPoint(pipeX, PipeY));
		machine->AddComponent(pipe);
		pipes.push_back(pipe);

		pipeX += PipeSpacing;
	}


	// Makes Air Sources for Card Reader

	for (auto pipe : pipes)
	{
		std::shared_ptr<AirSource> source = std::make_shared<AirSource>();
		std::shared_ptr<AirSink> sink = std::make_shared<AirSink>();
		source->SetSink(sink);

		sink->SetAccepter(pipe);
		cardReader->AddSource(source);
	}
	for (int i = 0; i < 3; i++)
	{
		auto source = std::make_shared<AirSource>();
		cardReader->AddSource(source);
	}



	//
	// The drum
	//
	auto drum = std::make_shared<StruckInstrument>(mResourcesDir, mAudioEngine, L"/audio/kick.wav", L"/images/drum.png");

	drum->SetLocation(wxPoint(CymbalAndDrumCenter - 75, -100));




	auto drumCylinder = std::make_shared<Cylinder>(mResourcesDir, 44, .25);
	drumCylinder->SetLocation(wxPoint(35, -30));



	drumCylinder->SetStruckInstrument(drum);
	auto source2 = std::make_shared<AirSource>();
	cardReader->AddSource(source2);
	std::shared_ptr<AirSink> sink2 = std::make_shared<AirSink>();
	source2->SetSink(sink2);
	sink2->SetAccepter(drumCylinder);


	//
	// The cymbal
	//
	auto cymbal = std::make_shared<Cymbal>(mResourcesDir, mAudioEngine);
	cymbal->SetLocation(wxPoint(CymbalAndDrumCenter, -230));
	machine->AddComponent(cymbal);

	auto cymbalCylinder = std::make_shared<Cylinder>(mResourcesDir, 20, 0.5);
	cymbalCylinder->SetLocation(wxPoint(CymbalAndDrumCenter - 25, -370));
	machine->AddComponent(cymbalCylinder);
	cymbalCylinder->SetStruckInstrument(cymbal);

	auto source = std::make_shared<AirSource>();
	cardReader->AddSource(source);
	std::shared_ptr<AirSink> sink = std::make_shared<AirSink>();
	source->SetSink(sink);

	sink->SetAccepter(cymbalCylinder);
	machine->AddComponent(drum);
	machine->AddComponent(drumCylinder);


	//
	// We do the tubing last so it is on top
	//
	for (int i = 0; i < 5; i++)
	{
		auto tubing = std::make_shared<Tubing>();
		auto tubingSource = std::make_shared<AirSource>();
		auto tubingSink = std::make_shared<AirSink>();
		tubing->SetSource(tubingSource);
		tubingSink->SetAccepter(tubing);
		cardReader->GetSource(i)->SetSink(tubingSink);
		auto pipeSink = std::make_shared<AirSink>();
		tubingSource->SetSink(pipeSink);
		pipeSink->SetAccepter(pipes[4-i]);

		tubing->AddClamp(wxPoint(cardReader->GetLocation().x -35 + 10.7 * i, cardReader->GetLocation().y -92), 50, 0);
		tubing->AddClamp(wxPoint(ClampingPostCenter + 15, -10 - 10*i), 40, .75);
		tubing->AddClamp(wxPoint(pipes[4-i]->GetLocation().x, pipes[4-i]->GetLocation().y), 25, .5);

		tubing->SetBend(true);
		machine->AddComponent(tubing);


	}

	// Draw tubing from card reader to drum
	int drumIndex = 8;
	auto tubing = std::make_shared<Tubing>();
	auto tubingSource = std::make_shared<AirSource>();
	auto tubingSink = std::make_shared<AirSink>();
	tubing->SetSource(tubingSource);
	tubingSink->SetAccepter(tubing);
	cardReader->GetSource(drumIndex)->SetSink(tubingSink);
	auto drumSink = std::make_shared<AirSink>();
	tubingSource->SetSink(drumSink);
	drumSink->SetAccepter(drumCylinder);

	tubing->AddClamp(wxPoint(cardReader->GetLocation().x -35 + 10.7 * drumIndex, cardReader->GetLocation().y -92), 50, 0);
	tubing->AddClamp(wxPoint(ClampingPostCenter + 10, -10 - 10 * 5), 50, .75);
	tubing->AddClamp(wxPoint(drumCylinder->GetLocation().x + 24.5, drumCylinder->GetLocation().y + 8), 25, .67);

	tubing->SetBend(true);
	machine->AddComponent(tubing);

	// Draw tubing from card reader to cymbal
	int cymbalIndex = 9;
	tubing = std::make_shared<Tubing>();
	tubingSource = std::make_shared<AirSource>();
	tubingSink = std::make_shared<AirSink>();
	tubing->SetSource(tubingSource);
	tubingSink->SetAccepter(tubing);
	cardReader->GetSource(cymbalIndex)->SetSink(tubingSink);
	auto cymbalSink = std::make_shared<AirSink>();
	tubingSource->SetSink(cymbalSink);
	cymbalSink->SetAccepter(cymbalCylinder);

	tubing->AddClamp(wxPoint(cardReader->GetLocation().x -35 + 10.7 * cymbalIndex, cardReader->GetLocation().y -92), 50, 0);
	tubing->AddClamp(wxPoint(-180, -150), 80, .5);
	tubing->AddClamp(wxPoint(-180, -300), 120, .5);
	tubing->AddClamp(wxPoint(cymbalCylinder->GetLocation().x-14, cymbalCylinder->GetLocation().y+22), 25, -.17);

	tubing->SetBend(true);
	machine->AddComponent(tubing);



	// Clamping post clamps for the tubing
	auto clamps = std::make_shared<Shape>();
	clamps->SetImage(mResourcesDir + L"/images/clamping-post-clamps.png");
	clamps->Rectangle(-clamps->GetImageWidth()/2, 0);
	clamps->SetLocation(wxPoint(ClampingPostCenter + 10, 0));
	machine->AddComponent(clamps);

	//
	// The foreground image (ropes that draw in front)
	//
	auto backgroundRope = std::make_shared<Shape>();
	backgroundRope->SetImage(mResourcesDir + L"/images/mortier-rope.png");
	backgroundRope->Rectangle(-BackgroundWidth /2, 0, BackgroundWidth, 0);
	backgroundRope->SetLocation(wxPoint(BackgroundCenter, 0));
	machine->AddComponent(backgroundRope);


	return machine;
}