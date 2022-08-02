#include "sphigs.h"
#include <stdio.h>
#include <assert.h>

   double vpnalpha, vpnbeta;
   double vupalpha, vupbeta;

   matrix vo_matrix, vm_matrix;
   matrix temp;

   int interaction_mode;  /* 0 = move wireframe, 1 = move filled */

   /* DEFAULT VALUES */
   point vrpdef={35.0,60.0,30.0}, prpdef={0.0,0.0,80.0};
   vector vpndef={0.0,0.0,1.0}, vupvdef={0.0,1.0,0.0};
   double umindef=-50.0, umaxdef=50.0, vmindef=-50.0, vmaxdef=50.0;
   double fplanedef=-0.2, bplanedef=-30000.0;

   /* VIEW 1 (user is playing with these numbers) */
   point vrp1, prp1;
   double umin1, umax1, vmin1, vmax1;
   double fplane1, bplane1;
   vector vpn1, vupv1;

   vector deltavec;

   char keymeas[5];


#define PI  3.141592653589



/* NORMALIZED "ARCHETYPAL" HOUSE */

static point house_vertices[] = {
   { 0.,10.,0. },
   { 8.,16.,0. },
   { 16.,10.,0. },
   { 16.,0.,0. },    /* Use the SPHIGS "point" data-type! */
   { 0.,0.,0. },
   { 0.,10.,-40. },
   { 8.,16.,-40. },
   { 16.,10.,-40. },
   { 16.,0.,-40. },
   { 0.,0.,-40. }
};



/* FACETS ARE VERTEX LISTS counter-clockwise from point of view of
   someone OUTSIDE the house. */

static vertex_index house_facets[] = {
   4,3,2,1,0, -1,
   5,6,7,8,9, -1,
   2,7,6,1,   -1,
   2,3,8,7,   -1,
   3,4,9,8,   -1,
   0,5,9,4,   -1,
   0,1,6,5,   -1
};



#define HOUSE_STRUCT 1
#define STREET_STRUCT 2
#define NEIGHBORHOOD_STRUCT 3


static void CreateNormalizedHouseStructure(void)
{
   int i;


   SPH_openStructure (HOUSE_STRUCT);
   SPH_polyhedron (10, 7, house_vertices, house_facets);
   SPH_closeStructure();
}

#define WriteMessage(s)  	SRGP_text (SRGP_defPoint(15,4), s)
#define WriteUpperMessage(s)  	SRGP_text (SRGP_defPoint(15,20), s)




static void ShowUsingNewView0 (void)
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
       0.0,1.0, 0.0,1.0, 0.0,1.0,
       vm_matrix);

   SPH_setViewRepresentation
      (0,
       vo_matrix, vm_matrix,
       0.0,1.0,  0.0,1.0, 0.0,1.0);
}


static void ShowUsingNewView1 (void)
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
       1.0,1.35,  0.0,0.35, 0.0,1.0,
       vm_matrix);

   SPH_setViewRepresentation
      (1,
       vo_matrix, vm_matrix,
       1.0,1.35,  0.0,0.35, 0.0,1.0);
}

static void RestoreCameraToDefault (void)
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

static void Prompt (void)
{
   fprintf (stderr, prompts[currentchange]);
}



