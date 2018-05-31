#include "Mesh.h"



Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
}

void Mesh::initialiseQuad()
{
	//Check that the mesh is not initialized already
	assert(vao == 0);

	//generate buffers
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);

	//Bind vertex array aka a mesh wrapper
	glBindVertexArray(vao);

	//bind vexter buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//Define 6 vertices for 2 triangles
	Vertex verticles[6];
	verticles[0].position = { -0.5f, 0, 0.5f, 1 };
	verticles[1].position = { 0.5f, 0, 0.5f, 1 };
	verticles[2].position = { -0.5f, 0, -0.5f, 1 };

	verticles[3].position = { -0.5f, 0, -0.5f, 1 };
	verticles[4].position = { 0.5f, 0, 0.5f, 1 };
	verticles[5].position = { 0.5f, 0, -0.5f, 1 };

	Vertex vertices[6];
	vertices[0].texCoord = { 0, 1 }; ///Bottom Left
	vertices[1].texCoord = { 1, 1};	 ///Bottom eight
	vertices[2].texCoord = { 0, 0};	 ///Top left

	vertices[3].texCoord = { 0, 0};	 ///Top left
	vertices[4].texCoord = { 1, 1 }; ///Bottom right
	vertices[5].texCoord = { 1, 0};	 ///Top right
	
	//fill vertex buffer
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vertex),
				 verticles, GL_STATIC_DRAW);

	//Enable first element as position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE,
						  sizeof(Vertex), 0);

	///Enable third element as texture
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
						  sizeof(Vertex), (void*)32);

	//Unbind buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Quad has 2 trianles
	triCount = 2;

	//More to go here
}

void Mesh::Box()
{
	///TO DO
}

void Mesh::draw()
{
	glBindVertexArray(vao);
	//Using indices or just vertices?
	if (ibo != 0)
	{
		glDrawElements(GL_TRIANGLES, 3 * triCount,
					   GL_UNSIGNED_INT, 0);
	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, 3 * triCount);
	}
}
