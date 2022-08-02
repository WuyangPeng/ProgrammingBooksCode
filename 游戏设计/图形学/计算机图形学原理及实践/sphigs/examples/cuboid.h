#define X 0
#define Y 1
#define Z 2

#define U 0
#define V 1

#define FRONT 0
#define BACK  1

#define WIDTH  0
#define HEIGHT 1

#define PROJ_TYPE PERSPECTIVE

#define NUM_PLANES 4
#define NUM_SHADES 16

#define CUBE_NUM_VERTICES 8
#define CUBE_NUM_FACES    6

typedef enum {
               WORKS_ID = 1,
               VIEW_ID,
               CUBE_ID,
               ROOM_ID,
               ROBOT_ID,
               TARGET1_ID,
               TARGET2_ID,
               TARGET3_ID
             } obj_id;

static int window_size[] = {600, 600};

static double VRP_vals[] = {0.5, 0.5, 0.0};
static double VPN_vals[] = {0.0, 0.0, 1.0};
static double VUV_vals[] = {0.0, 1.0, 0.0};
static double PRP_vals[] = {0.0, 30.0, 103.0};

static double view_map_min[] = {-10.0, -10.0};
static double view_map_max[] = {10.0, 10.0};

static double viewport_min[] = {0.0, 0.0, 0.0};
static double viewport_max[] = {1.0, 1.0, 1.0};

static double clip_dist[] = {100.0, 0.0};

static double cube_min[] = {0.0, 0.0, 0.0};
static double cube_max[] = {1.0, 1.0, 1.0};

static vertex_index cube_faces[] = { 4, 6, 7, 5, -1,
                                     6, 2, 3, 7, -1,
                                     2, 0, 1, 3, -1,
                                     0, 4, 5, 1, -1,
                                     1, 5, 7, 3, -1,
                                     2, 6, 4, 0, -1 };
