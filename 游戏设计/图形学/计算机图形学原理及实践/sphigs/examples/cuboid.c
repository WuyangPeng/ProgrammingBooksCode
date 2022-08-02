#include <stdio.h>
#include <sphigs.h>
#include "cuboid.h"

void
init_cube()
{
  point cube_vertices[CUBE_NUM_VERTICES];

  SPH_defPoint(cube_vertices[0],cube_min[X],cube_min[Y],cube_min[Z]);
  SPH_defPoint(cube_vertices[1],cube_min[X],cube_min[Y],cube_max[Z]);
  SPH_defPoint(cube_vertices[2],cube_min[X],cube_max[Y],cube_min[Z]);
  SPH_defPoint(cube_vertices[3],cube_min[X],cube_max[Y],cube_max[Z]);
  SPH_defPoint(cube_vertices[4],cube_max[X],cube_min[Y],cube_min[Z]);
  SPH_defPoint(cube_vertices[5],cube_max[X],cube_min[Y],cube_max[Z]);
  SPH_defPoint(cube_vertices[6],cube_max[X],cube_max[Y],cube_min[Z]);
  SPH_defPoint(cube_vertices[7],cube_max[X],cube_max[Y],cube_max[Z]);

  SPH_openStructure(CUBE_ID);
  SPH_setEdgeColor(COLOR_BLACK);
  SPH_polyhedron(CUBE_NUM_VERTICES,CUBE_NUM_FACES,cube_vertices,cube_faces);
  SPH_closeStructure();
}

/*
 *  Okay, let's see if I understood the stuff in the book.
 *
 *  Start vanilla. Look straight down the z-axis at point {0.5, 0.5, 0.0}.
 *  The up-vector (vuv) is the vector {0.0, 1.0, 0.0}. From these, we
 *  determine the view orientation matrix (vom). Then we get the projection
 *  reference point (prp) and the view mapping matrix (vmm). Finally, we
 *  set the view representation.
 */

void
init_view()
{
  point vrp, prp;
  vector vpn, vuv;
  matrix vom, vmm;

  SPH_defPoint(vrp,VRP_vals[X],VRP_vals[Y],VRP_vals[Z]);
  SPH_defPoint(vpn,VPN_vals[X],VPN_vals[Y],VPN_vals[Z]);
  SPH_defPoint(vuv,VUV_vals[X],VUV_vals[Y],VUV_vals[Z]);

  SPH_evaluateViewOrientationMatrix(vrp,vpn,vuv,vom);

  SPH_defPoint(prp,PRP_vals[X],PRP_vals[Y],PRP_vals[Z]);

  SPH_evaluateViewMappingMatrix(view_map_min[U],view_map_max[U],
                                view_map_min[V],view_map_max[V],
                                PROJ_TYPE,
                                prp,
                                clip_dist[FRONT],clip_dist[BACK],
                                viewport_min[X],viewport_max[X],
                                viewport_min[Y],viewport_max[Y],
                                viewport_min[Z],viewport_max[Z],
                                vmm);

  SPH_setViewRepresentation(VIEW_ID, vom, vmm,
                            viewport_min[X],viewport_max[X],
                            viewport_min[Y],viewport_max[Y],
                            viewport_min[Z],viewport_max[Z]);
}

/*
 *  Also a stub.
 */
void
init_room()
{
}

/*
 *  The robot is currently just a cube. Gotta start somewhere.
 */

void
init_robot()
{
}

/*
 *  There are currently no targets. This is a stub.
 */

void
init_targets()
{
}

void
start()
{
  SPH_begin(window_size[WIDTH],window_size[HEIGHT],NUM_PLANES,NUM_SHADES);
}

/*
 *  Initialize the view, room, robot, and any targets. As if you couldn't
 *  tell.
 */

void
init_all()
{
  init_cube();
printf("Initialized cube.\n");
  init_view();
printf("Initialized view.\n");
  init_room();
printf("Initialized room.\n");
  init_robot();
printf("Initialized robot.\n");
  init_targets();
printf("Initialized targets.\n");
printf("Posting!\n");
  SPH_postRoot(CUBE_ID,VIEW_ID);
}

void
done()
{
  SPH_unpostAllRoots (VIEW_ID);
  SPH_end ();
}

/*
 *  Practice good modularity. main() just calls the functions that do the
 *  real work.
 */

void
main()
{
  start();
  init_all();
  sleep(10);
  done();
}
