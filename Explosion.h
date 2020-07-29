#pragma once

#include<GL/glew.h>
#include<GLFW/glfw3.h>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<vector>

#include "Mesh.h"
#include "Texture.h"

using namespace std;

class Explosion
{
public:
	Explosion();

	void RenderExlosion(glm::mat4 model, GLuint uniformModel, Texture texture, vector<Mesh*> meshList);
	
	~Explosion();

private:

	float transDist;
	float curAngle;
	float toRadians;
};

