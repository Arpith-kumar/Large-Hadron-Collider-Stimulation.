#pragma once

#include<GL/glew.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<GLFW/glfw3.h>


class Camara{
public:

	Camara();

	Camara(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed);
	
	void keyControl(bool* keys,GLfloat deltaTime);
	
	//how much users moved in x-axis and y-axis respectively
	void mouseControl(GLfloat xChange, GLfloat yChange);

	glm::mat4 calculateViewMatrix();
	
	~Camara();

private:

	//position of camara
	glm::vec3 position;

	//front position of cam
	glm::vec3 front;

	//up position of cam
	glm::vec3 up;

	//right position of cam
	glm::vec3 right;

	//which way we are going to rotate in reference to
	//frame of reference
	glm::vec3 worldUp;

	GLfloat yaw, pitch;

	GLfloat moveSpeed, turnSpeed;

	//updates values as soon as it changes
	void update();
};

