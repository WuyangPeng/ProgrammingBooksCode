#pragma once
/********************************************************************
*	EventHandler:	If you want to call functions of your own when
*					OnOffButtons, RadioButtons, or BasicButtons are 
*					you must derive a class from EventHandler, and
*					override UIEvent. You then pass the new class
*					you made into a Group's appropriate widget create 
*					function (AddOnOffButton, AddBasicButton, or 
*					AddRadioButton). When a button is pressed, its
*					id number will get passed into UIEvent, so that
*					you can switch on it, and execute the appropriate
*					code.
*
*					Don't forget to pass in descriptive enum values
*					when creating your widgets (ie. FILE_LOAD,
*					WIREFRAME_TOGGLE, SPAWN_MONSTER, etc), so that
*					you can easily switch on this value in your 
*					UIEvent function.
*
********************************************************************/
class EventHandler
{
public:
	EventHandler(){};
	virtual void UIEvent( WPARAM id )=0;
};