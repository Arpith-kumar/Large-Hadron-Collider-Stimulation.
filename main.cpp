#define STB_IMAGE_IMPLEMENTATION

#include<stdio.h>
#include<iostream>
#include<string.h>
#include<string> 
#include<vector>
//for math oprations abs()
#include<cmath>
#include<Windows.h>
#include<GL/glew.h>
#include<GLFW/glfw3.h>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include "Mesh.h"
#include "Shader.h"
#include "Windows.h"
#include "Camara.h"
#include "Texture.h"
#include "Model.h"
#include "colormod.h"

using namespace std;
typedef float point[3];

const float toRadians = 3.1415926535897932384626433832795 / 180.0f;
float curAngle = 0.0f;
float curAngle01 = 0.0f;
float transDist = 0.0f;
float explosionAngle = 0.0f;
float offset = 0.0f;
float offsetInc = 0.05;
int ticks = 0;
bool flag;

float y01 = -10.0f;
float x01 = 0.0f;
float turnThreshY = 0.0f;
float at01 = 0.0f;
float turnThreshX = -12.0f;

float y02 = -10.5f;
float x02 = 0.0f;
float turnThreshY02 = 0.0f;
float at02 = 0.0f;
float turnThreshX02 = -12.0f;

float y03 = -11.0f;
float x03 = 0.0f;
float turnThreshY03 = 0.0f;
float at03 = 0.0f;
float turnThreshX03 = -12.0f;

float y04 = -11.5f;
float x04 = 0.0f;
float turnThreshY04 = 0.0f;
float at04 = 0.0f;
float turnThreshX04 = -12.0f;

Windows mainWindow;
vector<Mesh*> meshList;
vector<Shader*> shaderList;
Camara camera;
Texture atomTexture, metalTexture, metalTexture01, metalTexture02, brickTEX;
Model car, cube, hydrogenTank, cylinder, reactor, pipeline;

//delta time calculation
//if you had to move 5pix/sec but it moves 5pix/half-a-sec u 
//reduce the pix movement to 2.5pix
GLfloat deltaTime = 0.0;
GLfloat lastTime = 0.0f;


//adding a uniform variable inside this shader
//clamp-if value is not b/w 0-1 put it b/w 0-1
static const char* vShader = "Shader/shader.vert";
static const char* fShader = "Shader/shader.frag";


//----------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------


