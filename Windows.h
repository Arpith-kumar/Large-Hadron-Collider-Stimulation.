#pragma once
#include<stdio.h>
#include<iostream>
#include<GL/glew.h>
#include<GLFW/glfw3.h>

using namespace std;

class Windows{
public:
	Windows();

	Windows(GLint windowWidth, GLint windowHeight);

	int Initialization();

	GLfloat getBufferWidth() { return bufferWidth; }
	GLfloat getBufferHeight() { return bufferHeight; }

	bool getShouldClose() { return glfwWindowShouldClose(mainWindow); }
	
	bool* getKeys() { return keys; }

	GLfloat getXChange();
	GLfloat getYChange();
	
	void swapBuffers() { glfwSwapBuffers(mainWindow); }

	~Windows();

private:

	GLFWwindow *mainWindow;
	GLint width, height;
	GLint bufferWidth, bufferHeight;


	//this is covering the range of ASCI values
	bool keys[1024];

	//last values vs current values of X and Y
	GLfloat lastX, lastY, XChange, YChange;

	//checking the initilization movement for the cursor
	bool mouseFirstMoved;

	void createCallbacks();

	//key-actual value of the key b/w 0-1024
	//action-action performed on that key, press/release
	static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);

	static void handleMouse(GLFWwindow* window, double xPos, double yPos);
};

