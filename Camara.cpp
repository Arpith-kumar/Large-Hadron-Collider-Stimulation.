#include "Camara.h"

Camara::Camara() {}

Camara::Camara(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed){
	position = startPosition;
	worldUp = startUp;
	yaw = startYaw;
	pitch = startPitch;
	front = glm::vec3(0.0f, 0.0f, -1.0);

	moveSpeed = startMoveSpeed;
	turnSpeed = startTurnSpeed;

	update();
}

void Camara::keyControl(bool* keys, GLfloat deltaTime) {
	GLfloat velocity = moveSpeed * deltaTime;
	
	if (keys[GLFW_KEY_W]) {
		position += front * velocity;
	}

	if (keys[GLFW_KEY_S]) {
		position -= front * velocity;
	}

	if (keys[GLFW_KEY_A]) {
		position -= right * velocity;
	}

	if (keys[GLFW_KEY_D]) {
		position += right * velocity;
	}
}

void Camara::mouseControl(GLfloat xChange, GLfloat yChange) {
	xChange *= turnSpeed;
	yChange *= turnSpeed;

	yaw += xChange;
	pitch += yChange;

	if (pitch > 89.0f) {
		pitch = 89.0;
	}
	if (pitch < -89.0f) {
		pitch = -89.0;
	}

	update();
}

glm::mat4 Camara::calculateViewMatrix() {
	return glm::lookAt(position, position + front, up);
}

void Camara::update() {
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	/*when you normalize a vector we are trying to remove the magnitude of the vector 
	but direction will be preserved, it becomes a vector with unit magnitude and some direction*/
	//we just need to know where the front is not how far the front is
	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));

}

Camara::~Camara(){
}
