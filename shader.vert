#version 150 core

in vec3 position;
in vec3 color;
out vec3 Color;
in vec2 aTexCoord;
out vec2 TexCoord;
in vec3 aNormal;
out vec3 Normal;
out vec3 FragPos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main(){
	TexCoord = aTexCoord;
	//Color = color;
	Normal = aNormal;
	gl_Position = proj * view * model * vec4(position, 1.0);
	FragPos = vec3(model * vec4(position, 1.0));
}
	