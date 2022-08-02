// -------------------------
// matrix structure
typedef float matrix[3][3];

// -------------------------
// bone structure
typedef struct bone_struct {
  int    id;                     // ID
  char   name[30];               // name 
  float  direction[3];           // direction to translate local origin
  float  length;                 // distance to translate local origin
  float  orientation[3];         // angles to rotate local coordinate system
  char   axisOrder[10];          // order of roations (ignored for now)
  int    numberOfDOFs;           // number of DOFs of joint
  char   dof[3][10];             // names of DOFs (ignored for now)
  float  *dofPtr;                // pointer into dofValue list
  float  *dofValues[3];          // DOF values (from .AMC file)
  float  limit[3][3];            // limits on DOFs
  struct bone_struct   *next;    // linear linked list of bones
  struct bone_struct   *child;   // child of this bone
  struct bone_struct   *sibling; // sibling of this bone
  float  position[3];            // origin of local coordinate system
  matrix tucs;                   // (local) transformed unit coordinate system
} bone_td;

// -------------------------
// root structure
typedef struct root_struct {
  char   order[30];
  char   axisOrder[10];         
  float  *position[3];
  float  *orientation[3];
  bone_td *child;
} root_td;

