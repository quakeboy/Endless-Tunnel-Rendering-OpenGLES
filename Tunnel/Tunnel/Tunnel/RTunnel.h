/*
This source code is released by Quakeboy - http://qdevarena.blogspot.com
prasna991@gmail.com

You should not remove this comment notice... please :P
*/
#define QUAKEBOY_IS_AWESOME

#ifndef _RTUNNEL
#define _RTUNNEL

#include <windows.h>	//you can remove these includes when porting to other platforms
#include <gl/gl.h>
#include <gl/glu.h>
#include <math.h>

#define NUMVERTCOMPS	3						//components per vertex
#define NUMTEXCOMPS		2
#define M_PI			3.14159265358979323846	//pi value
#define D_TO_R			0.017453				//multiply any degree by this for its radian value

static GLfloat *vertices, *texels, *normals;
static GLushort *indices;
static GLuint texture1;

static int cross_section_sides = 20;
static int whole_torus_sides = 40;
static float torus_radius = 3.5f;
static float cross_section_radius = 0.75f;
static int totalpoints, totalindex;
static float counter = 0.0f;

void makeTorus(int sides, int cs_sides, float radius, float cs_radius);
void initOGL();
void render();

#endif