void createObjects() {

	std::vector<float> vertices;
	std::vector<GLuint> indices;

	int stacks = 20;
	int slices = 20;
	GLfloat Radius = 0.3;

	const float PI = glm::pi <float>();


	unsigned int parIndices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat parVertices[] = {
		//	x      y      z			u	  v
			-1.0f, -1.0f, 0.0f,		0.0f, 0.0f,
			0.0f, -1.0f, 1.0f,		0.5f, 0.0f,
			1.0f, -1.0f, 0.0f,		1.0f, 0.0f,
			0.0f, 1.0f, 0.0f,		0.5f, 1.0f
	};


	// loop through stacks.
	for (int i = 0; i <= stacks; ++i) {

		float V = (float)i / (float)stacks;
		float phi = V * PI;

		// loop through the slices.
		for (int j = 0; j <= slices; ++j) {

			float U = (float)j / (float)slices;
			float theta = U * (PI * 2);

			// use spherical coordinates to calculate the positions.
			float x = cos(theta) * sin(phi);
			float y = cos(phi);
			float z = sin(theta) * sin(phi);

			vertices.push_back(x * Radius);
			vertices.push_back(y * Radius);
			vertices.push_back(z * Radius);
		}
	}

	// Calc The Index Positions
	for (int i = 0; i < slices * stacks + slices; ++i) {
		indices.push_back(GLuint(i));
		indices.push_back(GLuint(i + slices + 1));
		indices.push_back(GLuint(i + slices));

		indices.push_back(GLuint(i + slices + 1));
		indices.push_back(GLuint(i));
		indices.push_back(GLuint(i + 1));
	}

	const int vert_size = vertices.size();
	const int indi_size = indices.size();

	GLfloat vertices01[] = {
		-1.0f,1.0f,0.0f,	0.0f,1.0f,
		-1.0f,-1.0f,0.0f,	0.0f,0.0f,
		1.0f,1.0f,0.0f,		1.0f,1.0f,
		1.0f,-1.0f,0.0f,	1.0f,0.0f,
		-1.0f,1.0f,-2.0f,	1.0f,1.0f,
		-1.0f,-1.0f,-2.0f,	1.0f,0.0f,
		1.0f,1.0f,-2.0f,	0.0f,1.0f,
		1.0f,-1.0f,-2.0f,	0.0f,0.0f
	};
	unsigned int indices01[] = {
		0, 2, 3, 1,
		2, 6, 7, 3,
		6, 4, 5, 7,
		4, 0, 1, 5,
		0, 4, 6, 2,
		1, 5, 7, 3
	};

	Mesh * obj0 = new Mesh();
	obj0->CreateMesh(&vertices[0], &indices[0], vert_size, indi_size);
	meshList.push_back(obj0);

	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(&vertices[0], &indices[0], vert_size, indi_size);
	meshList.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(&vertices[0], &indices[0], vert_size, indi_size);
	meshList.push_back(obj2);

	Mesh* obj3 = new Mesh();
	obj3->CreateMesh(&vertices[0], &indices[0], vert_size, indi_size);
	meshList.push_back(obj3);

	Mesh* obj4 = new Mesh();
	obj4->CreateMesh(&vertices[0], &indices[0], vert_size, indi_size);
	meshList.push_back(obj4);

	Mesh* obj5 = new Mesh();
	obj5->CreateMesh(&vertices[0], &indices[0], vert_size, indi_size);
	meshList.push_back(obj5);

	Mesh* obj6 = new Mesh();
	obj6->CreateMesh(&vertices[0], &indices[0], vert_size, indi_size);
	meshList.push_back(obj6);

	Mesh* obj7 = new Mesh();
	obj7->CreateMesh(&vertices[0], &indices[0], vert_size, indi_size);
	meshList.push_back(obj7);

	Mesh* obj8 = new Mesh();
	obj8->CreateMesh(&vertices[0], &indices[0], vert_size, indi_size);
	meshList.push_back(obj8);

	Mesh* obj9 = new Mesh();
	obj9->CreateMesh(&vertices[0], &indices[0], vert_size, indi_size);
	meshList.push_back(obj9);

	//room
	Mesh* obj10 = new Mesh();
	obj10->CreateMesh(vertices01, indices01, 40, 24);
	meshList.push_back(obj10);


	//electron extractor
	Mesh* obj11 = new Mesh();
	obj11->CreateMesh(vertices01, indices01, 40, 24);
	meshList.push_back(obj11);

	//explosion particles
	Mesh* obj12 = new Mesh();
	meshList.push_back(obj12);
	obj12->CreateMesh(parVertices, parIndices, 20, 12);
}


void CreateShaders() {
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(shader1);
}

