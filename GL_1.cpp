#include <iostream>
#include <stdio.h>
#include <GL/glew.h>
#include <SFML/Window.hpp>
#include <SFML/System/Time.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define M_PI 3.14159
#define STB_IMAGE_IMPLEMENTATION
#include "lib\stb_image.h"
#include "shaderClass.h"
#include "VAOClass.h"

typedef unsigned int uint;
typedef VertexArrayObject VAO;
typedef VertexBufferObject VBO;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

bool firstMouse = true;

float rotation = 0;

double yaw = -90;
double pitch = 0;

int lastX;
int lastY;

void cube(int buffer);
void setCamera(GLint _uView);
void circle(int verticesSize);
void setCameraMouse(GLint uniView, float elapsedTime, const sf::Window& window);
void setCameraKeyboard(GLint uniView, float elapsedTime);
void stereoProjection(GLuint shaderProgram_, float _left, float _right, float _bottom, float _top, float _near, float _far, float _zero_plane, float _dist, float _eye);
void generateCubeTextures(int primitive, uint texture1, uint texture2, uint texture3);

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

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Utworzenie VBO (Vertex Buffer Object)

	// i skopiowanie do niego danych wierzchołkowych

	GLuint vbo;
	glGenBuffers(1, &vbo);

	cube(vbo);

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
				setCameraMouse(uniView, time.asMicroseconds(), window);
				break;
			}
		}

		setCameraKeyboard(uniView, time.asMicroseconds());

		// Nadanie scenie koloru czarnego
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		switch (tryb) {
		case 1:
			glViewport(0, 0, window.getSize().x, window.getSize().y);
			glDrawBuffer(GL_BACK_LEFT);
			stereoProjection(shaderProgram, -6, 6, -4.8, 4.8, 12.99, -100, zeroPlane, dist, eye);
			glColorMask(true, false, false, false);
			generateCubeTextures(primitive, texture1, texture2, texture3);
			glClear(GL_DEPTH_BUFFER_BIT);

			glDrawBuffer(GL_BACK_RIGHT);
			stereoProjection(shaderProgram, -6, 6, -4.8, 4.8, 12.99, -100, zeroPlane, dist, -eye);
			glColorMask(false, false, true, false);
			generateCubeTextures(primitive, texture1, texture2, texture3);
			glColorMask(true, true, true, true);
			break;
		case 2:
			glViewport(0, 0, window.getSize().x / 2, window.getSize().y);
			stereoProjection(shaderProgram, -6, 6, -4.8, 4.8, 12.99, -100, zeroPlane, dist, eye);
			generateCubeTextures(primitive, texture1, texture2, texture3);

			glViewport(window.getSize().x / 2, 0, window.getSize().x / 2, window.getSize().y);
			stereoProjection(shaderProgram, -6, 6, -4.8, 4.8, 12.99, -100, zeroPlane, dist, -eye);
			generateCubeTextures(primitive, texture1, texture2, texture3);
			break;
		case 3:
			glViewport(0, 0, window.getSize().x, window.getSize().y);
			generateCubeTextures(primitive, texture1, texture2, texture3);
			break;
		}
		// Wymiana buforów tylni/przedni
		window.display();
	}

	// Kasowanie programu i czyszczenie buforów

	glDeleteProgram(shaderProgram);
	//glDeleteShader(fragmentShader);
	//glDeleteShader(vertexShader);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);

	// Zamknięcie okna renderingu
	window.close();
	return 0;

}

void cube(int buffer) {
	int punkty = 36;

	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f
	};

	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * punkty * 8, vertices, GL_STATIC_DRAW);
}

void setCamera(GLint _uView) {

	float cameraSpeed = 0.0009f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		cameraPos += cameraSpeed * cameraFront;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		cameraPos -= cameraSpeed * cameraFront;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		rotation -= cameraSpeed;
		cameraFront.x = sin(rotation);
		cameraFront.z = -cos(rotation);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		rotation += cameraSpeed;
		cameraFront.x = sin(rotation);
		cameraFront.z = -cos(rotation);
	}

	glm::mat4 view;
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	glUniformMatrix4fv(_uView, 1, GL_FALSE, glm::value_ptr(view));
}

