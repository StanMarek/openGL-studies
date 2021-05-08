#include "shaderClass.h"
#define BUFFER_SIZE 512

std::string get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	char bufferVertex[BUFFER_SIZE];
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

	this->ID = glCreateProgram();

	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);

	glLinkProgram(ID);
}

void Shader::Activate()
{
	glUseProgram(ID);
}

void Shader::Delete()
{
	glDeleteProgram(ID);
}
