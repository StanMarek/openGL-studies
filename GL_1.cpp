#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <GL/glew.h>
#include <SFML/Window.hpp>
#include <SFML/System/Time.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define M_PI 3.14159
#define STB_IMAGE_IMPLEMENTATION
#include "lib/stb_image.h"
#include "shaderClass.h"
#include "externalFunctions.h"
#include "globalVariables.h"
#include "VAOClass.h"
#include "VBOClass.h"
#include "EBOClass.h"
#include "textureClass.h"

typedef unsigned int uint;
namespace exf = functions;

GLuint loadTexture(const char* texturePath);

int main() {

	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 4;

	// Creating rendering window
	// Small window
	sf::Window window(sf::VideoMode(800, 800, 32), "OpenGL StanMarek", sf::Style::Titlebar | sf::Style::Close, settings);
	// Full screen
	//sf::Window window(sf::VideoMode(1920, 1080, 32), "OpenGL StanMarek", sf::Style::Fullscreen | sf::Style::Close, settings);

	window.setMouseCursorGrabbed(true);
	window.setMouseCursorVisible(false);

	// GLEW initialization
	glewExperimental = GL_TRUE;
	glewInit();

	// Creating VAO (Vertex Array Object)
	VertexArrayObject VAO;
	VAO.Bind();

	// Creating EBO (Element Buffer Object)
	ElementBufferObject EBO;

	// Creating VBO (Vertex Buffer Object
	VertexBufferObject VBO;

	glEnable(GL_MULTISAMPLE);
	glEnable(GL_CULL_FACE);

	// Loading model from .obj file
	int points = 0;
	std::vector<std::vector<int>> objects;
	//exf::loadModelObj(points, "models/projekt.obj", VBO.ID);
	exf::loadModelOBJNormalsCoord(points, "models/proj1smooth.obj", VBO.ID, objects);

	// Creating vertex and fragment shader
	Shader shader("shader.vert", "shader.frag");
	shader.Activate();

	GLint posAttrib = glGetAttribLocation(shader.ID, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);

	/*
	Uncomment this (colAttrib) to have colors,
	also need to change shaders code to have colors as input and output
	*/
	/*GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));*/

	GLint NorAttrib = glGetAttribLocation(shader.ID, "aNormal");
	glEnableVertexAttribArray(NorAttrib);
	glVertexAttribPointer(NorAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));

	GLint TexCoord = glGetAttribLocation(shader.ID, "aTexCoord");
	glEnableVertexAttribArray(TexCoord);
	glVertexAttribPointer(TexCoord, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));

	glm::mat4 model = glm::mat4(1.0f);
	//model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));

	GLint uniTrans = glGetUniformLocation(shader.ID, "model");
	glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(model));

	GLint uniView = glGetUniformLocation(shader.ID, "view");

	glm::mat4 proj = glm::perspective(glm::radians(45.0f), 800.0f / 800.0f, 0.06f, 100.0f);
	GLint uniProj = glGetUniformLocation(shader.ID, "proj");
	glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));

	//glm::vec3 lightPos(-2.2f, 2.0f, 10.0f);
	glm::vec3 lightPos(-3.3f, 3.0f, 15.0f);
	//glm::vec3 lightPos(-1000.0f, 1000.0f, 10000.0f);
	GLint uniLightPos = glGetUniformLocation(shader.ID, "lightsPos");
	glUniform3fv(uniLightPos, 1, glm::value_ptr(lightPos));

	uniCamPos = glGetUniformLocation(shader.ID, "camPos");

	glEnable(GL_DEPTH_TEST);

	std::vector<GLuint> textures;
	GLuint texture1 = loadTexture("textures/crate.bmp");
	GLuint texture2 = loadTexture("textures/metal.bmp");
	GLuint texture3 = loadTexture("textures/basketball.jpg");
	GLuint texture4 = loadTexture("textures/pink.jpg");
	textures.push_back(texture1);
	textures.push_back(texture2);
	textures.push_back(texture3);
	textures.push_back(texture4);

	bool running = true;

	int mouseValueY = 0;
	int primitive = GL_TRIANGLES;
	int tryb = 3;
	int counter = 0;

	float dist = 13;
	float zeroPlane = 0;
	float eye = 0.05;

	window.setFramerateLimit(150);

	sf::Clock clock;
	sf::Time time;

	// Main loop 
	while (running) {
		time = clock.restart();
		
		sf::Event windowEvent;
		while (window.pollEvent(windowEvent)) {
			switch (windowEvent.type) {
			case sf::Event::Closed: running = false; break;
			case sf::Event::KeyPressed: {
				switch (windowEvent.key.code)
				{
					case sf::Keyboard::Escape: running = false; break;
					case sf::Keyboard::Numpad1:	primitive = GL_POINTS; break;	
					case sf::Keyboard::Numpad2: primitive = GL_LINES; break;
					case sf::Keyboard::Numpad3: primitive = GL_LINE_STRIP; break;
					case sf::Keyboard::Numpad4: primitive = GL_LINE_LOOP; break;
					case sf::Keyboard::Numpad5: primitive = GL_TRIANGLES; break;
					case sf::Keyboard::Numpad6: primitive = GL_TRIANGLE_STRIP; break;
					case sf::Keyboard::Numpad7: primitive = GL_TRIANGLE_FAN; break;
					case sf::Keyboard::Numpad8: primitive = GL_QUADS; break;
					case sf::Keyboard::Numpad9: primitive = GL_QUAD_STRIP; break;
					case sf::Keyboard::Numpad0: primitive = GL_POLYGON; break;
					case sf::Keyboard::Q: dist += 0.1; break;
					case sf::Keyboard::W: dist -= 0.1; break;
					case sf::Keyboard::A: zeroPlane += 0.1; break;
					case sf::Keyboard::S: zeroPlane -= 0.1; break;
					case sf::Keyboard::Z: eye += 0.005; break;
					case sf::Keyboard::X: eye -= 0.005; break;
					case sf::Keyboard::Num1: tryb = 1; break;
					case sf::Keyboard::Num2: tryb = 2; break;
					case sf::Keyboard::Num3: tryb = 3; break;
				}
			}break;
			case sf::Event::MouseMoved:
				exf::setCameraMouse(uniView, time.asMicroseconds(), window);
				break;
			}
		}

		exf::setCameraKeyboard(uniView, time.asMicroseconds());
		
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		switch (tryb) {
		case 1:
			glViewport(0, 0, window.getSize().x, window.getSize().y);
			glDrawBuffer(GL_BACK_LEFT);
			exf::stereoProjection(shader.ID, -6, 6, -4.8, 4.8, 12.99, -100, zeroPlane, dist, eye);
			glColorMask(true, false, false, false);
			exf::bindTextureModel(primitive, textures, objects);
			glClear(GL_DEPTH_BUFFER_BIT);

			glDrawBuffer(GL_BACK_RIGHT);
			exf::stereoProjection(shader.ID, -6, 6, -4.8, 4.8, 12.99, -100, zeroPlane, dist, -eye);
			glColorMask(false, false, true, false);
			exf::bindTextureModel(primitive, textures, objects);

			glColorMask(true, true, true, true);
			break;
		case 2:
			glViewport(0, 0, window.getSize().x / 2, window.getSize().y);
			exf::stereoProjection(shader.ID, -6, 6, -4.8, 4.8, 12.99, -100, zeroPlane, dist, eye);
			exf::bindTextureModel(primitive, textures, objects);

			glViewport(window.getSize().x / 2, 0, window.getSize().x / 2, window.getSize().y);
			exf::stereoProjection(shader.ID, -6, 6, -4.8, 4.8, 12.99, -100, zeroPlane, dist, -eye);
			glBindTexture(GL_TEXTURE_2D, texture1);
			exf::bindTextureModel(primitive, textures, objects);
			break;
		case 3:
			glViewport(0, 0, window.getSize().x, window.getSize().y);
			exf::bindTextureModel(primitive, textures, objects);
			break;
		}
		window.display();
	}

	// Deleting program and clearing buffers
	shader.Delete();
	VAO.Delete();
	VBO.Delete();
	EBO.Delete();
	
	window.close();
	return 0;
}

GLuint loadTexture(const char* texturePath)
{
	GLuint texture;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 8.0f);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(texturePath, &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "ZBYCHOLUDZIE TESKTURA " << texturePath << " NIE DZIALA" << std::endl;
	}
	stbi_image_free(data);

	return texture;
}

