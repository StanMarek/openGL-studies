#include "externalFunctions.h"

void functions::cube(GLuint buffer) {
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

	GLsizeiptr size = sizeof(GLfloat) * punkty * 8;
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void functions::cube(VertexBufferObject& vbo)
{
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

	GLsizeiptr size = sizeof(GLfloat) * punkty * 8;
	vbo.Bind();
	//glBindBuffer(GL_ARRAY_BUFFER, vbo.ID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
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

	glUniform3fv(uniCamPos, 1, glm::value_ptr(cameraPos));

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

void functions::loadModelObj(int& punkty_, const char* filename, int buffer)
{
	int vert_num = 0;
	int trian_num = 0;

	std::ifstream myReadFile;
	myReadFile.open(filename);

	std::string output;

	if (myReadFile.is_open()) {
		while (!myReadFile.eof()) {
			myReadFile >> output;
			if (output == "v") vert_num++;
			if (output == "f") trian_num++;
		}
	}

	myReadFile.close();
	myReadFile.open(filename);

	float** vert = new float* [vert_num];
	for (int k = 0; k < vert_num; k++)
		vert[k] = new float[3];

	int** trian = new int* [trian_num];
	for (int k = 0; k < trian_num; k++)
		trian[k] = new int[3];

	int licz_vert = 0;
	int licz_elem = 0;

	while (!myReadFile.eof()) {
		myReadFile >> output;
		if (output == "v") {
			myReadFile >> vert[licz_vert][0];
			myReadFile >> vert[licz_vert][1];
			myReadFile >> vert[licz_vert][2];
			licz_vert++;
		}
		if (output == "f") {
			myReadFile >> trian[licz_elem][0];
			myReadFile >> trian[licz_elem][1];
			myReadFile >> trian[licz_elem][2];
			licz_elem++;
		}
		output.clear();
	}

	GLfloat* vertices = new GLfloat[trian_num * 9];
	int vert_current = 0;

	for (int i = 0; i < trian_num; i++) {
		vertices[vert_current + 0] = vert[trian[i][0] - 1][0];
		vertices[vert_current + 1] = vert[trian[i][0] - 1][1];
		vertices[vert_current + 2] = vert[trian[i][0] - 1][2];

		vertices[vert_current + 3] = vert[trian[i][1] - 1][0];
		vertices[vert_current + 4] = vert[trian[i][1] - 1][1];
		vertices[vert_current + 5] = vert[trian[i][1] - 1][2];

		vertices[vert_current + 6] = vert[trian[i][2] - 1][0];
		vertices[vert_current + 7] = vert[trian[i][2] - 1][1];
		vertices[vert_current + 8] = vert[trian[i][2] - 1][2];

		vert_current += 9;
	}

	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * trian_num * 9, vertices, GL_STATIC_DRAW);

	punkty_ = trian_num * 9;

	delete[] vertices;
	for (int i = 0; i < vert_num; i++)
		delete[] vert[i];
	delete[] vert;
	for (int i = 0; i < vert_num; i++)
		delete[] trian[i];
	delete[] trian;
}

void functions::loadModelObj_EBO(int& punkty_, const char* filename, int buffer_vbo, int buffer_ebo)
{
	int vert_num = 0;
	int trian_num = 0;

	std::ifstream myReadFile;
	myReadFile.open(filename);

	std::string output;

	if (myReadFile.is_open()) {
		while (!myReadFile.eof()) {
			myReadFile >> output;
			if (output == "v") vert_num++;
			if (output == "f") trian_num++;
		}
	}

	myReadFile.close();
	myReadFile.open(filename);

	float* vert = new float[vert_num * 3];
	int* element = new int[trian_num * 3];
	int licz_vert = 0;
	int licz_elem = 0;
	int tmp = 0;

	while (!myReadFile.eof()) {
		myReadFile >> output;
		if (output == "v") {
			myReadFile >> vert[licz_vert];
			myReadFile >> vert[licz_vert + 1];
			myReadFile >> vert[licz_vert + 2];
			licz_vert += 3;
		}
		if (output == "f") {
			myReadFile >> tmp;	tmp--; element[licz_elem] = tmp;
			myReadFile >> tmp;	tmp--; element[licz_elem + 1] = tmp;
			myReadFile >> tmp;	tmp--; element[licz_elem + 2] = tmp;
			licz_elem += 3;
		}
		output.clear();
	}

	glBindBuffer(GL_ARRAY_BUFFER, buffer_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vert_num * 3, vert, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, buffer_ebo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLuint) * trian_num * 3, element, GL_STATIC_DRAW);

	punkty_ = trian_num * 3;

	delete[] vert;
	delete[] element;
}

