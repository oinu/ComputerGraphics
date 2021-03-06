//GLEW
#define GLEW_STATIC
#include <GL\glew.h>
//GLFW
#include <GLFW\glfw3.h>
#include <iostream>
#include <shader.hpp>

using namespace std;
const GLint WIDTH = 800, HEIGHT = 600;
bool WIDEFRAME = false;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

int main() {
	//initGLFW
//TODO

	//set GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	//create a window

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Ventana", nullptr, nullptr);
	if (!window) {
		cout << "Error al crear la ventana" << endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);

//TODO

	//set GLEW and inicializate
	glewExperimental = GL_TRUE;
	if (GLEW_OK != glewInit()) {
		std::cout << "Error al inicializar glew" << std::endl;
		glfwTerminate();
		return NULL;
	}

	int screenWithd, screenHeight;
	glfwGetFramebufferSize(window, &screenWithd, &screenHeight);


//TODO

	//set function when callback
	glfwSetKeyCallback(window, key_callback);

//TODO

	//set windows and viewport
	glViewport(0, 0, screenWithd, screenHeight);
//TODO

	//fondo
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//TODO


	//cargamos los shader
	GLuint programID = LoadShaders("./src/SimpleVertexShader.vertexshader", "./src/SimpleFragmentShader.fragmentshader");

	// Definir el buffer de vertices
	GLfloat cubeVertex[] = {
		-1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,
		1.0f, 1.0f, -1.0f };

	GLuint IndexBufferObject[]{
		//0,1,3,
		//1,2,3 
		2,0,1,
		1,3,2
	};
	// Definir el EBO

	// Crear los VBO, VAO y EBO
	GLuint VBO, VAO, EBO;

	//reservar memoria para el VAO, VBO y EBO
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1,&VBO);
	glGenBuffers(1, &EBO);

	//Establecer el objeto
	glBindVertexArray(VAO);

		//Declarar el VBO y el EBO

		//Enlazar el buffer con openGL
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);

		//Establecer las propiedades de los vertices
		glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertex), cubeVertex, GL_STATIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(IndexBufferObject), IndexBufferObject, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		//liberar el buffer
	
	//liberar el buffer de vertices
		

	//bucle de dibujado
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glfwSwapBuffers(window);
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		if (WIDEFRAME == true) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		//Establecer el color de fondo
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//establecer el shader
		glUseProgram(programID);

		//pitar el VAO
		glBindVertexArray(VAO);

		//pintar con lineas
		glPolygonMode(GL_FRONT, GL_LINE);
		//pintar con triangulos
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// Swap the screen buffers
		glBindVertexArray(0);
		
	}
	// liberar la memoria de los VAO, EBO y VBO
	glfwSwapBuffers(window);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	// Terminate GLFW, clearing any resources allocated by GLFW.
	exit(EXIT_SUCCESS);
	glfwTerminate();
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	//TODO, comprobar que la tecla pulsada es escape para cerrar la aplicación y la tecla w para cambiar a modo widwframe
	//W
	if (key == GLFW_KEY_W && action == GLFW_PRESS) {
		if (WIDEFRAME == true) {
			glPolygonMode(GL_FRONT, GL_LINE);
			WIDEFRAME = false;
		}
		else {
			glPolygonMode(GL_FRONT, GL_FILL);
			WIDEFRAME = true;
		}
	}
}
