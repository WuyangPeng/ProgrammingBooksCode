#include "defs.h"
#include "/cs/src/sphigs/src/sphigs/sphigs.h"

main()
{
   matrix vm_matrix,
          vo_matrix;
   point vrp_pt = {60.0, 0.0, 100.0},
         prp_pt = {0.0, 0.0, 100.0};
   vector vpn_vec = {0.0, 0.0, 1.0}, 
          vup_vec = {0.0, 1.0, 0.0};
   point basic_pts[VERTICES];
   vertex_index basic_facets[30] = {0, 3, 2, 1, -1, 1, 2, 6, 5, -1,
		           5, 6, 7, 4, -1, 4, 7, 3, 0, -1,
		           0, 1, 5, 4, -1, 3, 7, 6, 2, -1};

   SPH_begin(SPH_WIDTH, SPH_HEIGHT, 2, 0);
   SPH_evaluateViewOrientationMatrix(
              vrp_pt, vpn_vec, vup_vec, vo_matrix);
   SPH_evaluateViewMappingMatrix(
	      UMIN, UMAX, VMIN, VMAX,
	      PERSPECTIVE,
	      prp_pt, FRONT_DIST, BACK_DIST,
              0.0, 1.0, 0.0, 1.0, 0.0, 1.0,
              vm_matrix);
   SPH_setViewRepresentation(
              FIRST_VIEW, vo_matrix, vm_matrix, 
              0.0, 1.0, 0.0, 1.0, 0.0, 1.0);

   basic_pts[0][0]=0.0; basic_pts[0][1]=0.0; basic_pts[0][2]=0.0;
   basic_pts[1][0]=1.0; basic_pts[1][1]=0.0; basic_pts[1][2]=0.0;
   basic_pts[2][0]=1.0; basic_pts[2][1]=1.0; basic_pts[2][2]=0.0;
   basic_pts[3][0]=0.0; basic_pts[3][1]=1.0; basic_pts[3][2]=0.0;
   basic_pts[4][0]=0.0; basic_pts[4][1]=0.0; basic_pts[4][2]=1.0;
   basic_pts[5][0]=1.0; basic_pts[5][1]=0.0; basic_pts[5][2]=1.0;
   basic_pts[6][0]=1.0; basic_pts[6][1]=1.0; basic_pts[6][2]=1.0;
   basic_pts[7][0]=0.0; basic_pts[7][1]=1.0; basic_pts[7][2]=1.0;

   SPH_setImplicitRegenerationMode (ALLOWED);

   SPH_openStructure(BASIC);
   SPH_polyhedron(VERTICES, FACETS,
		  basic_pts, basic_facets);
   SPH_closeStructure();

   SPH_postRoot(BASIC, 0);
   SRGP_waitEvent(-1);
}

