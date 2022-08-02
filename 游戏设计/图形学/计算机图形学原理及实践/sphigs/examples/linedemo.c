#include "sphigs.h"
#include <stdio.h>

   double vpnalpha, vpnbeta;
   double vupalpha, vupbeta;

   matrix vo_matrix, vm_matrix;
   matrix temp_matrix, rot, scale;

   /* DEFAULT VALUES */
   point vrpdef, prpdef;
   double umindef, umaxdef, vmindef, vmaxdef;
   double fplanedef, bplanedef;
   vector vpndef, vupvdef;

   /* VIEW 1 (user can play with these numbers) */
   point vrp1, prp1;
   double umin1, umax1, vmin1, vmax1;
   double fplane1, bplane1;
   vector vpn1, vupv1;

vector deltavec;



char keymeas[5];


/* NORMALIZED "ARCHETYPAL" HOUSE */

static point house_vertices[] = {
   { 0.,10.,0. },
   { 8.,16.,0. },
   { 16.,10.,0. },
   { 16.,0.,0. }, 
   { 0.,0.,0. },
   { 0.,0.,-40. },
   { 16.,0.,-40. },
   { 16.,10.,-40. },
   { 8.,16.,-40. },
   { 0.,10.,-40. }
};



#define HOUSE_STRUCT 1
#define STREET_STRUCT 2
#define NEIGHBORHOOD_STRUCT 3


/* READS three doubles from stdin */
ReadVector (vec)
double *vec;
{
   scanf("%lf %lf %lf\n", &vec[0], &vec[1], &vec[2]);
}



#define WaitForKeystroke	SRGP_waitEvent(-1)
#define WriteMessage(s)  	SRGP_text (SRGP_defPoint(15,4), s)
#define WriteUpperMessage(s)  	SRGP_text (SRGP_defPoint(15,20), s)




ShowUsingNewView1()
{
   SPH_evaluateViewOrientationMatrix 
      (vrp1,
       vpn1,
       vupv1,
       vo_matrix);

   SPH_evaluateViewMappingMatrix
      (umin1, umax1,   vmin1, vmax1, PERSPECTIVE,
       prp1,
       fplane1, bplane1,
       0.0, 1.0,  0.0, 1.0,  0.0, 1.0,
       vm_matrix);

   SPH_setViewRepresentation
      (1,
       vo_matrix, vm_matrix,
       0.0, 1.0,  0.0, 1.0,  0.0, 1.0);
}


RestoreCameraToDefault()
{
   /* COPY DEFAULTS INTO VIEW 1's DATA */
   MAT3_COPY_VEC (vrp1, vrpdef);
   MAT3_COPY_VEC (vpn1, vpndef);
   MAT3_COPY_VEC (vupv1, vupvdef);
   MAT3_COPY_VEC (prp1, prpdef);
   fplane1 = fplanedef;
   bplane1 = bplanedef;
   umin1 = umindef;
   vmin1 = vmindef;
   umax1 = umaxdef;
   vmax1 = vmaxdef;

}



#define CHANGE_VRP	1
#define CHANGE_VPN	2
#define CHANGE_PRP	3
#define CHANGE_WINDOW	4
#define CHANGE_FRONT	5
#define CHANGE_BACK	6

char *prompts[] =
{
   "",
   "You can now change the View Reference Point -- on any axis...\n",
   "You can now change the View Plane Normal -- x=yaw, y=pitch...\n",
   "You can now change the Projection Reference Point -- on n axis only...\n",
   "You can now slide the uvn window -- on u or v axis only...\n",
   "You can now slide the front clipping plane -- on n axis only...\n",
   "You can now slide the back clipping plane -- on n axis only...\n"
};

int currentchange;

Prompt()
{
   fprintf (stderr, prompts[currentchange]);
}




