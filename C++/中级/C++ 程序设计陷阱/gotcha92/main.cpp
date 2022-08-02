#include "button.h"
#include "moreactions.h"

int main() {
	Button b( "PRESS" );
	b.press();
	
	Talk talk;
	Beep beep;
	
	b.setAction( &talk );
	b.press();
	
	Macro m1;
	m1.add( &talk );
	m1.add( &beep );
	m1.add( &talk );
	b.setAction( &m1 );
	b.press();
	
	Macro m2;
	m2.add( m1.clone() );
	m2.add( &beep );
	b.setAction( &m2 );
	b.press();
	
	return 0;
}
