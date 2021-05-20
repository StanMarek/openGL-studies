#ifndef GLOBAL_VARAIBLES_H
#define GLOBAL_VARIABLES_H
#define M_PI 3.14159

#include <glm/gtc/type_ptr.hpp>

extern glm::vec3 cameraPos;
extern glm::vec3 cameraFront;
extern glm::vec3 cameraUp;

extern bool firstMouse;

extern float rotation;

extern double yaw;
extern double pitch;

extern int lastX;
extern int lastY;

#endif
