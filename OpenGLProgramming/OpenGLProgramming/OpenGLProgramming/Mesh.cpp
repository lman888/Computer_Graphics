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

	verticles[0].texCoord = { 0, 1 }; ///Bottom Left
	verticles[1].texCoord = { 1, 1};	 ///Bottom eight
	verticles[2].texCoord = { 0, 0};	 ///Top left

	verticles[3].texCoord = { 0, 0};	 ///Top left
	verticles[4].texCoord = { 1, 1 }; ///Bottom right
	verticles[5].texCoord = { 1, 0};	 ///Top right

	verticles[0].normal = { 0, 1, 0, 0 };
	verticles[1].normal = { 0, 1, 0, 0 };
	verticles[2].normal = { 0, 1, 0, 0 };

	verticles[3].normal = { 0, 1, 0, 0 };
	verticles[4].normal = { 0, 1, 0, 0 };
	verticles[5].normal = { 0, 1, 0, 0 };
	
	//fill vertex buffer
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vertex),
				 verticles, GL_STATIC_DRAW);

	//Enable first element as position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE,
						  sizeof(Vertex), 0);

	//Enable second element
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE,
		sizeof(Vertex), (void*)16);

	//Enable third element as texture
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

void Mesh::initialise(unsigned int vertexCount, const Vertex* vertices, unsigned int indexCount, unsigned int * indices)
{
	assert(vao == 0);

	//generate buffers
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);

	//bind vertex array aka a mesh wrapper
	glBindVertexArray(vao);

	//bind vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//fill vertex buffer
	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Vertex),
		vertices, GL_STATIC_DRAW);

	//enable first element as position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 
		sizeof(Vertex), 0);

	//bind indices if there are any
	if (indexCount != 0)
	{
		glGenBuffers(1, &ibo);

		//bind vertex buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

		//fill vertex buffer
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);

		triCount = indexCount / 3;
	}
	else
	{
		triCount = vertexCount / 3;
	}

	//unbind buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
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
