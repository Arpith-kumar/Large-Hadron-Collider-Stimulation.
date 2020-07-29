#include "Shader.h"



Shader::Shader(){
	shaderID = 0;
	uniformModel = 0;
	uniformProjection = 0;
}

void Shader::CreateFromString(const char* vertexCode, const char* fragementCode) {
	CompileShader(vertexCode, fragementCode);
}

void Shader::CreateFromFiles(const char* vertexLocation, const char* fragementLocation) {
	string vertexString = ReadFile(vertexLocation);
	string fragementString = ReadFile(fragementLocation);

	//to character array
	const char* vertexCode = vertexString.c_str();
	const char* fragementCode = fragementString.c_str();

	CompileShader(vertexCode, fragementCode);
}

string Shader::ReadFile(const char* fileLocation) {
	string content;
	ifstream fileStream(fileLocation, ios::in);

	if (!fileStream.is_open()) {
		cerr << "Failed to read" <<fileLocation<<"! File doesn't exist";
	}

	string line = "";
	while (!fileStream.eof()) {
		getline(fileStream, line);
		content.append(line+"\n");
	}

	fileStream.close();
	return content;
}

void Shader::CompileShader(const char* vertexCode, const char* fragementCode) {
	shaderID = glCreateProgram();

	if (!shaderID) {
		printf("Error creating shader program!\n");
		return;
	}

	AddShader(shaderID, vertexCode, GL_VERTEX_SHADER);
	AddShader(shaderID, fragementCode, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(shaderID);
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);

	if (!result) {
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error linking program: '%s'\n", eLog);
		return;
	}

	glValidateProgram(shaderID);
	glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);

	if (!result) {
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error validating program: '%s'\n", eLog);
		return;
	}

	//get the actual id/location of the uniform variable
	//(shader program,name of variable in the shader)
	uniformProjection = glGetUniformLocation(shaderID, "projection");
	uniformModel = glGetUniformLocation(shaderID, "model");
	uniformView = glGetUniformLocation(shaderID, "view");

}

GLuint Shader::GetProjectionLocation() {
	return uniformProjection;
}

GLuint Shader::GetModelLocation() {
	return uniformModel;
}

GLuint Shader::GetViewLocation() {
	return uniformView;
}

void Shader::UseShader() {
	glUseProgram(shaderID);
}

void Shader::ClearShader() {
	if (shaderID != 0) {
		glDeleteProgram(shaderID);
		shaderID = 0;
	}

	uniformModel = 0;
	uniformProjection = 0;

}

void Shader::AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType) {

	GLint theShader = glCreateShader(shaderType);

	const GLchar* theCode[1];
	theCode[0] = shaderCode;

	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);

	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);

	if (!result) {
		glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
		printf("Error compiling the %d shader: '%s'\n", shaderType, eLog);
		return;
	}

	glAttachShader(theProgram, theShader);
}


Shader::~Shader(){
	ClearShader();
}
