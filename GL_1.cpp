#include <iostream>
#include <stdio.h>

#include <GL/glew.h>

#include <SFML/Window.hpp>
#include <SFML/System/Time.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define M_PI 3.14159265358979323846

typedef unsigned int uint;

// Kody shaderów
const GLchar* vertexSource = R"glsl(
	#version 150 core
	in vec3 position;
	in vec3 color;
	out vec3 Color;
	in vec2 aTexCoord;
	out vec2 TexCoord;
		uniform mat4 model;
		uniform mat4 view;
		uniform mat4 proj;
	void main(){
	TexCoord = aTexCoord;
	Color = color;
	gl_Position = proj * view * model * vec4(position, 1.0);
	}
	)glsl";

const GLchar* fragmentSource = R"glsl(
	#version 150 core
	in vec3 Color;
	out vec4 outColor;
	in vec2 TexCoord;
	uniform sampler2D texture1;
	uniform sampler2D texture2;	
	uniform sampler2D texture3;

	void main()
	{
	//outColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), texture(texture3, TexCoord), 0.5);
	outColor = texture(texture1, TexCoord)*texture(texture2, TexCoord)*texture(texture3, TexCoord);
	//outColor = vec4(Color, 1.0);
	}
	)glsl";

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

bool firstMouse = true;

float obrot = 0;

double yaw = -90;
double pitch = 0;

int lastX;
int lastY;

void cube(int buffer) {
	int punkty = 36;
	//int punkty = 24;

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

void ustawKamere(GLint _uView) {

	float cameraSpeed = 0.0009f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		cameraPos += cameraSpeed * cameraFront;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		cameraPos -= cameraSpeed * cameraFront;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		obrot -= cameraSpeed;
		cameraFront.x = sin(obrot);
		cameraFront.z = -cos(obrot);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		obrot += cameraSpeed;
		cameraFront.x = sin(obrot);
		cameraFront.z = -cos(obrot);
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


	/*GLfloat vertices[] = {
		0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
	};*/

	//int verticesSize = 15;

	//glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// Utworzenie i skompilowanie shadera wierzchołków
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	char bufferVertex[512];

	GLint statusVertex;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &statusVertex);

	if (statusVertex != GL_TRUE) {
		glGetShaderInfoLog(vertexShader, 512, NULL, bufferVertex);
		std::cout << "ERROR " << statusVertex << std::endl;
		std::cout << "Failed vertex shader" << bufferVertex << std::endl;
	}
	else {
		std::cout << "Vertex Shader compilation: OK\n";
	}

	// Utworzenie i skompilowanie shadera fragmentów

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	char bufferFragment[512];

	GLint statusFragment;
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &statusFragment);

	if (statusFragment != GL_TRUE) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, bufferFragment);
		std::cout << "ERROR " << statusFragment << std::endl;
		std::cout << "Failed fragement shader" << bufferFragment << std::endl;
	}
	else {
		std::cout << "Fragment Shader compilation: OK\n";
	}

	// Zlinkowanie obu shaderów w jeden wspólny program

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	//glBindFragDataLocation(shaderProgram, 0, "outColor");

	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	// Specifikacja formatu danych wierzchołkowych

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

	window.setFramerateLimit(60);
	int counter = 0;

	sf::Clock clock;
	sf::Time time;

	while (running) {
		time = clock.restart();
		counter++;
		float FPS = 1000000 / time.asMicroseconds();
		//std::cout << "ZBYCHOLUDY " << counter << "\n";
		if (counter > FPS) {
			//window.setTitle("FPS: " + std::to_string(FPS) + "author: StanMarek");
			window.setTitle(std::to_string(FPS));
			counter = 0;
		}
		sf::Event windowEvent;
		while (window.pollEvent(windowEvent)) {
			switch (windowEvent.type) {

			case sf::Event::Closed:
				running = false;
				break;

			case sf::Event::KeyPressed:
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
				}

				/*case sf::Event::MouseMoved:
					if (windowEvent.mouseMove.y > mouseValueY) {
						verticesSize++;
					}
					else {
						verticesSize--;
						if (verticesSize < 3)
							verticesSize = 3;
					}
					mouseValueY = windowEvent.mouseMove.y;*/

			case sf::Event::MouseMoved:
				setCameraMouse(uniView, time.asMicroseconds(), window);
				break;
			}
		}

		setCameraKeyboard(uniView, time.asMicroseconds());
		//ustawKamere(uniView);
		// Nadanie scenie koloru czarnego

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//circle(verticesSize);
		//glDrawArrays(primitive, 0, verticesSize);
		//glDrawArrays(primitive, 0, 36);

	/*	glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		glDrawArrays(GL_TRIANGLES, 0, 24);*/

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glDrawArrays(GL_TRIANGLES, 0, 12);
		//glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture2);
		glDrawArrays(GL_TRIANGLES, 12, 12);

		glBindTexture(GL_TEXTURE_2D, texture3);
		glDrawArrays(GL_TRIANGLES, 24, 12);

		// Wymiana buforów tylni/przedni
		window.display();
	}

	// Kasowanie programu i czyszczenie buforów

	glDeleteProgram(shaderProgram);
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);

	// Zamknięcie okna renderingu
	window.close();
	return 0;

}