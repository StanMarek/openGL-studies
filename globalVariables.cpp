#include "globalVariables.h"

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

bool firstMouse = true;

float rotation = 0;

double yaw = -90;
double pitch = 0;

int lastX = 0;
int lastY = 0;

GLint uniCamPos = 0;