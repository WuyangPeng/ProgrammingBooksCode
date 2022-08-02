/* polygon modeler */

#define MAX_POLYGONS 8
#define MAX_VERTICES 10

typedef int bool;
#define TRUE 1
#define FALSE 0

#include <stdlib.h>
#include <stdio.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void myMouse(int,int, int, int);
void myMotion(int, int);
void myDisplay();
void myReshape(int, int);
void color_menu(int);
void main_menu(int);
int pick_polygon(int x, int y);

void myinit();

/* globals */

/* polygon struct */

typedef struct polygon
{ 
     int color; /* color index */
     bool used; /* TRUE if polygon exists */
     int xmin, xmax, ymin, ymax; /* bounding box */
     float xc, yc; /* center of polygon */
     int nvertices; /* number of vertices */
     int x[MAX_VERTICES]; /* vertices */
     int y[MAX_VERTICES];
} polygon;

/* flags */

bool picking = FALSE; /* true while picking */
bool moving = FALSE; /* true while moving polygon */
int in_polygon = -1; /* not in any  polygon */
int present_color = 0; /* default color */

GLsizei wh = 500, ww = 500; /* initial window size */

int draw_mode = 0; /* drawing mode */

GLfloat colors[8][3]={{0.0, 0.0, 0.0}, {1.0, 0.0, 0.0},{0.0, 1.0, 0.0},
    {0.0, 0.0, 1.0}, {0.0, 1.0, 1.0}, {1.0, 0.0, 1.0}, {1.0, 1.0, 0.0},
    {1.0, 1.0, 1.0}};

polygon polygons[MAX_POLYGONS];


void myReshape(int w, int h)
{

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity(); 
        gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity(); 

        glViewport(0,0,w,h);

        ww = w;
        wh = h; 
}

void myinit()
{
        int  i;

/* set clear color to grey */

        glClearColor(0.5, 0.5, 0.5, 1.0);

/* mark all polygons unused */

        for(i = 0; i<MAX_POLYGONS; i++) polygons[i].used = FALSE;
}



void myMouse(int btn, int state, int x, int y)
{
    int i,j;
    y = wh-y;
    if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN &&!picking&&!moving)

    /* adding vertices */    

    {
        moving = FALSE;
        if(in_polygon>=0) 
        {
             if(polygons[in_polygon].nvertices == MAX_VERTICES)
             {
                 printf("exceeds maximum number vertices\n");
                 exit(0);
             }
             i = polygons[in_polygon].nvertices;
             polygons[in_polygon].x[i] = x;
             polygons[in_polygon].y[i] = y;
             polygons[in_polygon].nvertices++;
        }
    }
    if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN &&picking&&!moving)
    {

    /* delete polygon */

        picking = FALSE;
        moving = FALSE;
        j = pick_polygon(x,y);
        if(j >= 0)
        {
                    polygons[j].used = FALSE;
                    in_polygon = -1;
                    glutPostRedisplay();
        }
    } 
}

int pick_polygon(int x, int y)
{

        /* find first polygon in which we are in bounding box */

        int i;
        for(i=0; i<MAX_POLYGONS; i++)
        {
             if(polygons[i].used)
                if((x>=polygons[i].xmin)&&(x<=polygons[i].xmax)&&(y>=polygons[i].ymin)&&(y<polygons[i].ymax))
                {
                    in_polygon = i;
                    moving = TRUE;
                    return(i);
                }
        printf("not in a polygon\n");
        return(-1);
        }
}

void myMotion(int x, int y)
{

   /* find if we are inside a polugon */

   float dx, dy;
   int i,j;
   if(moving)
   {
       y = wh - y;
       j = pick_polygon(x, y);
       if(j<0) 
          {
                printf("not in a polygon\n");
                return;
           }

       /* if inside then move polygon */

       dx = x - polygons[j].xc;
       dy = y - polygons[j].yc;
       for(i = 0; i< polygons[j].nvertices; i++)
       {
           polygons[j].x[i] += dx;
           polygons[j].y[i] += dy;
       }

      /* update bounding box */

       polygons[j].xc += dx;
       polygons[j].yc += dy;
       if(dx>0) polygons[j].xmax += dx;
         else polygons[j].xmin += dx;
       if(dy>0) polygons[j].ymax += dy;
         else polygons[j].ymin += dy;
       glutPostRedisplay();
    }
}

