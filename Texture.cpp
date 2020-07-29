#include "Texture.h"

Texture::Texture()
{
	textureID = 0;
	width = 0;
	height = 0;
	bitDepth = 0;
	fileLocation = "";
}

Texture::Texture(const char* fileLoc)
{
	textureID = 0;
	width = 0;
	height = 0;
	bitDepth = 0;
	fileLocation = fileLoc;
}


bool Texture::LoadTexture() {

	unsigned char* texData = stbi_load(fileLocation, &width, &height, &bitDepth, 0);

	if (!texData) {
		printf("Failed to find: %s\n", fileLocation);
		return false;
	}


	//(one texture, ref to our texture)
	glGenTextures(1, &textureID);
	//(TYPE OF TEXTURE TO BIND)
	glBindTexture(GL_TEXTURE_2D, textureID);

	//(apply to GL_TEXTURE_2D, how to handel wraping on x-axis, method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//same thing for y axis
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//handel zooming
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//load data for our image
	//(saying we want to set the img for whatever is bound to texture2d,
	//mitmap levels, format of our img, width, height, legacy value!
	//format of img loading, type of data we are sending in, data itself)
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
	glGenerateMipmap(GL_TEXTURE_2D);

	//UNBIND Texture
	glBindTexture(GL_TEXTURE_2D, 0); 
	stbi_image_free(texData);

	return true;
}


bool Texture::LoadTextureA() {

	unsigned char* texData = stbi_load(fileLocation, &width, &height, &bitDepth, 0);

	if (!texData) {
		printf("Failed to find: %s\n", fileLocation);
		return false;
	}


	//(one texture, ref to our texture)
	glGenTextures(1, &textureID);
	//(TYPE OF TEXTURE TO BIND)
	glBindTexture(GL_TEXTURE_2D, textureID);

	//(apply to GL_TEXTURE_2D, how to handel wraping on x-axis, method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//same thing for y axis
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//handel zooming
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//load data for our image
	//(saying we want to set the img for whatever is bound to texture2d,
	//mitmap levels, format of our img, width, height, legacy value!
	//format of img loading, type of data we are sending in, data itself)
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
	glGenerateMipmap(GL_TEXTURE_2D);

	//UNBIND Texture
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(texData);

	return true;
}

void Texture::UseTexture() {
	//texture unit 0
	glActiveTexture(GL_TEXTURE0);
	//binding the above tex unit to this texture
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::ClearTexture() {
	glDeleteTextures(1, &textureID);
	textureID = 0;
	width = 0;
	height = 0;
	bitDepth = 0;
	fileLocation = "";
}

Texture::~Texture() {
	ClearTexture();
}