main(argc, argv)
int argc;
char **argv;
{

   int i;



   fprintf (stderr, "I hope you redirected stdin so I can read from\n");
   fprintf (stderr, "   the data file.  Otherwise, you'll be sitting\n");
   fprintf (stderr, "   here forever!\n");

   /* READ THE DEFAULTS */
   ReadVector (vrpdef);
   ReadVector (vpndef);
   ReadVector (vupvdef);
   ReadVector (prpdef);
   scanf ("%lf %lf\n", &fplanedef, &bplanedef);
   scanf ("%lf %lf   %lf %lf\n", &umindef, &umaxdef, &vmindef, &vmaxdef);


   /* STARTUP SPHIGS */
   SPH_begin (1100,800,0,0);


   /*** HERE WE SET UP THE VIEW #1 THAT WILL SHOW A WIREFRAME VERSION OF
        THE PICTURE, THAT CAN BE MANIPULATED BY THE USER. */
   RestoreCameraToDefault();
   ShowUsingNewView1();

   


   /* the only rendering mode supported with this interim SPHIGS version */
   SRGP_loadCommonColor (2, "grey");
   SRGP_loadCommonColor (3, "red");
   SPH_setViewBackgroundColor (1, 2);
   SPH_setRenderingMode (1, WIREFRAME_RAW); 

   /* Creating a structure containing just polymarkers. */
   SPH_openStructure (HOUSE_STRUCT);
   SPH_polyMarker (10, house_vertices);
   SPH_closeStructure ();
   SPH_postRoot (HOUSE_STRUCT, 1);   /* posting structure 1 to view 0 */
   WriteMessage ("Normalized house vertices (no lines).");
   WriteUpperMessage ("Hit any key to continue.");
   WaitForKeystroke;
   SPH_unpostRoot (HOUSE_STRUCT, 1);



   SPH_openStructure (HOUSE_STRUCT);
   SPH_polyLine (10, house_vertices);
   SPH_closeStructure ();
   SPH_postRoot (HOUSE_STRUCT, 1);   /* posting structure 1 to view 0 */
   WriteMessage ("Same w/ lines (some lines missing because this really should be a polyhedron).");
   WriteUpperMessage ("Hit any key to continue.");
   WaitForKeystroke;
   SPH_unpostRoot (HOUSE_STRUCT, 1);

   SPH_openStructure (STREET_STRUCT);
   SPH_setModXform(SPH_translate(0.0, 0.0, 0.0, temp_matrix), POSTCONCATENATE);
   SPH_executeStructure (HOUSE_STRUCT);
   for (i=0; i<5; i++) {
      SPH_setModXform(SPH_translate(20.0, 0.0, 0.0, temp_matrix),
		      POSTCONCATENATE);
      SPH_executeStructure (HOUSE_STRUCT);
   }
   SPH_closeStructure();
   SPH_postRoot (STREET_STRUCT, 1);
   WriteMessage("Normalized street made up of transformed houses.");
   WriteUpperMessage ("Hit any key to continue.");
   WaitForKeystroke;
   SPH_unpostRoot (STREET_STRUCT, 1);



   SPH_openStructure (NEIGHBORHOOD_STRUCT);
   SPH_executeStructure (STREET_STRUCT);
   for (i=0; i<3; i++) {
      SPH_setModXform(SPH_translate(0.0, 0.0, -70.0, temp_matrix),
		      POSTCONCATENATE);
      SPH_setMarkerColor (3);
      SPH_setLineColor (0);
      SPH_setMarkerSizeScaleFactor (2.0);
      SPH_setMarkerStyle (MARKER_X);
      SPH_executeStructure (STREET_STRUCT);
   }
   SPH_closeStructure();
   SRGP_tracing(TRUE);
   SPH_postRoot (NEIGHBORHOOD_STRUCT, 1);
   SRGP_tracing(FALSE);
   WriteMessage("Normalized neighborhood made up of transformed streets.");
   WriteUpperMessage ("Hit a key.");
   WaitForKeystroke;
   WriteUpperMessage ("            You can now move the camera.  See console for details.");


   fprintf (stderr, 
"You can now move the camera using the keyboard.\n\
 Numeric keys change what it is you are moving:\n\
    1 --> change the VRP\n\
    2 --> change the VPN\n\
    3 --> change the PRP\n\
    6 --> restore camera settings to default (in case you get lost)\n\
 Here is how you change the points or vectors:\n\
            s and d change the X value\n\
            e and x change the Y value\n\
            - and = change the Z value\n\
            for sdex-=, lowercase changes coarsely, but\n\
                        uppercase changes with fine detail\n\
            \n\
            I apologize for this shoddy interface!\n");


   SRGP_setInputMode (KEYBOARD, SAMPLE);
   SRGP_setInputMode (LOCATOR, EVENT);
   SRGP_setKeyboardProcessingMode (RAW);

   currentchange = CHANGE_VRP;
   Prompt();
   vpnalpha=0.0;
   vpnbeta=0.0;
   vupalpha=0.0;
   vupbeta= M_PI/2.0;
   
   while (1) {
      SRGP_waitEvent (INDEFINITE);
      SRGP_getKeyboard (keymeas, 3);
      MAT3_SET_VEC (deltavec, 0.0, 0.0, 0.0);
      switch (keymeas[0]) {
       case '1': currentchange = CHANGE_VRP; Prompt(); continue; break;
       case '2': currentchange = CHANGE_VPN; Prompt(); continue; break;
       case '3': currentchange = CHANGE_PRP; Prompt(); continue; break;
/*       case '4': currentchange = CHANGE_WINDOW; Prompt(); continue; break;
         case '5': currentchange = CHANGE_FRONT; Prompt(); continue; break;
         case '6': currentchange = CHANGE_BACK; Prompt(); continue; break; */
       case '8': RestoreCameraToDefault();
	 
       case 's': deltavec[0]= -10.0; break;
       case 'd': deltavec[0]= 10.0; break;
       case 'e': deltavec[1]= 10.0; break;
       case 'x': deltavec[1]= -10.0; break;
       case '=': deltavec[2]= 10.0; break;
       case '-': deltavec[2]= -10.0; break;

       case 'S': deltavec[0]= -1.0; break;
       case 'D': deltavec[0]= 1.0; break;
       case 'E': deltavec[1]= 1.0; break;
       case 'X': deltavec[1]= -1.0; break;
       case '+': deltavec[2]= 1.0; break;
       case '_': deltavec[2]= -1.0; break;
      }
      
      switch (currentchange) {
       case CHANGE_VRP:	 MAT3_ADD_VEC (vrp1, vrp1, deltavec); break;
       case CHANGE_VPN:
	 vpnalpha += deltavec[0]*M_PI/180.0;
	 vpnbeta += deltavec[1]*M_PI/180.0;
	 MAT3_SET_VEC (vpn1, 
		       sin(vpnalpha)*cos(vpnbeta),
		       sin(vpnbeta)*cos(vpnalpha),
		       cos(vpnalpha) );
	 break;
       case CHANGE_PRP:	
	 deltavec[0] = 0.0;  deltavec[1] = 0.0;
	 MAT3_ADD_VEC (prp1, prp1, deltavec); 
	 if (prp1[2] <= 0.0) {
	    prp1[2] = 0.0001;
	    fprintf (stderr, "PRP limited to positive N.\n");
	 }
	 break;
       case CHANGE_WINDOW:
	 umin1+=deltavec[0]; umax1+=deltavec[0];
	 vmin1+=deltavec[1]; vmax1+=deltavec[1];
	 break;
       case CHANGE_FRONT:
	 fplane1 += deltavec[2]; 
	 if (fplane1 >= 0.0) {
	    fplane1 = -0.0001;
	    fprintf (stderr, "front plane Z limited to negative N.\n");
	 }
	 break;
       case CHANGE_BACK:
	 bplane1 += deltavec[2]; 
	 if (bplane1 >= 0.0) {
	    bplane1 = -0.0001;
	    fprintf (stderr, "back plane Z limited to negative N.\n");
	 }
	 break;
    }
    ShowUsingNewView1();
  }
}
