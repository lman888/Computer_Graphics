#pragma once

#include <gl_core_4_5.h>
#include <GLFW\glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>


class Mesh
{
public:
	Mesh() : triCount(0), vao(0), vbo(0), ibo(0) {}
	~Mesh();

	///Our Vertex will need a pos, which we'll use a Vec4 for.
	struct Vertex
	{
		glm::vec4 position;
		glm::vec4 normal;
		glm::vec2 texCoord;
	};

	///Initialises the plane
	void initialiseQuad();
	
	void initialise(unsigned int vertexCount, const Vertex* vertices,
		unsigned int indexCount /*= 0*/,
		unsigned int* indices /*= nullptr*/);

	///TO DO BOX
	void Box();

	///Virtual draw
	virtual void draw();

protected:

	///Variables
	unsigned int triCount;
	unsigned int vao, vbo, ibo;
};

