#pragma once

#include<stdio.h>
#include<string>
#include<iostream>
#include<fstream>

#include<GL/glew.h>

using namespace std;

class Shader{
public:
	Shader();

	void CreateFromString(const char* vertexCode, const char* fragementCode);
	void CreateFromFiles(const char* vertexLocation, const char* fragementLocation);

	string ReadFile(const char* fileLocation);

	GLuint GetProjectionLocation();
	GLuint GetModelLocation();
	GLuint GetViewLocation();

	void UseShader();
	void ClearShader();

	~Shader();

private:
	GLuint shaderID, uniformProjection, uniformModel, uniformView;

	void CompileShader(const char* vertexCode, const char* fragementCode);
	void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
};

