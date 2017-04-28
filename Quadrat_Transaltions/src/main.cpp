//GLEW
#define GLEW_STATIC
#define GLM_FORCE_RADIANS
#include <GL\glew.h>
//GLFW
#include <GLFW\glfw3.h>
#include <iostream>
#include "../shader.hpp"
#include <SOIL.h>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

using namespace std;
using namespace glm;
const GLint WIDTH = 800, HEIGHT = 600;
bool WIDEFRAME = true;
bool girEsquerra,girDreta;
float opacity = 0.5f;
float mangle=10.0f;

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
	shader programID("./src/TextureVertex.vertexshader", "./src/TextureFragment.fragmentshader");

	// Definir el buffer de vertices
	GLfloat cubeVertex[] = 
	{
		// Positions          // Colors           // Texture Coords
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left 
	};

	// Definir el EBO
	GLuint IndexBufferObject[]{
		0,1,2,
		2,3,0
	};

	//crear textura en opengl
	GLuint texture,texture2;
	glGenTextures(1, &texture);
	glGenTextures(1, &texture2);

	//enllaça la textures 
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, texture2);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//Cargar imagen

	int width, height,width2,height2;
	unsigned char* image;
	unsigned char* image2;

	image = SOIL_load_image("./src/texture.png", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, texture);

	image2 = SOIL_load_image("./src/texture2.png", &width2, &height2, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width2, height2, 0, GL_RGB, GL_UNSIGNED_BYTE, image2);
	SOIL_free_image_data(image2);
	glBindTexture(GL_TEXTURE_2D, texture2);

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
		
		//Vertex
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		//Colors
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		//Coordenada Textura
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);

		

		//liberar el buffer
	//liberar el buffer de vertices
		

	//bucle de dibujado
	while (!glfwWindowShouldClose(window))
	{

		//Matrix
		mat4 model = mat4(1.0);
		model = translate(model, vec3(0.5f, 0.5f, 0.0f));

		if (girDreta)
		{
			model = rotate(model, radians(mangle), vec3(0.0, 1.0, 0.0));
		}
		if (girEsquerra)
		{
			model = rotate(model, radians(mangle), vec3(0.0, -1.0, 0.0));
		}

		model = scale(model, vec3(0.5, 0.5, 0.0));

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

		//Passem textures
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glUniform1i(glGetUniformLocation(programID.Program, "text1"), 0);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		glUniform1i(glGetUniformLocation(programID.Program, "text2"), 1);

		//Passem l'opacitat
		GLint op;
		op = glGetUniformLocation(programID.Program, "opacity");
		glUniform1f(op, opacity);

		glUniformMatrix4fv(glGetUniformLocation(programID.Program, "transform"),1, GL_FALSE, glm::value_ptr(model));


		//establecer el shader
		programID.USE();
				

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
	if (key == GLFW_KEY_UP && opacity <1)
	{
		opacity += 0.1f;
	}
	else if (key == GLFW_KEY_DOWN && opacity>=0)
	{
		opacity -= 0.1f;
	}

	if (key == GLFW_KEY_LEFT)
	{
		mangle += 10.0f;
		girEsquerra = true;
		girDreta = false;
	}
	else if (key == GLFW_KEY_RIGHT)
	{
		mangle -= 10.0f;
		girDreta = true;
		girEsquerra = false;
	}
	else
	{
		girEsquerra = false;
		girDreta = false;
	}
}
