#include <iostream>
#include <stdio.h>
#include <GL/glew.h>
#include <SFML/Window.hpp>
#include <SFML/System/Time.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "lib\stb_image.h"
#include "shaderClass.h"
#include "VAOClass.h"
#include "externalFunctions.h"

// exf - external functions
namespace exf = functions;

typedef unsigned int uint;
typedef VertexArrayObject VAO;
typedef VertexBufferObject VBO;

int main() {

	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	// Okno renderingu

	sf::Window window(sf::VideoMode(800, 800, 32), "OpenGL StanMarek", sf::Style::Titlebar | sf::Style::Close, settings);
	//sf::Window window(sf::VideoMode(1920, 1080, 32), "OpenGL StanMarek", sf::Style::Fullscreen | sf::Style::Close, settings);

	window.setMouseCursorGrabbed(true);
	window.setMouseCursorVisible(false);

	// Inicjalizacja GLEW
	glewExperimental = GL_TRUE;
	glewInit();

	// Utworzenie VAO (Vertex Array Object)
	VAO vao;
	GLuint vaoID = vao.ID;
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);

	// Utworzenie VBO (Vertex Buffer Object)

	// i skopiowanie do niego danych wierzchołkowych

	VBO vbo;
	GLuint vboID = vbo.ID;
	
	exf::cube(vbo);

	// Utworzenie i skompilowanie shadera
	Shader shader("shader.vert", "shader.frag");
	shader.Activate();
	GLuint shaderProgram = shader.ID;

	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);

	GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

	GLint TexCoord = glGetAttribLocation(shaderProgram, "aTexCoord");
	glEnableVertexAttribArray(TexCoord);
	glVertexAttribPointer(TexCoord, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));

	GLint uniTrans = glGetUniformLocation(shaderProgram, "model");
	glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(model));

	GLint uniView = glGetUniformLocation(shaderProgram, "view");

	glm::mat4 proj = glm::perspective(glm::radians(45.0f), 800.0f / 800.0f, 0.06f, 100.0f);
	GLint uniProj = glGetUniformLocation(shaderProgram, "proj");
	glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));

	glEnable(GL_DEPTH_TEST);

	uint texture1;

	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width;
	int height;
	int nrChannel;

	stbi_set_flip_vertically_on_load(true);

	unsigned char* data = stbi_load("textures/jp2.bmp", &width, &height, &nrChannel, 0);

	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "ZBYCHOLUDZIE COS SIE POPSULO1\n";
	}
	stbi_image_free(data);

	uint texture2;

	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_set_flip_vertically_on_load(true);

	data = stbi_load("textures/upload.bmp", &width, &height, &nrChannel, 0);

	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "ZBYCHOLUDZIE COS SIE POPSULO2\n";
	}
	stbi_image_free(data);

	uint texture3;

	glGenTextures(1, &texture3);
	glBindTexture(GL_TEXTURE_2D, texture3);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_set_flip_vertically_on_load(true);

	data = stbi_load("textures/swag.bmp", &width, &height, &nrChannel, 0);

	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "ZBYCHOLUDZIE COS SIE POPSULO3\n";
	}
	stbi_image_free(data);

	glUniform1f(glGetUniformLocation(shaderProgram, "texture1"), 0);
	glUniform1f(glGetUniformLocation(shaderProgram, "texture2"), 1);
	glUniform1f(glGetUniformLocation(shaderProgram, "texture3"), 2);

	// Rozpoczęcie pętli zdarzeń

	bool running = true;

	int mouseValueY = 0;//verticesSize;
	int primitive = GL_TRIANGLES;
	int tryb = 3;
	int counter = 0;

	float dist = 13;
	float zeroPlane = 0;
	float eye = 0.05;

	window.setFramerateLimit(60);

	sf::Clock clock;
	sf::Time time;

	while (running) {
		time = clock.restart();
		counter++;
		float FPS = 1000000 / time.asMicroseconds();
		if (counter > FPS) {
			window.setTitle("FPS: " + std::to_string(FPS) + "author: StanMarek");
			//window.setTitle(std::to_string(FPS));
			counter = 0;
		}
		sf::Event windowEvent;
		while (window.pollEvent(windowEvent)) {
			switch (windowEvent.type) {

			case sf::Event::Closed:
				running = false;
				break;

			case sf::Event::KeyPressed: {
				switch (windowEvent.key.code)
				{
				case sf::Keyboard::Escape:
					running = false;
					break;
				case sf::Keyboard::Numpad1:
					primitive = GL_POINTS;
					break;
				case sf::Keyboard::Numpad2:
					primitive = GL_LINES;
					break;
				case sf::Keyboard::Numpad3:
					primitive = GL_LINE_STRIP;
					break;
				case sf::Keyboard::Numpad4:
					primitive = GL_LINE_LOOP;
					break;
				case sf::Keyboard::Numpad5:
					primitive = GL_TRIANGLES;
					break;
				case sf::Keyboard::Numpad6:
					primitive = GL_TRIANGLE_STRIP;
					break;
				case sf::Keyboard::Numpad7:
					primitive = GL_TRIANGLE_FAN;
					break;
				case sf::Keyboard::Numpad8:
					primitive = GL_QUADS;
					break;
				case sf::Keyboard::Numpad9:
					primitive = GL_QUAD_STRIP;
					break;
				case sf::Keyboard::Numpad0:
					primitive = GL_POLYGON;
					break;
				case sf::Keyboard::Q:
					dist += 0.1;
					break;
				case sf::Keyboard::W:
					dist -= 0.1;
					break;
				case sf::Keyboard::A:
					zeroPlane += 0.1;
					break;
				case sf::Keyboard::S:
					zeroPlane -= 0.1;
					break;
				case sf::Keyboard::Z:
					eye += 0.005;
					break;
				case sf::Keyboard::X:
					eye -= 0.005;
					break;
				case sf::Keyboard::Num1:
					tryb = 1;
					break;
				case sf::Keyboard::Num2:
					tryb = 2;
					break;
				case sf::Keyboard::Num3:
					tryb = 3;
					break;
				}
			}break;

			case sf::Event::MouseMoved:
				exf::setCameraMouse(uniView, time.asMicroseconds(), window);
				break;
			}
		}

		exf::setCameraKeyboard(uniView, time.asMicroseconds());
		
		// Nadanie scenie koloru czarnego
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		switch (tryb) {
		case 1:
			glViewport(0, 0, window.getSize().x, window.getSize().y);
			glDrawBuffer(GL_BACK_LEFT);
			exf::stereoProjection(shaderProgram, -6, 6, -4.8, 4.8, 12.99, -100, zeroPlane, dist, eye);
			glColorMask(true, false, false, false);
			exf::generateCubeTextures(primitive, texture1, texture2, texture3);
			glClear(GL_DEPTH_BUFFER_BIT);

			glDrawBuffer(GL_BACK_RIGHT);
			exf::stereoProjection(shaderProgram, -6, 6, -4.8, 4.8, 12.99, -100, zeroPlane, dist, -eye);
			glColorMask(false, false, true, false);
			exf::generateCubeTextures(primitive, texture1, texture2, texture3);
			glColorMask(true, true, true, true);
			break;
		case 2:
			glViewport(0, 0, window.getSize().x / 2, window.getSize().y);
			exf::stereoProjection(shaderProgram, -6, 6, -4.8, 4.8, 12.99, -100, zeroPlane, dist, eye);
			exf::generateCubeTextures(primitive, texture1, texture2, texture3);

			glViewport(window.getSize().x / 2, 0, window.getSize().x / 2, window.getSize().y);
			exf::stereoProjection(shaderProgram, -6, 6, -4.8, 4.8, 12.99, -100, zeroPlane, dist, -eye);
			exf::generateCubeTextures(primitive, texture1, texture2, texture3);
			break;
		case 3:
			glViewport(0, 0, window.getSize().x, window.getSize().y);
			exf::generateCubeTextures(primitive, texture1, texture2, texture3);
			break;
		}
		// Wymiana buforów tylni/przedni
		window.display();
	}

	// Kasowanie programu i czyszczenie buforów

	shader.Delete();
	//glDeleteShader(fragmentShader);
	//glDeleteShader(vertexShader);
	vbo.Delete();
	vao.Delete();

	// Zamknięcie okna renderingu
	window.close();
	return 0;
}