#pragma once
#include<iostream>
#include<string>
#include<glew/glew.h>
#include<GLFW/glfw3.h>
#include<soil2/SOIL2.h>

class Texture {
private:
	GLuint id;
	int height;
	int width;
	unsigned int type;
	GLint textureUnit;

public:
	Texture(const char* fileName, GLenum type, GLint texture_unit) {
		this->type = type;
		this->textureUnit = texture_unit;
		unsigned char* image = SOIL_load_image(fileName, &this->width, &this->height, NULL, SOIL_LOAD_RGBA);

		glGenTextures(1, &this->id);
		glBindTexture(type, this->id);

		glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		if (image) {
			glTexImage2D(type, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
			glGenerateMipmap(type);
		}
		else {
			std::cout << "ERROR::TEXTURE_LOADING_FAILED" << "\n";
		}

		glActiveTexture(0);
		glBindTexture(GL_TEXTURE_2D, 0);
		SOIL_free_image_data(image);
	}

	~Texture() {
		glDeleteTextures(1, &this->id);
	}

	inline GLuint getID() const {
		return this->id;
	}

	void bind() {
		glActiveTexture(GL_TEXTURE0 + this->textureUnit);
		glBindTexture(this->type, this->id);
	}

	void unbind() {
		glActiveTexture(0);
		glBindTexture(this->type, 0);
	}

	inline GLint getTextureUnit() const { return this->textureUnit; }

	void loadFromFile(const char* fileName) {
		if (this->id) {
			glDeleteTextures(1, &this->id);
		}
		unsigned char* image = SOIL_load_image(fileName, &this->width, &this->height, NULL, SOIL_LOAD_RGBA);

		glGenTextures(1, &this->id);
		glBindTexture(this->type, this->id);

		glTexParameteri(this->type, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(this->type, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(this->type, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(this->type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		if (image) {
			glTexImage2D(this->type, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
			glGenerateMipmap(this->type);
		}
		else {
			std::cout << "ERROR::TEXTURE::LOADFROMFILED::TEXTURE_LOADING_FAILED" << fileName << "\n";
		}

		glActiveTexture(0);
		glBindTexture(this->type, 0);
		SOIL_free_image_data(image);
	}
};