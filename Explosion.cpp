#include "Explosion.h"


Explosion::Explosion()
{
	transDist = 0.0f;
	curAngle = 0.0f;
	toRadians = 0.0f;
}


void Explosion::RenderExlosion(glm::mat4 model, GLuint uniformModel, Texture texture, vector<Mesh*> meshList) {
	toRadians = glm::pi<float>();



	model = glm::mat4();
	model = glm::translate(model, glm::vec3(transDist, 0.0f, 0.0f));
	model = glm::rotate(model, (curAngle)* toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.1f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	texture.UseTexture();
	meshList[2]->RenderMesh();

	model = glm::mat4();
	model = glm::translate(model, glm::vec3(-transDist, 0.0f, 0.0f));
	model = glm::rotate(model, (-curAngle) * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.1f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	texture.UseTexture();
	meshList[2]->RenderMesh();

	model = glm::mat4();
	model = glm::translate(model, glm::vec3(0.0f, transDist, 0.0f));
	model = glm::rotate(model, (curAngle)* toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.1f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	texture.UseTexture();
	meshList[2]->RenderMesh();

	model = glm::mat4();
	model = glm::translate(model, glm::vec3(0.0f, -transDist, 0.0f));
	model = glm::rotate(model, (-curAngle) * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.1f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	texture.UseTexture();
	meshList[2]->RenderMesh();

	model = glm::mat4();
	model = glm::translate(model, glm::vec3(transDist, transDist, transDist));
	model = glm::rotate(model, (curAngle)* toRadians, glm::vec3(1.0f, 1.0f, 1.0f));
	model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.1f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	texture.UseTexture();
	meshList[2]->RenderMesh();

	model = glm::mat4();
	model = glm::translate(model, glm::vec3(transDist, transDist, -transDist));
	model = glm::rotate(model, (-curAngle) * toRadians, glm::vec3(1.0f, 1.0f, 1.0f));
	model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.1f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	texture.UseTexture();
	meshList[2]->RenderMesh();

	model = glm::mat4();
	model = glm::translate(model, glm::vec3(-transDist, transDist, -transDist));
	model = glm::rotate(model, (curAngle)* toRadians, glm::vec3(1.0f, 1.0f, 1.0f));
	model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.1f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	texture.UseTexture();
	meshList[2]->RenderMesh();

	model = glm::mat4();
	model = glm::translate(model, glm::vec3(-transDist, transDist, transDist));
	model = glm::rotate(model, (-curAngle) * toRadians, glm::vec3(1.0f, 1.0f, 1.0f));
	model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.1f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	texture.UseTexture();
	meshList[2]->RenderMesh();

	model = glm::mat4();
	model = glm::translate(model, glm::vec3(transDist, -transDist, transDist));
	model = glm::rotate(model, (curAngle)* toRadians, glm::vec3(1.0f, 1.0f, 1.0f));
	model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.1f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	texture.UseTexture();
	meshList[2]->RenderMesh();


	model = glm::mat4();
	model = glm::translate(model, glm::vec3(transDist, -transDist, -transDist));
	model = glm::rotate(model, (-curAngle) * toRadians, glm::vec3(1.0f, 1.0f, 1.0f));
	model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.1f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	texture.UseTexture();
	meshList[2]->RenderMesh();

	model = glm::mat4();
	model = glm::translate(model, glm::vec3(-transDist, -transDist, -transDist));
	model = glm::rotate(model, (curAngle)* toRadians, glm::vec3(1.0f, 1.0f, 1.0f));
	model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.1f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	texture.UseTexture();
	meshList[2]->RenderMesh();

	model = glm::mat4();
	model = glm::translate(model, glm::vec3(-transDist, -transDist, transDist));
	model = glm::rotate(model, (-curAngle) * toRadians, glm::vec3(1.0f, 1.0f, 1.0f));
	model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.1f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	texture.UseTexture();
	meshList[2]->RenderMesh();


	transDist += 0.0001;

	if (transDist > 5.0f) {
		transDist = 0.0f;
	}

	curAngle += 0.1f;

	if (curAngle >= 360) {
		curAngle -= 360;
	}
}

Explosion::~Explosion()
{
	transDist = 0.0f;
	curAngle = 0.0f;
	toRadians = 0.0f;
}
