#pragma once
#include <glfw3.h>
#include "../glm/glm.hpp"
#include "../glm/ext.hpp"

#include "../dependencies/glCore/gl_core_4_5.h"

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

	void initialiseQuad();

	virtual void draw();

protected:
	unsigned int triCount;
	unsigned int vao, vbo, ibo;
};

