#include "externalFunctions.h"

void functions::cube(int buffer) {
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

void functions::setCamera(GLint _uView) {

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

void functions::circle(int verticesSize) {

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

void functions::setCameraMouse(GLint uniView, float elapsedTime, const sf::Window& window) {

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

void functions::setCameraKeyboard(GLint uniView, float elapsedTime) {

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

void functions::stereoProjection(GLuint shaderProgram_, float _left, float _right, float _bottom, float _top, float _near, float _far, float _zero_plane, float _dist, float _eye)
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

void functions::generateCubeTextures(int primitive, uint texture1, uint texture2, uint texture3) {
	glBindTexture(GL_TEXTURE_2D, texture1);
	glDrawArrays(primitive, 0, 12);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glDrawArrays(primitive, 12, 12);
	glBindTexture(GL_TEXTURE_2D, texture3);
	glDrawArrays(primitive, 24, 12);
}