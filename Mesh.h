#pragma once

#include<vector>
#include<GL/glew.h>

using namespace std;

class Mesh{
public:
	Mesh();

	void CreateMesh(GLfloat* vertices, unsigned int* indices, unsigned int numOfVertices, unsigned int numOfIndices);
	void RenderMesh();
	void RenderModelMesh();
	void RenderCubeMesh();
	void ClearMesh();

	~Mesh();

private:
	GLuint VAO, VBO, IBO;
	//GLsizei is nothing but int but opengl considers it a variable used to store size of something
	GLsizei indexCount;

};