int main(int argc, char* argv[]){
	mainWindow = Windows(1920, 1080);
	mainWindow.Initialization();

	createObjects();
	CreateShaders();

	camera = Camara(glm::vec3(0.0f, 8.0f, -18.0f), glm::vec3(0.0f, 1.0f, 0.0), 100.0f, -30.0f, 5.0f, 0.5f);
	//camera = Camara(glm::vec3(0.0f, 0.0f, -15.0f), glm::vec3(0.0f, 1.0f, 0.0), -90.0f, 0.0f, 5.0f, 0.5f);


	//set-up texture

	brickTEX= Texture("Textures/brick.png");
	brickTEX.LoadTextureA();

	atomTexture = Texture("Textures/atom01.jpg");
	atomTexture.LoadTexture();

	metalTexture = Texture("Textures/metal.png");
	metalTexture.LoadTexture();

	metalTexture01 = Texture("Textures/h2-tex.jpg");
	metalTexture01.LoadTexture();

	metalTexture02 = Texture("Textures/MetalGalvanized.jpg");
	metalTexture02.LoadTexture();

	car = Model(1);
	car.LoadModel("Models/torus.obj");

	hydrogenTank = Model(1);
	hydrogenTank.LoadModel("Models/Water_Tank_BI.obj");

	cylinder = Model(0);
	cylinder.LoadModel("Models/cylinder.obj");

	reactor = Model(0);
	reactor.LoadModel("Models/scanner.obj");

	pipeline = Model(0);
	pipeline.LoadModel("Models/pipeline.obj");

	/*cube = Model();
	cube.LoadModel("Models/cube.obj", 1);*/

	GLuint uniformModel = 0, uniformProjection = 0, uniformView = 0;

	//(standard fov,aspect ratio,near,far)
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / (GLfloat)mainWindow.getBufferHeight(),0.1f,100.0f);

	cout <<"\nCurrently in Use:"<<endl;
	cout << "\n(OpenGl, Graphics, Driver Version)" << endl;
	cout << glGetString(GL_VERSION) << endl;

	Color::Modifier red(Color::FG_RED);
	Color::Modifier def(Color::FG_DEFAULT);
	cout << "This ->" << red << (char)254u << def << "<- is red." << endl;
	std::cout << (char)254u;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	// you can loop k higher to see more color choices
	//for (int k = 1; k < 2; k++)
	//{
	//	// pick the colorattribute k you want
	//	SetConsoleTextAttribute(hConsole, k);
	//	cout << k << " I want to be nice today!";
	//}


	while (!mainWindow.getShouldClose()){
		
		//offset += offsetInc;

		//return current time in seconds
		GLfloat now = glfwGetTime();

		deltaTime = now - lastTime;
		lastTime = now;
		 

		glfwPollEvents();

		camera.keyControl(mainWindow.getKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		//for main collider
		if (curAngle >=357.0f || curAngle<=5.0f) {
			curAngle += 0.01f;
		}
		else {
			curAngle += 0.3f;
		}

		//explosion trigger
		if (curAngle <=0.1f) {
			transDist = 0.0f;
		}
		
		//sub-collider
		if (ticks>2){
			curAngle01 += 0.5f;
		}
		else if (ticks > 6) {
			curAngle01 += 1.0f;
		}
		else {
			curAngle01 += 0.3f;
		}

		

		if (curAngle>=360) {
			curAngle -= 360;
		}

		if (curAngle01 >= 360) {
			ticks += 1;
			curAngle01 -= 360;
		}
	
		glClearColor(0.0f,0.0f,1.0f,0.4f);
		//clearing both color buffer bit and depth buffer bit
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		

		shaderList[0]->UseShader();
		uniformModel = shaderList[0]->GetModelLocation();
		uniformProjection = shaderList[0]->GetProjectionLocation();
		uniformView = shaderList[0]->GetViewLocation();



		//matrix 4x4 identity matrix
		glm::mat4 model;
		//(model, angle in rad, axis w.r.t to rotate)
		model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(5.0f, 0.0f, 0.0f));
		//scaling
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		
		//Matrix that is going to hold 4 float values
		//(loc of the variable,no.of model matrix,transpose,pointer that points to our model)
		//glm::value_ptr-because we cannot pass the raw value stored by glm to the shaders
		glUniformMatrix4fv(uniformModel,1,GL_FALSE,glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		atomTexture.UseTexture();
		meshList[0]->RenderMesh();


		//--------------------------------------------------------------------------
		model = glm::mat4();
		model = glm::translate(model, glm::vec3(-15.25f, -12.5f, 0.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		hydrogenTank.RenderModel();

		//---------------------------------------------------------------

		//--------------------------------------------------------------------------
		model = glm::mat4();
		model = glm::translate(model, glm::vec3(6.15f, -0.5f, 1.0f));
		model = glm::rotate(model, (0)* toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.35f, 0.35f, 0.35f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		reactor.RenderModel();

		//-----------------------------------------------------------------
		model = glm::mat4();
		model = glm::translate(model, glm::vec3(-6.8f, 0.0f, 0.0f));
		model = glm::rotate(model, (90) * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cylinder.RenderModel();

		//-----------------------------------------------------------------
		model = glm::mat4();
		model = glm::translate(model, glm::vec3(-15.25f, -10.25f, 0.0f));
		//model = glm::rotate(model, (90) * toRadians, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pipeline.RenderModel();


		//--------------------------------------------------------------------------


		model = glm::mat4();
		model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(5.0f, 0.2f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		atomTexture.UseTexture();
		meshList[1]->RenderMesh();
		//-----------------------------------------------------------------

		model = glm::mat4();
		model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(5.0f, -0.2f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		atomTexture.UseTexture();
		meshList[2]->RenderMesh();

		//-----------------------------------------------------------------

		model = glm::mat4();
		model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(5.2f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		atomTexture.UseTexture();
		meshList[3]->RenderMesh();

		//-----------------------------------------------------------------

		model = glm::mat4();
		model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(4.8f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		atomTexture.UseTexture();
		meshList[4]->RenderMesh();


		//-----------------------------------------------------------------
		//-----------------------------------------------------------------
		//-----------------------------------------------------------------
		//-----------------------------------------------------------------
		
		model = glm::mat4();
		model = glm::rotate(model, -(curAngle * toRadians), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(5.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		atomTexture.UseTexture();
		meshList[5]->RenderMesh();
		//---------------------------------------------------------------
		model = glm::mat4();
		model = glm::rotate(model, -(curAngle * toRadians), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(5.0f, 0.2f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		atomTexture.UseTexture();
		meshList[6]->RenderMesh();
		//-----------------------------------------------------------------

		model = glm::mat4();
		model = glm::rotate(model, -(curAngle * toRadians), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(5.0f, -0.2f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		atomTexture.UseTexture();
		meshList[7]->RenderMesh();
		//-----------------------------------------------------------------

		model = glm::mat4();
		model = glm::rotate(model, -(curAngle * toRadians), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(5.2f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		atomTexture.UseTexture();
		meshList[8]->RenderMesh();

		//-----------------------------------------------------------------

		model = glm::mat4();
		model = glm::rotate(model, -(curAngle * toRadians), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(4.8f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		atomTexture.UseTexture();
		meshList[9]->RenderMesh();


		//--------------------------------------------------------------------------
		model = glm::mat4();
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, (curAngle)* toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.85f, 0.85f, 0.85f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		car.RenderModel();

		//MIN-TORUS
		//---------------------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------------------
		//--------------------------------------------------------------------------------------------
		//---------------------------------------------------------------------------------------------
		model = glm::mat4();
		model = glm::translate(model, glm::vec3(-10.0f, 0.0f, 0.0f));

		model = glm::rotate(model, curAngle01 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		atomTexture.UseTexture();
		meshList[0]->RenderMesh();
		//---------------------------------------------------------------

		model = glm::mat4();
		model = glm::translate(model, glm::vec3(-10.0f, 0.0f, 0.0f));

		model = glm::rotate(model, curAngle01 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(2.0f, 0.1f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		atomTexture.UseTexture();
		meshList[1]->RenderMesh();
		//-----------------------------------------------------------------

		model = glm::mat4();
		model = glm::translate(model, glm::vec3(-10.0f, 0.0f, 0.0f));

		model = glm::rotate(model, curAngle01 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(2.0f, -0.1f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		atomTexture.UseTexture();
		meshList[2]->RenderMesh();

		//-----------------------------------------------------------------

		model = glm::mat4();
		model = glm::translate(model, glm::vec3(-10.0f, 0.0f, 0.0f));

		model = glm::rotate(model, curAngle01 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(2.1f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		atomTexture.UseTexture();
		meshList[3]->RenderMesh();

		//-----------------------------------------------------------------

		model = glm::mat4();
		model = glm::translate(model, glm::vec3(-10.0f, 0.0f, 0.0f));

		model = glm::rotate(model, curAngle01 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(1.9f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		atomTexture.UseTexture();
		meshList[4]->RenderMesh();


		//-----------------------------------------------------------------
		//-----------------------------------------------------------------
		//-----------------------------------------------------------------
		//-----------------------------------------------------------------

		model = glm::mat4();
		model = glm::translate(model, glm::vec3(-10.0f, 0.0f, 0.0f));

		model = glm::rotate(model, (curAngle01 * toRadians), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.2f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		atomTexture.UseTexture();
		meshList[5]->RenderMesh();
		//---------------------------------------------------------------
		model = glm::mat4();
		model = glm::translate(model, glm::vec3(-10.0f, 0.0f, 0.0f));

		model = glm::rotate(model, (curAngle01 * toRadians), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(2.0f, 0.1f, 0.2f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		atomTexture.UseTexture();
		meshList[6]->RenderMesh();
		//-----------------------------------------------------------------

		model = glm::mat4();
		model = glm::translate(model, glm::vec3(-10.0f, 0.0f, 0.0f));

		model = glm::rotate(model, (curAngle01 * toRadians), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(2.0f, -0.1f, 0.2f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		atomTexture.UseTexture();
		meshList[7]->RenderMesh();
		//-----------------------------------------------------------------

		model = glm::mat4();
		model = glm::translate(model, glm::vec3(-10.0f, 0.0f, 0.0f));

		model = glm::rotate(model, (curAngle01 * toRadians), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(2.1f, 0.0f, 0.2f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		atomTexture.UseTexture();
		meshList[8]->RenderMesh();

		//-----------------------------------------------------------------

		model = glm::mat4();
		model = glm::translate(model, glm::vec3(-10.0f, 0.0f, 0.0f));

		model = glm::rotate(model, (curAngle01 * toRadians), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(1.9f, 0.0f, 0.2f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		atomTexture.UseTexture();
		meshList[9]->RenderMesh();


		//--------------------------------------------------------------------------
		model = glm::mat4();
		model = glm::translate(model, glm::vec3(-10.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, (curAngle)* toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.35f, 0.35f, 0.35f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		car.RenderModel();

		//-----------------------------------------------------------------
		//-----------------------------------------------------------------
		//-----------------------------------------------------------------
		//-----------------------------------------------------------------
		
		//room
		model = glm::mat4();
		model = glm::translate(model, glm::vec3(-5.0f, 0.0f, 10.0f));
		model = glm::scale(model, glm::vec3(20.5f, 20.5f, 20.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		metalTexture02.UseTexture();
		meshList[10]->RenderCubeMesh();

		//electron extractor
		model = glm::mat4();
		model = glm::translate(model, glm::vec3(-15.25f, -5.0f, 1.0f));
		//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		metalTexture.UseTexture();
		meshList[10]->RenderCubeMesh();

		//collision start
		//-----------------------------------------------------------------
		//-----------------------------------------------------------------
		//-----------------------------------------------------------------
		//-----------------------------------------------------------------

		model = glm::mat4();
		model = glm::translate(model, glm::vec3(5.0f, -0.0001f, 0.0f));
		model = glm::translate(model, glm::vec3(transDist, 0.0f, 0.0f));
		model = glm::rotate(model, (explosionAngle)* toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		atomTexture.UseTexture();
		meshList[12]->RenderModelMesh();

		model = glm::mat4();
		model = glm::translate(model, glm::vec3(5.0f, -0.0001f, 0.0f));
		model = glm::translate(model, glm::vec3(-transDist, 0.0f, 0.0f));
		model = glm::rotate(model, (-explosionAngle) * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		atomTexture.UseTexture();
		meshList[12]->RenderModelMesh();

		model = glm::mat4();
		model = glm::translate(model, glm::vec3(5.0f, -0.0001f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, transDist, 0.0f));
		model = glm::rotate(model, (explosionAngle)* toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		atomTexture.UseTexture();
		meshList[12]->RenderModelMesh();

		model = glm::mat4();
		model = glm::translate(model, glm::vec3(5.0f, -0.0001f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, -transDist, 0.0f));
		model = glm::rotate(model, (-explosionAngle) * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		atomTexture.UseTexture();
		meshList[12]->RenderModelMesh();

		model = glm::mat4();
		model = glm::translate(model, glm::vec3(5.0f, -0.0001f, 0.0f));
		model = glm::translate(model, glm::vec3(transDist, transDist, 0.0f));
		model = glm::rotate(model, (-explosionAngle) * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		atomTexture.UseTexture();
		meshList[12]->RenderModelMesh();

		model = glm::mat4();
		model = glm::translate(model, glm::vec3(5.0f, -0.0001f, 0.0f));
		model = glm::translate(model, glm::vec3(-transDist, transDist, 0.0f));
		model = glm::rotate(model, (-explosionAngle) * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		atomTexture.UseTexture();
		meshList[12]->RenderModelMesh();

		model = glm::mat4();
		model = glm::translate(model, glm::vec3(5.0f, -0.0001f, 0.0f));
		model = glm::translate(model, glm::vec3(-transDist, -transDist, 0.0f));
		model = glm::rotate(model, (-explosionAngle) * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		atomTexture.UseTexture();
		meshList[12]->RenderModelMesh();

		model = glm::mat4();
		model = glm::translate(model, glm::vec3(5.0f, -0.0001f, 0.0f));
		model = glm::translate(model, glm::vec3(transDist, -transDist, 0.0f));
		model = glm::rotate(model, (-explosionAngle) * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		atomTexture.UseTexture();
		meshList[12]->RenderModelMesh();

		model = glm::mat4();
		model = glm::translate(model, glm::vec3(5.0f, -0.0001f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, -transDist, transDist));
		model = glm::rotate(model, (explosionAngle)* toRadians, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		atomTexture.UseTexture();
		meshList[12]->RenderModelMesh();

		model = glm::mat4();
		model = glm::translate(model, glm::vec3(5.0f, -0.0001f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, -transDist, -transDist));
		model = glm::rotate(model, (explosionAngle)* toRadians, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		atomTexture.UseTexture();
		meshList[12]->RenderModelMesh();

		model = glm::mat4();
		model = glm::translate(model, glm::vec3(5.0f, -0.0001f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, transDist, -transDist));
		model = glm::rotate(model, (explosionAngle)* toRadians, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		atomTexture.UseTexture();
		meshList[12]->RenderModelMesh();

		model = glm::mat4();
		model = glm::translate(model, glm::vec3(5.0f, -0.0001f, 0.0f));
		model = glm::translate(model, glm::vec3(transDist, transDist, transDist));
		model = glm::rotate(model, (explosionAngle)* toRadians, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		atomTexture.UseTexture();
		meshList[12]->RenderModelMesh();

		model = glm::mat4();
		model = glm::translate(model, glm::vec3(5.0f, -0.0001f, 0.0f));
		model = glm::translate(model, glm::vec3(transDist, transDist, -transDist));
		model = glm::rotate(model, (-explosionAngle) * toRadians, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		atomTexture.UseTexture();
		meshList[12]->RenderModelMesh();

		model = glm::mat4();
		model = glm::translate(model, glm::vec3(5.0f, -0.0001f, 0.0f));
		model = glm::translate(model, glm::vec3(-transDist, transDist, -transDist));
		model = glm::rotate(model, (explosionAngle)* toRadians, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		atomTexture.UseTexture();
		meshList[12]->RenderModelMesh();

		model = glm::mat4();
		model = glm::translate(model, glm::vec3(5.0f, -0.0001f, 0.0f));
		model = glm::translate(model, glm::vec3(-transDist, transDist, transDist));
		model = glm::rotate(model, (-explosionAngle) * toRadians, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		atomTexture.UseTexture();
		meshList[12]->RenderModelMesh();

		model = glm::mat4();
		model = glm::translate(model, glm::vec3(5.0f, -0.0001f, 0.0f));
		model = glm::translate(model, glm::vec3(transDist, -transDist, transDist));
		model = glm::rotate(model, (explosionAngle)* toRadians, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		atomTexture.UseTexture();
		meshList[12]->RenderModelMesh();

		model = glm::mat4();
		model = glm::translate(model, glm::vec3(5.0f, -0.0001f, 0.0f));
		model = glm::translate(model, glm::vec3(transDist, -transDist, -transDist));
		model = glm::rotate(model, (-explosionAngle) * toRadians, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		atomTexture.UseTexture();
		meshList[12]->RenderModelMesh();

		model = glm::mat4();
		model = glm::translate(model, glm::vec3(5.0f, -0.0001f, 0.0f));
		model = glm::translate(model, glm::vec3(-transDist, -transDist, -transDist));
		model = glm::rotate(model, (explosionAngle)* toRadians, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		atomTexture.UseTexture();
		meshList[12]->RenderModelMesh();

		model = glm::mat4();
		model = glm::translate(model, glm::vec3(5.0f, -0.0001f, 0.0f));
		model = glm::translate(model, glm::vec3(-transDist, -transDist, transDist));
		model = glm::rotate(model, (-explosionAngle) * toRadians, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		atomTexture.UseTexture();
		meshList[12]->RenderModelMesh();

		explosionAngle += 0.8f;

		transDist += 0.001;
		if (transDist > 1.5f) {
			transDist = 100.0f;
		}

		/*if (explosionAngle >= 360) {
			explosionAngle -= 360;
		}*/

		//----------------------------------------------------------------
		//-----------------------------------------------------------------
		//-----------------------------------------------------------------
		//-----------------------------------------------------------------
		//collision end

		//atom-in pipe
		//-------------------------------------------------------------------------
		
		model = glm::mat4();
		at01 = -15.20f + x01;
		model = glm::translate(model, glm::vec3(at01, y01, 0.0f));
		model = glm::scale(model, glm::vec3(0.35f, 0.35f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		atomTexture.UseTexture();
		meshList[1]->RenderMesh();
		if (turnThreshY > y01) { y01 = y01 + 0.001; }
		if (y01 >= -0.8) { x01 = x01 + 0.001; }
		if (at01>turnThreshX) { y01 = -10.0f; x01 = 0.0f; turnThreshY = 0.0f; at01 = 0.0f; turnThreshX = -12.0f; }

		model = glm::mat4();
		at02 = -15.20f + x02;
		model = glm::translate(model, glm::vec3(at02, y02, 0.0f));
		model = glm::scale(model, glm::vec3(0.35f, 0.35f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		atomTexture.UseTexture();
		meshList[1]->RenderMesh();
		if (turnThreshY02 > y02) { y02 = y02 + 0.001; }
		if (y02 >= -0.8) { x02 = x02 + 0.001; }
		if (at02 > turnThreshX02) { y02 = -10.0f; x02 = 0.0f; turnThreshY02 = 0.0f; at02 = 0.0f; turnThreshX02 = -12.0f; }

		model = glm::mat4();
		at03 = -15.20f + x03;
		model = glm::translate(model, glm::vec3(at03, y03, 0.0f));
		model = glm::scale(model, glm::vec3(0.35f, 0.35f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		atomTexture.UseTexture();
		meshList[1]->RenderMesh();
		if (turnThreshY03 > y03) { y03 = y03 + 0.001; }
		if (y03 >= -0.8) { x03 = x03 + 0.001; }
		if (at03 > turnThreshX03) { y03 = -10.0f; x03 = 0.0f; turnThreshY03 = 0.0f; at03 = 0.0f; turnThreshX03 = -12.0f; }

		model = glm::mat4();
		at04 = -15.20f + x04;
		model = glm::translate(model, glm::vec3(at04, y04, 0.0f));
		model = glm::scale(model, glm::vec3(0.35f, 0.35f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		atomTexture.UseTexture();
		meshList[1]->RenderMesh();
		if (turnThreshY04 > y04) { y04 = y04 + 0.001; }
		if (y04 >= -0.8) { x04 = x04 + 0.001; }
		if (at04 > turnThreshX04) { y04 = -10.0f; x04 = 0.0f; turnThreshY04 = 0.0f; at04 = 0.0f; turnThreshX04 = -12.0f; }
		
		//-----------------------------------------------------------------
		//atom run end




		//atom-trans from min to max
		//-----------------------------------------------------------------

		//model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, .0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		atomTexture.UseTexture();
		meshList[0]->RenderMesh();

		//--------------------------------------------------------------------------

		model = glm::mat4();
		//model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(5.0f, 0.2f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		atomTexture.UseTexture();
		//meshList[1]->RenderMesh();
		//-----------------------------------------------------------------

		model = glm::mat4();
		//model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(5.0f, -0.2f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		atomTexture.UseTexture();
		//meshList[2]->RenderMesh();

		//-----------------------------------------------------------------

		model = glm::mat4();
		//model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(5.2f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		atomTexture.UseTexture();
		//meshList[3]->RenderMesh();

		//-----------------------------------------------------------------

		model = glm::mat4();
		//model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(4.8f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		atomTexture.UseTexture();
		//meshList[4]->RenderMesh();

		glUseProgram(0);

		mainWindow.swapBuffers();
	}
	return 0;
}