void
main(int argc, char** argv)
{

   int i;


   /* STARTUP SPHIGS */
   SPH_begin (600,400,0,0);

   SPH_setDoubleBufferingFlag (TRUE);

   /*** HERE WE SET UP THE VIEW #1 THAT WILL SHOW A WIREFRAME VERSION OF
        THE PICTURE, THAT CAN BE MANIPULATED BY THE USER. */
   RestoreCameraToDefault();
   ShowUsingNewView1();
   SPH_setViewPointLightSource (0,   0.0, 100.0, 150.0);
   ShowUsingNewView0();




   CreateNormalizedHouseStructure();


   SPH_loadCommonColor (2, "yellow");
   SPH_loadCommonColor (3, "green");
   SPH_loadCommonColor (4, "turquoise");
   SPH_loadCommonColor (5, "pink");
   SPH_loadCommonColor (6, "goldenrod");
   SPH_loadCommonColor (7, "beige");

   SPH_setViewBackgroundColor (1, 7);



   SPH_openStructure (STREET_STRUCT);
   SPH_setInteriorColor (2);
   SPH_translate (0.0,0.0,0.0, temp);
   SPH_executeStructure (HOUSE_STRUCT);
   SPH_closeStructure();




   SPH_openStructure (STREET_STRUCT);
   SPH_setInteriorColor (4);
   for (i=0; i<5; i++) {
      SPH_setInteriorColor (3+i);
      SPH_translate (20.0,0.0,0.0, temp);
      SPH_setModelingTransformation (temp, PRECONCATENATE);
      SPH_executeStructure (HOUSE_STRUCT);
   }
   SPH_closeStructure();


   SPH_openStructure (NEIGHBORHOOD_STRUCT);
   SPH_executeStructure (STREET_STRUCT);
   for (i=0; i<3; i++) {
      SPH_translate(0.0,0.0,-70.0, temp);
      SPH_setModelingTransformation (temp, PRECONCATENATE);
      SPH_executeStructure (STREET_STRUCT);
   }
   SPH_closeStructure();


   SPH_openStructure (NEIGHBORHOOD_STRUCT);
     SPH_scale (1.5, 2.0, 2.0, temp);
     SPH_setModelingTransformation (temp, ASSIGN);
     SPH_rotateY (40.0, temp);
     SPH_setModelingTransformation (temp, PRECONCATENATE);
     SPH_translate (-30.0, 0.0, -150.0, temp);
     SPH_setModelingTransformation (temp, PRECONCATENATE);
     SPH_setInteriorColor (3);
     SPH_setEdgeColor (5);
     SPH_executeStructure (HOUSE_STRUCT);
   SPH_closeStructure();
   
   
   SPH_setRenderingMode (0, LIT_FLAT);
   SPH_setRenderingMode (1, WIREFRAME); 

   SPH_postRoot (NEIGHBORHOOD_STRUCT, 0);
   SPH_postRoot (NEIGHBORHOOD_STRUCT, 1);

   currentchange = CHANGE_VRP;

   fprintf (stderr, "\n\nRead the README file for information on how to\n");
   fprintf (stderr, "   play with the camera.\n\n");
   Prompt();
   interaction_mode = 0;
   vpnalpha=0.0;
   vpnbeta=0.0;
   vupalpha=0.0;
   vupbeta= PI/2.0;
   
   SRGP_setInputMode (KEYBOARD, EVENT);
   SRGP_setKeyboardProcessingMode (RAW);
   
   while (1) {
      SRGP_waitEvent (INDEFINITE);
      SRGP_getKeyboard (keymeas, 3);
      MAT3_SET_VEC (deltavec, 0.0, 0.0, 0.0);
      switch (keymeas[0]) {
       case '1': currentchange = CHANGE_VRP; Prompt(); continue; break;
       case '2': currentchange = CHANGE_VPN; Prompt(); continue; break;
       case '3': currentchange = CHANGE_PRP; Prompt(); continue; break;
       case '4': currentchange = CHANGE_WINDOW; Prompt(); continue; break;
       case '5': currentchange = CHANGE_FRONT; Prompt(); continue; break;
       case '6': currentchange = CHANGE_BACK; Prompt(); continue; break;
       case '7': RestoreCameraToDefault();
       case '8': interaction_mode = ! interaction_mode; break;
	 
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

       case 13:  ShowUsingNewView0(); break;
      }
      
      switch (currentchange) {
       case CHANGE_VRP:	 MAT3_ADD_VEC (vrp1, vrp1, deltavec); break;
       case CHANGE_VPN:
	 vpnalpha += deltavec[0]*PI/180.0;
	 vpnbeta += deltavec[1]*PI/180.0;
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
    if (interaction_mode == 1 )
       ShowUsingNewView0();
  }
}
