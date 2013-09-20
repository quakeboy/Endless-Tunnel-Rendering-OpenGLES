#include "RTunnel.h"

void initOGL()
{
	totalpoints = cross_section_sides * whole_torus_sides;
	makeTorus(whole_torus_sides, cross_section_sides, torus_radius, cross_section_radius);

	glViewport(0, 0, 800, 800);	
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glPointSize(2.0f);
	
	glMatrixMode(GL_PROJECTION);
	gluPerspective(120, 1.0f, 0.01, 100);

//	//comment when camera inside
//	glLoadIdentity();
//	glOrthof(-6, 6, -9, 9, -100, 100);

	glMatrixMode(GL_MODELVIEW);
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
}


//This code is written keeping OpenGLES in mind too.. so not using unsupported features
void makeTorus(int sides, int cs_sides, float radius, float cs_radius)
{
	int vertexmemory = sizeof(GLfloat) * sides * NUMVERTCOMPS * cs_sides;
	int texturememory = sizeof(GLfloat) * sides * NUMTEXCOMPS * cs_sides;
	int indexmemory = sizeof(GLushort) * (2 * (sides+1) * cs_sides + cs_sides);	// that + cs_sides is for triangle strip continuation
	
	totalindex = (2 * (sides+1) * cs_sides + cs_sides);
	
	vertices = (GLfloat*)malloc(vertexmemory);
	texels = (GLfloat*)malloc(texturememory);
	indices = (GLushort*) malloc(indexmemory);
	
	int angleincs = 360/sides;
	int cs_angleincs = 360/cs_sides;
	float currentradius, zval;
	
	int t=0;
	
	//calculating the vertex array
	for (int j=0, m=0; j<360; j+=cs_angleincs, m++)
	{
		currentradius = radius + (cs_radius * cosf(j * D_TO_R ));
		zval = cs_radius * sinf(j * D_TO_R );
		
		int findex = (m*sides*3);
		for (int i=0, n=0; i<360; i+=angleincs, n++)
		{
			vertices[findex+ n*3] = currentradius * cosf(i * D_TO_R );
			vertices[findex+ n*3 +1] = currentradius * sinf(i * D_TO_R );
			vertices[findex+ n*3 +2] = zval;
			
			texels[t++] = n/2.0f;
			texels[t++] = m/25.0f;
		}
	}
	
	int i=0, n=0;
	//calculating the index array
	for (;i<cs_sides; i++) {
		for (int j=0; j<sides; j++) {
			indices[n++] = i * sides + j;
			indices[n++] = ((i+1)%cs_sides) * sides + j;
		}
		
		indices[n++] = i * sides;
		indices[n++] = ((i+1)%cs_sides) * sides;
		indices[n++] = ((i+1)%cs_sides) * sides;
	}
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	counter+=0.37f;
	counter = counter>360 ? 0:counter;
	glLoadIdentity();

	//glTranslatef(0.0f, 0.0f, -6.0f);
	gluLookAt(-3.5f, 0.0f, 0.0f, -3.5f, 1.0f, 0.0f, sinf(counter*D_TO_R), 0.0f, cosf(counter*D_TO_R));

	glRotatef(counter*2, 0.0f, 0.0f, 1.0f);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, texels);

/*
	// SAFELY UNCOMMENT TO SEE SOME MAGIC
	glMatrixMode(GL_TEXTURE);
	glTranslatef(0.0f, -0.0015f, 0.0f);
	glMatrixMode(GL_MODELVIEW);
*/

	glDrawElements(GL_TRIANGLE_STRIP, totalindex, GL_UNSIGNED_SHORT, indices);	
	//glDrawArrays(GL_POINTS, 0, (totalpoints));	//to see just the points
}

#ifndef QUAKEBOY_IS_AWESOME
#error QUAKEBOY_HAS_TO_BE_AWESOME
#endif