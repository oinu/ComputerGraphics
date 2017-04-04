#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL\glew.h>
#include <GLFW\glfw3.h>

class shader
{
	
public:
	GLuint Program;
	shader(const GLchar*, const GLchar*);
	~shader();
	void USE();
};

