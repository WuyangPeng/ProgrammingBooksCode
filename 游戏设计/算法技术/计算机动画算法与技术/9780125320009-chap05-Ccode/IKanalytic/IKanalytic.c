// ---------------------------------------------------------------------
// CONFIGURE
// analytic IK: determine joint angles needed to configure linkage so 
//              end effector is at goal position
// the linkage consists of : base joint - linkage 1 -  elbow joint - linkage 2 - end effector
// L1 and L2 are the lengths of the first and second linkages, respectively
// the base joint (joint1) has a z-rotation and a y-rotation
// the elbow joint (joint2) has a z-rotation
// the 'goal' is set externally
// ---------------------------------------------------------------------
void configure()
{

	float	d,t;
	float	rad,cs,radg;
	float	x,y,z;
	float	tang;
	float	temp;
	
	x = goal[0]; y = goal[1]; z = goal[2];
	
	// compute distances
	t = sqrt(x*x+z*z);  // distance from base to projection of goal to groundplane
	d = sqrt(t*t+y*y);	// distance from base to goal
	
	// compute y rotations
	if ((t<EPSILON) && (t>-EPSILON)) joint1[1] = 0.0;
	else {
		if (x > 0) joint1[1] = acos(z/t)-PI/2;	// rotation around y
		else {
			if (z>0) joint1[1] = -PI/2 - acos(z/t);
			else joint1[1] = 3*PI/2 - acos(z/t);
		}
	}

	// compute angle from base to goal in x-z space
	if ((d<EPSILON) && (d>-EPSILON)) { joint1[0]=0.0; joint2[0]=0.0; }
	else {
		cs = t/d;
		radg = acos(cs);

		if (d >= L1+L2) {
			joint1[0] = PI/2 - radg;
			joint2[0] = 0.0;
		}
		else {

			// compute interior angle #1
			cs = (L1*L1+d*d-L2*L2)/(2*L1*d);   // interior angle at base
			tang = acos(cs);
		
			// compute interior angle #2
			cs = (L1*L1+L2*L2-d*d)/(2*L1*L2);
			joint2[0] = acos(cs);				// interior angle at elbow

			// derive angles
			joint1[0] = PI/2 - radg - tang;  	// angle from vertical to link #1
			joint2[0] = PI - joint2[0];			// convert #2 to external angle
		}
	}
	return;
}

