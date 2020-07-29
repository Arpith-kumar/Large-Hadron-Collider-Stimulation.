#include "Mesh.h"


Mesh::Mesh() {
	VAO = 0;
	VBO = 0;
	IBO = 0;
	indexCount = 0;
}

void Mesh::CreateMesh(GLfloat* vertices, unsigned int* indices, unsigned int numOfVertices, unsigned int numOfIndices) {
	indexCount = numOfIndices;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//craate a buffer for our ibo
	//IBO same as EBO
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * numOfIndices, indices, GL_STATIC_DRAW);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numOfVertices, vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 5, 0);
	glEnableVertexAttribArray(0);

	// value for our texture co-ordinates @ loc=1 

	//the last param should be a plain ptr so- (void*)
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 5, (void*)(sizeof(vertices[0]) * 3));
	glEnableVertexAttribArray(1);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void Mesh::RenderMesh() {

	glBindVertexArray(VAO);

	//bind ibo
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	//glDrawArrays(GL_TRIANGLES,0,3);
	//draw with element id's
	//(draw mode, count of the indices, format of those indices, 0)
	glDrawElements(GL_TRIANGLE_FAN, indexCount, GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::RenderModelMesh() {
	glBindVertexArray(VAO);

	//bind ibo
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	//glDrawArrays(GL_TRIANGLES,0,3);
	//draw with element id's
	//(draw mode, count of the indices, format of those indices, 0)
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


void Mesh::RenderCubeMesh() {
	glBindVertexArray(VAO);

	//bind ibo
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	//glDrawArrays(GL_TRIANGLES,0,3);
	//draw with element id's
	//(draw mode, count of the indices, format of those indices, 0)
	glDrawElements(GL_QUADS, indexCount, GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::ClearMesh() {

	//in c++ there is no garbage collection so we have to do it manually
	if (IBO != 0) {
		glDeleteBuffers(1, &IBO);
		IBO = 0;
	}

	if (VBO != 0) {
		glDeleteBuffers(1, &VBO);
		VBO = 0;
	}

	if (VAO != 0) {
		glDeleteVertexArrays(1, &VAO);
		VAO = 0;
	}

	indexCount = 0;
}

Mesh::~Mesh() {
	ClearMesh();
}
