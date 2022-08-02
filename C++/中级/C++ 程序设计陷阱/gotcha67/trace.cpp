#include "trace.h"

Trace a( "global" );
 
void loopy( int cond1, int cond2 ) {
    Trace b( "function body" );
it: Trace c( "later in body" );
    if( cond1 == cond2 )
        return;
    if( cond1-1 ) {
        Trace d( "if" );
        static Trace stat( "local static" );
        while( --cond1 ) {
            Trace e( "loop" );
            if( cond1 == cond2 )
                goto it;
        }
        Trace f( "after loop" );
    }
    Trace g( "after if" );
}
