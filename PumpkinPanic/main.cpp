#include <libdragon.h>
#include <GL/gl.h>
#include <GL/gl_integration.h>
#include <malloc.h>
#include <math.h>

#include "cube.hpp"
#include "plane.hpp"
#include "player.hpp"

GLfloat fog_color[] = { 0.3f, 0.1f, 0.6f, 1.f };
float viewDist = 20.f;

static GLuint cubeBuffers[2];
static GLuint planeBuffers[2];
static GLuint textures[4];

Player player = Player();

static const char* texture_paths[4] = {
	"pumpkinSkin.sprite",
	"diamond.sprite",
	"pentagon.sprite",
	"triangle.sprite",
};

sprite_t* load_sprite(const char* path)
{
	int fp = dfs_open(path);
	sprite_t* sprite = (sprite_t*)malloc(dfs_size(fp));
	dfs_read(sprite, 1, dfs_size(fp), fp);
	dfs_close(fp);
	return sprite;
}

void setup()
{
	glGenBuffersARB(2, cubeBuffers);

	glBindBufferARB(GL_ARRAY_BUFFER_ARB, cubeBuffers[0]);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW_ARB);

	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, cubeBuffers[1]);
	glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW_ARB);

	glGenBuffersARB(2, planeBuffers);

	glBindBufferARB(GL_ARRAY_BUFFER_ARB, planeBuffers[0]);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, sizeof(plane_vertices), plane_vertices, GL_STATIC_DRAW_ARB);

	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, planeBuffers[1]);
	glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, sizeof(plane_indices), plane_indices, GL_STATIC_DRAW_ARB);

	glEnable(GL_LIGHT0);
	//glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	//glEnable(GL_MULTISAMPLE_ARB);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	float aspect_ratio = (float)display_get_width() / (float)display_get_height();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1 * aspect_ratio, 1 * aspect_ratio, -1, 1, 1, viewDist);
	//glOrtho(-2*aspect_ratio, 2*aspect_ratio, -2, 2, 5, -5);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	GLfloat light_pos[] = { 0, 0, 0, 1 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

	GLfloat light_diffuse[] = { 1, 1, 1, 1 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.0f);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 1.0f / viewDist);

	GLfloat mat_diffuse[] = { 1, 1, 1, 0.6f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);

	glEnable(GL_FOG);

	glFogfv(GL_FOG_COLOR, fog_color);
	glFogf(GL_FOG_START, 0.0f);
	glFogf(GL_FOG_END, viewDist);

	glGenTextures(4, textures);

	for (uint32_t i = 0; i < 4; i++)
	{
		glBindTexture(GL_TEXTURE_2D, textures[i]);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		sprite_t* sprite = load_sprite(texture_paths[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sprite->width, sprite->height, 0, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1_EXT, sprite->data);
		free(sprite);
	}
}

void draw_cube()
{
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, cubeBuffers[0]);
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, cubeBuffers[1]);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glVertexPointer(3, GL_FLOAT, sizeof(vertex_t), (GLvoid*) (0 * sizeof(float)));
	glTexCoordPointer(2, GL_FLOAT, sizeof(vertex_t), (GLvoid*)(3 * sizeof(float)));
	glNormalPointer(GL_FLOAT, sizeof(vertex_t), (GLvoid*)(5 * sizeof(float)));
	glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(vertex_t), (GLvoid*)(8 * sizeof(float)));

	glDrawElements(GL_TRIANGLES, sizeof(cube_indices) / sizeof(uint16_t), GL_UNSIGNED_SHORT, 0);
}
void draw_plane()
{
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, planeBuffers[0]);
	glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, planeBuffers[1]);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glVertexPointer(3, GL_FLOAT, sizeof(vertex_t), (GLvoid*)(0 * sizeof(float)));
	glTexCoordPointer(2, GL_FLOAT, sizeof(vertex_t), (GLvoid*)(3 * sizeof(float)));
	glNormalPointer(GL_FLOAT, sizeof(vertex_t), (GLvoid*)(5 * sizeof(float)));
	glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(vertex_t), (GLvoid*)(8 * sizeof(float)));

	glDrawElements(GL_TRIANGLES, sizeof(plane_indices) / sizeof(uint16_t), GL_UNSIGNED_SHORT, 0);
}


void draw_band()
{
	glBegin(GL_QUAD_STRIP);

	const uint32_t segments = 16;

	for (uint32_t i = 0; i <= segments; i++)
	{
		float angle = (2 * M_PI / segments) * (i % segments);

		float x = cosf(angle) * 2;
		float z = sinf(angle) * 2;

		glVertex3f(x, -0.2f, z);
		glVertex3f(x, 0.2f, z);
	}

	glEnd();
}

void draw_circle()
{
	glBegin(GL_LINE_LOOP);

	const uint32_t segments = 16;

	for (uint32_t i = 0; i < segments; i++)
	{
		float angle = (2 * M_PI / segments) * (i % segments);

		float x = cosf(angle);
		float z = sinf(angle);

		glVertex3f(x, 1.5f, z);
		glVertex3f(x, 1.5f, z);
	}

	glEnd();
}

void render()
{
	glClearColor(fog_color[0], fog_color[1], fog_color[2], fog_color[3]);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//// band / circle
	//glPushMatrix();

	//glRotatef(rotation * 0.46f, 0, 1, 0);
	//glRotatef(rotation * 1.35f, 1, 0, 0);
	//glRotatef(rotation * 1.81f, 0, 0, 1);

	//glDisable(GL_LIGHTING);
	//glDisable(GL_BLEND);
	//glDisable(GL_CULL_FACE);
	//glDisable(GL_TEXTURE_2D);

	//glColor3f(1.f, 1.f, 1.f);
	//draw_band();
	//glColor3f(0.f, 1.f, 1.f);
	//draw_circle();

	//glPopMatrix();

	glPushMatrix();

	// move the player away from the camera
	glTranslatef(player.pos[0], player.pos[1], player.pos[2]);
	glRotatef(player.rot[0], 1, 0, 0);
	glRotatef(player.rot[1], 0, 0, 1);
	glRotatef(player.rot[2], 0, 1, 0);

	glEnable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, textures[0]);

	draw_cube();

	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, textures[1]);
	for (int i = 0; i < player.obstacles_length; ++i) {
		glPushMatrix();
		glTranslatef((player.obstacles[i].lane - 1) * 2, -2, player.obstacles[i].zpos + player.elapsedFrames *.1f);
		draw_plane();
		glPopMatrix();
	}
}

int main()
{
	debug_init_isviewer();
	debug_init_usblog();

	dfs_init(DFS_DEFAULT_LOCATION);

	display_init(RESOLUTION_320x240, DEPTH_16_BPP, 1, GAMMA_NONE, ANTIALIAS_RESAMPLE_FETCH_ALWAYS);

	gl_init();

	//rdpq_debug_start();
	//rdpq_debug_log(true);

	setup();

	controller_init();

	while (1)
	{
		player.update();

		render();

		gl_swap_buffers();
	}
}