void color_menu(int index)
{
    present_color =  index;
    if(in_polygon>=0) polygons[in_polygon].color = index;
}

void main_menu(int index)
{
   int i;
   switch(index)
   {
      case(1):  /* create a new polygon */
	{

                moving = FALSE;
   		for(i=0; i<MAX_POLYGONS; i++) if(polygons[i].used == FALSE) break;
    		if(i == MAX_POLYGONS)
    		{
         		printf("exceeeded maximum number of polygons\n");
         		exit(0);
    		}
                polygons[i].color = present_color;
                polygons[i].used = TRUE;
    		polygons[i].nvertices = 0;
    		in_polygon = i;
                picking = FALSE;
                break;
     	}
	case(2):   /* end polygon and find bounding box and center */
	{
                moving = FALSE;
                if(in_polygon>=0)
                {
                   polygons[in_polygon].xmax = polygons[in_polygon].xmin = polygons[in_polygon].x[0];
                   polygons[in_polygon].ymax = polygons[in_polygon].ymin = polygons[in_polygon].y[0];
                   polygons[in_polygon].xc = polygons[in_polygon].x[0];
                   polygons[in_polygon].yc = polygons[in_polygon].y[0];
                   for(i=1;i<polygons[in_polygon].nvertices;i++)
                   {
                     if(polygons[in_polygon].x[i]<polygons[in_polygon].xmin)
                              polygons[in_polygon].xmin = polygons[in_polygon].x[i];
                     else if(polygons[in_polygon].x[i]>polygons[in_polygon].xmax)
                              polygons[in_polygon].xmax = polygons[in_polygon].x[i];
                     if(polygons[in_polygon].y[i]<polygons[in_polygon].ymin)
                              polygons[in_polygon].ymin = polygons[in_polygon].y[i];
                     else if(polygons[in_polygon].y[i]>polygons[in_polygon].ymax)
                              polygons[in_polygon].ymax = polygons[in_polygon].y[i];
                     polygons[in_polygon].xc += polygons[in_polygon].x[i];
                     polygons[in_polygon].yc += polygons[in_polygon].y[i];
                   }
                   polygons[in_polygon].xc = polygons[in_polygon].xc/polygons[in_polygon].nvertices;
                   polygons[in_polygon].yc = polygons[in_polygon].yc/polygons[in_polygon].nvertices;
                }
		in_polygon = -1;
                glutPostRedisplay();
		break;
	}
	case(3):  /* set picking mode */
	{
                picking = TRUE;
                moving = FALSE;
		break;
	}
        case(4):  /* set moving mode */
        {
                moving = TRUE;
                break;
        }
	case(5):  /* exit */
	{
		exit(0);
		break;
	}
   }
}

void myDisplay()
{

    /* display all active polygons */

    int i, j;

    glClear(GL_COLOR_BUFFER_BIT);
    for(i=0; i<MAX_POLYGONS; i++)
    {
       if(polygons[i].used)
       {
           glColor3fv(colors[polygons[i].color]);
           glBegin(GL_POLYGON);
           for(j=0; j<polygons[i].nvertices; j++) glVertex2i(polygons[i].x[j], polygons[i].y[j]);
           glEnd();
       }
    }
    glFlush();
}


int main(int argc, char** argv)
{
    int c_menu;

    glutInit(&argc,argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("polygon modeler");
    glutDisplayFunc(myDisplay);
    myinit ();
    c_menu = glutCreateMenu(color_menu);
    glutAddMenuEntry("Black",0);
    glutAddMenuEntry("Red",1);
    glutAddMenuEntry("Green",2);
    glutAddMenuEntry("Blue",3);
    glutAddMenuEntry("Cyan",4);
    glutAddMenuEntry("Magenta",5);
    glutAddMenuEntry("Yellow",6);
    glutAddMenuEntry("White",7);

    glutCreateMenu(main_menu);
    glutAddMenuEntry("new polygon", 1);
    glutAddMenuEntry("end polygon", 2);
    glutAddMenuEntry("delete polygon", 3);
    glutAddMenuEntry("move polygon", 4);
    glutAddMenuEntry("quit",5);
    glutAddSubMenu("Colors", c_menu);
    glutAttachMenu(GLUT_MIDDLE_BUTTON);

    glutReshapeFunc (myReshape); 
    glutMouseFunc (myMouse);
    glutMotionFunc(myMotion);
    glutMainLoop();

}
