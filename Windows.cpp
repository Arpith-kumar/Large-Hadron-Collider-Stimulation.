#include "Windows.h"

Windows::Windows(){
	width = 800;
	height = 600;

	for (size_t i = 0; i < 1024; i++) {
		keys[i] = 0;
	}
}

Windows::Windows(GLint windowWidth, GLint windowHeight) {
	width = windowWidth;
	height = windowHeight;

	for (size_t i = 0; i < 1024; i++) {
		keys[i] = 0;
	}
}

int Windows::Initialization() {
	if (!glfwInit()) {
		cerr << "GLFW Initilization failed!";
		glfwTerminate();
		return 1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	/*glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);*/

	//mainWindow = glfwCreateWindow(width, height, "TEST WINDOW", NULL, NULL);
	mainWindow = glfwCreateWindow(width, height, "TEST WINDOW", glfwGetPrimaryMonitor(), nullptr);

	if (!mainWindow) {
		cerr << "GLFW Window creation failed!";
		glfwTerminate();
		return 1;
	}

	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	glfwMakeContextCurrent(mainWindow);

	//handel key and mouse input
	createCallbacks();

	//fixing your cursor to your window
	//(window, what i/p to change, mode we want to set for this i/p, )
	//your cursor will not appear on the screen
	
	//glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {
		cerr << "GLEW Initilization failed!";
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	//enabling depth testing
	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, bufferWidth, bufferHeight);

	//(glfw window, owner of that window)
	//tells which object owns this window
	glfwSetWindowUserPointer(mainWindow, this);
}

void Windows::createCallbacks() {
	glfwSetKeyCallback(mainWindow, handleKeys);
	glfwSetCursorPosCallback(mainWindow, handleMouse);
}

GLfloat Windows::getXChange() {
	GLfloat theChange = XChange;
	XChange = 0.0f;
	return theChange;
}

GLfloat Windows::getYChange() {
	GLfloat theChange = YChange;
	YChange = 0.0f;
	return theChange;
}


void Windows::handleKeys(GLFWwindow* window, int key, int code, int action, int mode) {
	Windows* theWindow = static_cast<Windows*>(glfwGetWindowUserPointer(window));
	
	if (key == GLFW_KEY_ESCAPE &&	action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS) {
			theWindow->keys[key] = true;
			//cout << "Pressed "<<key<<endl;
		}
		else if(action == GLFW_RELEASE){
			theWindow->keys[key] = false;
			//cout << "Released " << key<<endl;
		}
	}

}

void Windows::handleMouse(GLFWwindow* window, double xPos, double yPos) {
	Windows* theWindow = static_cast<Windows*>(glfwGetWindowUserPointer(window));

	if (theWindow->mouseFirstMoved) {
		theWindow->lastX = xPos;
		theWindow->lastY = yPos;
		theWindow->mouseFirstMoved = false;
	}

	theWindow->XChange = xPos - theWindow->lastX;
	theWindow->YChange = theWindow->lastY - yPos;
	/*theWindow->YChange = yPos - theWindow->lastY;*/

	theWindow->lastX = xPos;
	theWindow->lastY = yPos;
	//cout << "X: "<<theWindow->XChange<<"	Y: "<<theWindow->YChange<<endl;
}

Windows::~Windows(){
	glfwDestroyWindow(mainWindow);
	glfwTerminate();
}