void circle(int verticesSize) {

	GLfloat* vertices = new GLfloat[verticesSize * 6];

	float alfa = 0.0f;
	float d_alfa = 2 * M_PI / verticesSize;

	int r = 1;
	for (int i = 0; i < verticesSize * 6; i += 6) {
		vertices[i] = r * cos(alfa);
		vertices[i + 1] = r * sin(alfa);
		vertices[i + 2] = 0.0f;

		vertices[i + 3] = sin(alfa);
		vertices[i + 4] = cos(alfa);
		vertices[i + 5] = tan(alfa);

		alfa += d_alfa;
	}

	glBufferData(GL_ARRAY_BUFFER, verticesSize * 6 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

	delete[] vertices;
}

void setCameraMouse(GLint uniView, float elapsedTime, const sf::Window& window) {

	sf::Vector2i localPosition = sf::Mouse::getPosition(window);

	sf::Vector2i position;
	bool relocation = false;

	if (localPosition.x <= 0) {
		position.x = window.getSize().x;
		position.y = localPosition.y;
		relocation = true;
	}
	if (localPosition.x >= window.getSize().x - 1) {
		position.x = 0;
		position.y = localPosition.y;
		relocation = true;
	}
	if (localPosition.y <= 0) {
		position.y = window.getSize().y;
		position.x = localPosition.x;
		relocation = true;
	}
	if (localPosition.y >= window.getSize().y - 1) {
		position.y = 0;
		position.x = localPosition.x;
		relocation = true;
	}

	if (relocation) {
		sf::Mouse::setPosition(position, window);
		firstMouse = true;
	}
	localPosition = sf::Mouse::getPosition(window);

	if (firstMouse) {
		lastX = localPosition.x;
		lastY = localPosition.y;
		firstMouse = false;
	}

	double xOffset = localPosition.x - lastX;
	double yOffset = localPosition.y - lastY;
	lastX = localPosition.x;
	lastY = localPosition.y;

	double sensitivity = 0.001f;
	double cameraSpeed = 0.005f * elapsedTime;

	xOffset *= sensitivity;
	yOffset *= sensitivity;

	yaw += xOffset * cameraSpeed;
	pitch -= yOffset * cameraSpeed;

	if (pitch > 89.0f) pitch = 89.0f;
	if (pitch < -89.0f) pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);

	glm::mat4 view;
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));
}

void setCameraKeyboard(GLint uniView, float elapsedTime) {

	float cameraSpeed = 0.000002f * elapsedTime;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		cameraPos += cameraSpeed * cameraFront;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		cameraPos -= cameraSpeed * cameraFront;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}

	glm::mat4 view;
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));
}


void stereoProjection(GLuint shaderProgram_, float _left, float _right, float _bottom, float _top, float _near, float _far, float _zero_plane, float _dist, float _eye)
{
	/*
		Perform the perspective projection for one eye's subfield.
		The projection is in the direction of the negative z-axis.
				_left=-6.0;
				_right=6.0;
				_bottom=-4.8;
				 _top=4.8;
		[default: -6.0, 6.0, -4.8, 4.8]
		left, right, bottom, top = the coordinate range, in the plane of zero parallax setting,
			 which will be displayed on the screen.
			 The ratio between (right-left) and (top-bottom) should equal the aspect
		ratio of the display.
					  _near=6.0;
					  _far=-20.0;
		[default: 6.0, -6.0]
		near, far = the z-coordinate values of the clipping planes.
					  _zero_plane=0.0;
		[default: 0.0]
		zero_plane = the z-coordinate of the plane of zero parallax setting.
		[default: 14.5]
						 _dist=10.5;
	   dist = the distance from the center of projection to the plane of zero parallax.
		[default: -0.3]
					 _eye=-0.3;
		eye = half the eye separation; positive for the right eye subfield,
		negative for the left eye subfield.
	*/

	float   _dx = _right - _left;
	float   _dy = _top - _bottom;

	float   _xmid = (_right + _left) / 2.0;
	float   _ymid = (_top + _bottom) / 2.0;

	float   _clip_near = _dist + _zero_plane - _near;
	float   _clip_far = _dist + _zero_plane - _far;

	float  _n_over_d = _clip_near / _dist;

	float   _topw = _n_over_d * _dy / 2.0;
	float   _bottomw = -_topw;
	float   _rightw = _n_over_d * (_dx / 2.0 - _eye);
	float   _leftw = _n_over_d * (-_dx / 2.0 - _eye);

	// Create a frustum, and shift it off axis
	glm::mat4 proj = glm::frustum(_leftw, _rightw, _bottomw, _topw, _clip_near, _clip_far);

	proj = glm::translate(proj, glm::vec3(-_xmid - _eye, -_ymid, 0));

	GLint uniProj = glGetUniformLocation(shaderProgram_, "proj");
	glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));
}

void generateCubeTextures(int primitive, uint texture1, uint texture2, uint texture3) {
	glBindTexture(GL_TEXTURE_2D, texture1);
	glDrawArrays(primitive, 0, 12);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glDrawArrays(primitive, 12, 12);
	glBindTexture(GL_TEXTURE_2D, texture3);
	glDrawArrays(primitive, 24, 12);
}