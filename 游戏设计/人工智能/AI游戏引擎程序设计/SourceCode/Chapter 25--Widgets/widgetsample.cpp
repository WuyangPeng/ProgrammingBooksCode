// Our car's EventHandler class. Note that it must
// be created with a pointer to the car so that
// we can interact with it in our UIEvent's switch
// statement. Alternatively, we could also
// simply derive our car class directly from
// an EventHandler, and remove the need for
// a Car pointer.
class CarEventHandler : public EventHandler
{
public:
	CarEventHandler( Car * car ){ m_car = car; }
	virtual void UIEvent ( WPARAM id );
private:
	Car * m_car;
};

void CarEventHandler::UIEvent(WPARAM id )
{
	switch (id)
	{
	case Car::IGNITION_KEY:
		m_car->StartCar();
		break;
	case Car::WIPERS_CONTROL:
		m_car->StartWipers();
		break;
	case Car::AIR_COND:
		m_car->ToggleAirCond();
		break;
	}
}

class RacingGame
{
public:
	RacingGame(){};
	void AddWidgets( WidgetBank wb );
	
private:
	Car		m_car;
	Track	m_track;
};

class Car
{
public:
	enum {
		IGNITION_KEY,
		WIPERS_CONTROL,
		AIR_COND
	};
	void AddWidgets( Group * g );
	void StartCar(){ m_engine.Start() }
	void StartWipers(){ m_wipersOnOff = true; }
	void ToggleAirCond( m_air ? m_air = FALSE : m_air = TRUE );

private:
	Engine	m_engine;
	bool	m_lightsOnOff;
	bool	m_transmission;
	bool	m_air;
	bool	m_wipersOnOff;

	CarEventHandler m_eventHandler;
};

/********************************************************************
*	Name:	AddWidgets
*
*	Info:	A typical AddWidgets function for a fictitious racing 
*			game. Because the RacingGame object is high level, it
*			will be adding Groups directly to the widget bank. Actual
*			Widgets will be added to these groups by the AddWidget 
*			functions of lesser, individual components of the game.
*
*	Args:	wb - A pointer to the WidgetBank, which is the top-level
*			parent of all Widgets and Groups. Again, you don't add widgets
*			directly to the widget bank--you only add Groups.
*
********************************************************************/
void RacingGame::AddWidgets( WidgetBank * wb )
{
	Group * g;

	// Add our first group to the widget bank. AddGroup() returns a
	// pointer to the group it created. You can either use this pointer
	// to add widgets now, or, preferably, pass it to the AddWidgets()
	// function of a lower-level contained class.
	g = wb->AddGroup("Car Properties");
	
	// Now that we have our group, we'll pass it to the AddWidgets
	// function of our car class object, which is a member of a
	// RacingGame object.
	m_car.AddWidgets( g );

	// That takes care of the car's widgets, so let's add widgets for 
	// the race track. We'll make another group, and reassign our 
	// group pointer to it
	g = wb->AddGroup("Track Properties");

	// Again, we pass the newly assigned pointer to the AddWidget()
	// function of a lower level class, this time a RaceTrack object.
	m_track.AddWidgets( g );
}


/********************************************************************
 *	Name:	AddWidgets
 *
 *	Info:	A typical AddWidgets function for a fictitious car class
 *			to demonstrate the use of widgets. This example only
 *			covers a Car object, but remember that you have to write
 *			an AddWidgets function for any class that you want
 *			to have widgets. From here you might write AddWidgets
 *			functions for your racetrack class, your environmental
 *			class, your AI classes, etc.
 *
 *	Args:	wb - A pointer to a Group. We use a Group pointer
 *			to add the actual Widgets to our application.
 *
 *******************************************************************/
void Car::AddWidgets( Group * g )
{
	// We'll need a pointer to a group. We'll call it pg, for "parent
	// group"--be careful not to confuse it with the group pointer
	// that is being passed into this function.
	Group * pg;

	// Our car class contains an engine object. Let's give it its own
	// widget group. Groups can contain other groups, which gives
	// you a lot of flexibility to organize your widgets.
	pg = AddGroup("Engine Properties");
	
	// Our engine class has its own AddWidgets function, so we'll
	// pass it our new group pointer

	m_engine.AddWidgets( pg );

	// Our car class has some member variables that would
	// be fun to control while the game runs. We'll hook up
	// some widgets to them now, using the group pointer
	// that was passed in

	// let's start by adding a widget to control the on/off state
	// of the car's headlights
	g->AddOnOff( "Headlights", m_lightsOnOff );

	// it would be nice to monitor the car's fuel gauge--we'll
	// add a Watcher widget.
	g->AddWatcher( "Fuel Level", m_fuel);

	// We want to tune the car's mass as it drives around, so
	// we'll attach a ScrubberWidget. We're going to catch the
	// ScrubberWidget pointer that this function returns, so that
	// we can change a setting
	ScrubberWidget * sw;
	sw = g->AddScrubber( "Mass", m_mass );

	// We don't want negative or absurdly huge values for the mass of this car
	// during scrubbing, so we'll set some limits on the value using the pointer
	// we got back from the AddScrubber function
	sw->SetMinMax( 0, 10000);

	// Car objects can have automatic or manual transmissions. We'll use a radio
	// button, which allows you to have a caption for the overall control, as
	// well as each actual button. 
	g->AddRadio( "Transmission:", "Automatic", "Manual", m_transmission );

	// For our final widget, we'll add a button that starts the car's engine and 
	// other systems. Because we want to attach some functionality to this button
	// (it won't do anything if we don't), we pass in an EventHandler object that 
	// we've written for Car Objects. We also pass in an enum name for the button. 
	// This enum value will become the id number of the widget. When the button
	// is actually pressed by a user, its id number is passed to the EventHandler's 
	// UIEvent function, and is used in a switch statement to call that widget's 
	// particular code.
	g->AddBasicButton("Start Car", IGNITION_KEY, m_eventHandler );

	// We'll add a few more widgets that use the same EventHandler. 
	g->AddBasicButton("Windshield Wipers", WIPERS_CONTROL, m_eventHandler);
	g->AddOnOff("Air Conditioning", m_air, AIR_COND, m_eventHandler );
	
}