bool functions::loadModelOBJNormalsCoord(int& punkty_, const char* filename, int buffer, std::vector<std::vector<int>>& objects)
{
	int vert_num = 0;
	int triangles = 0;
	int normals = 0;
	int coord_num = 0;
	int obj_num = 0;

	std::ifstream myReadFile;
	myReadFile.open(filename);
	std::string output;
	if (myReadFile.is_open()) {
		while (!myReadFile.eof()) {
			myReadFile >> output;
			if (output == "v") vert_num++;
			if (output == "f") triangles++;
			if (output == "vn") normals++;
			if (output == "vt") coord_num++;
			if (output == "o") {
				if (objects.size() == 0) {
					objects.push_back({ 0 });
				}
				else {
					objects.back().push_back(triangles * 3 - objects.back()[0]);
					objects.push_back({ triangles * 3 });
				}
			}
		}
		objects.back().push_back(triangles * 3 - objects.back()[0]);
	}

	myReadFile.close();
	myReadFile.open(filename);

	float** vert;
	vert = new float* [vert_num]; //przydzielenie pamiêci na w wierszy

	for (int i = 0; i < vert_num; i++)
		vert[i] = new float[3];


	int** trian;
	trian = new int* [triangles]; //przydzielenie pamiêci na w wierszy

	for (int i = 0; i < triangles; i++)
		trian[i] = new int[9];

	float** norm;
	norm = new float* [normals]; //przydzielenie pamiêci na w wierszy

	for (int i = 0; i < normals; i++)
		norm[i] = new float[3];

	float** coord;
	coord = new float* [coord_num]; //przydzielenie pamiêci na w wierszy

	for (int i = 0; i < coord_num; i++)
		coord[i] = new float[2];

	int licz_vert = 0;
	int licz_triang = 0;
	int licz_normals = 0;
	int licz_coord = 0;


	while (!myReadFile.eof()) {
		output = "";
		myReadFile >> output;
		if (output == "vn") { myReadFile >> norm[licz_normals][0]; myReadFile >> norm[licz_normals][1]; myReadFile >> norm[licz_normals][2]; licz_normals++; }
		if (output == "v") { myReadFile >> vert[licz_vert][0]; myReadFile >> vert[licz_vert][1]; myReadFile >> vert[licz_vert][2]; licz_vert++; }
		if (output == "vt") { myReadFile >> coord[licz_coord][0]; myReadFile >> coord[licz_coord][1]; licz_coord++; }

		if (output == "f") {

			for (int i = 0; i < 9; i += 3)
			{
				std::string s;
				myReadFile >> s;
				std::stringstream ss(s);

				std::vector <std::string> el;
				std::string item;


				while (getline(ss, item, '/')) {
					el.push_back(item);
				}
				trian[licz_triang][i] = std::stoi(el[0]);
				trian[licz_triang][i + 1] = std::stoi(el[1]);
				trian[licz_triang][i + 2] = std::stoi(el[2]);


			}
			licz_triang++;
		}
	}
	GLfloat* vertices = new GLfloat[triangles * 24];

	int vert_current = 0;

	for (int i = 0; i < triangles; i++)
	{
		vertices[vert_current] = vert[trian[i][0] - 1][0];
		vertices[vert_current + 1] = vert[trian[i][0] - 1][1];
		vertices[vert_current + 2] = vert[trian[i][0] - 1][2];
		vertices[vert_current + 3] = norm[trian[i][2] - 1][0];
		vertices[vert_current + 4] = norm[trian[i][2] - 1][1];
		vertices[vert_current + 5] = norm[trian[i][2] - 1][2];
		vertices[vert_current + 6] = coord[trian[i][1] - 1][0];
		vertices[vert_current + 7] = coord[trian[i][1] - 1][1];

		vertices[vert_current + 8] = vert[trian[i][3] - 1][0];
		vertices[vert_current + 9] = vert[trian[i][3] - 1][1];
		vertices[vert_current + 10] = vert[trian[i][3] - 1][2];
		vertices[vert_current + 11] = norm[trian[i][5] - 1][0];
		vertices[vert_current + 12] = norm[trian[i][5] - 1][1];
		vertices[vert_current + 13] = norm[trian[i][5] - 1][2];
		vertices[vert_current + 14] = coord[trian[i][4] - 1][0];
		vertices[vert_current + 15] = coord[trian[i][4] - 1][1];

		vertices[vert_current + 16] = vert[trian[i][6] - 1][0];
		vertices[vert_current + 17] = vert[trian[i][6] - 1][1];
		vertices[vert_current + 18] = vert[trian[i][6] - 1][2];
		vertices[vert_current + 19] = norm[trian[i][8] - 1][0];
		vertices[vert_current + 20] = norm[trian[i][8] - 1][1];
		vertices[vert_current + 21] = norm[trian[i][8] - 1][2];
		vertices[vert_current + 22] = coord[trian[i][7] - 1][0];
		vertices[vert_current + 23] = coord[trian[i][7] - 1][1];

		vert_current += 24;
	}

	for (auto i : objects) {
		for (auto j : i) {
			std::cout << j << ' ';
		}
		std::cout << std::endl;
	}

	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * triangles * 24, vertices, GL_STATIC_DRAW);

	punkty_ = triangles * 3;

	delete vertices;

	for (int i = 0; i < vert_num; i++)
		delete[] vert[i];
	delete[] vert;

	for (int i = 0; i < triangles; i++)
		delete[] trian[i];
	delete[] trian;

	for (int i = 0; i < normals; i++)
		delete[] norm[i];
	delete[] norm;

	for (int i = 0; i < coord_num; i++)
		delete[] coord[i];
	delete[] coord;

	return 0;
}

void functions::bindTextureModel(GLint _primitive, std::vector<unsigned int>& _textures, std::vector<std::vector<int>>& _objects) {
	// krzesla
	glBindTexture(GL_TEXTURE_2D, _textures[0]);
	glDrawArrays(_primitive, _objects[1][0], _objects[1][1]);
	glDrawArrays(_primitive, _objects[2][0], _objects[2][1]);
	glDrawArrays(_primitive, _objects[3][0], _objects[3][1]);
	glDrawArrays(_primitive, _objects[4][0], _objects[4][1]);

	// stol
	glBindTexture(GL_TEXTURE_2D, _textures[1]);
	glDrawArrays(_primitive, _objects[0][0], _objects[0][1]);

	// pilka
	glBindTexture(GL_TEXTURE_2D, _textures[2]);
	glDrawArrays(_primitive, _objects[5][0], _objects[5][1]);

	// cylinder
	glBindTexture(GL_TEXTURE_2D, _textures[3]);
	glDrawArrays(_primitive, _objects[6][0], _objects[6][1]);
}