#include <gl\gl.h>
#include <gl\glu.h>

#define NEAR_PLANE 0.1f
#define NEAR_PLANE_THRESHOLD 0.0f
#define FAR_PLANE 3000.0f

extern HGLRC m_hRC;

int CreateView(HDC hdc);
void ResizeView(int sx,int sy);
void DeleteView();
void InitView();

