#include "button.h"

Button::Button( const char *label )
    : label_( label ), action_( new NullAction ) {}
    
void Button::press() const
    { (*action_)(); }
    
void Button::setAction( const Action *action )
    { delete action_; action_ = action->clone(); }

Action::~Action()
	{}

Button::~Button()
	{ delete action_; }
