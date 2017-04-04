#include <iostream>

#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>

using namespace std;
const GLint WIDTH = 800, HEIGHT = 600;

static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//cuando se pulsa una tecla escape cerramos la aplicacion
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int main() {

	GLFWwindow* window;
	glfwSetErrorCallback(error_callback);

	//comprobar que GLFW estaactivo
	if (!glfwInit())
		exit(EXIT_FAILURE);

	//crear la ventana
	window = glfwCreateWindow(WIDTH, HEIGHT, "Primera ventana", nullptr, nullptr);
	if (!window) {
		cout << "Error al crear la ventana" << endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	if (GLEW_OK != glewInit()) {
		std::cout << "Error al inicializar glew" << std::endl;
		glfwTerminate();
		return NULL;
	}

	int screenWithd, screenHeight;
	glfwGetFramebufferSize(window, &screenWithd, &screenHeight);

	//que funcion se llama cuando se detecta una pulsaci�n de tecla en la ventana x
	glfwSetKeyCallback(window, key_callback);

	while (!glfwWindowShouldClose(window)) {
		////definir las dimensiones del buffer
		//int screenWithd, screenHeigtht;
		//float ratio;
		//glfwGetFramebufferSize(window, &screenWithd, &screenHeigtht);
		//ratio = screenWithd / (float)screenHeigtht;

		//origen de la camara, dimensiones de la ventana
		glViewport(0, 0, screenWithd, screenHeight);
		glClear(GL_COLOR_BUFFER_BIT);

		//color de fondo
		glClearColor(0, 0, 0, 1.0);

		//definir la matriz de proyeccion
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-10, 10, -10.f, 10.f, -1.0f, 10.f);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		//glRotatef((float)glfwGetTime() * 50.f,1.f, 0.f, 0.f);

		//para volver a dejar la rotacion parada
		//glLoadIdentity();

#if(false)
		glPointSize(10.0f);
		glColor3f(0.0f, 0.0f, 0.0f);
		glBegin(GL_POINTS);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.5f, 0.5f, 0.0f);
		glEnd();
#endif

#if(false)
		GLfloat angulo;
		glLineWidth(10.0f);
		glBegin(GL_LINES);
		//for (int i = 0; i < 360; i += 3) {
		//	glColor3f(0.0f, 0.0f, 0.0f);
		//	angulo = (GLfloat) i*3.141519f / 180.f; //grados a radianes
		//	glVertex3f(0.0f, 0.0f, 0.0f);
		//	glVertex3f(cos(angulo), sin(angulo), 0.0f);
		//}
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex3f(6.0f, 2.f, 0.f);
		glColor3f(1.0f, 0.5f, 0.5f);
		glVertex3f(0.f, 0.f, 0.f);
		glEnd();
#endif

#if(false)
		glLineWidth(3.0f);
		glColor3f(0.0f, 0.0f, 0.0f);
		glBegin(GL_LINE_STRIP);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(-5.5f, 0.5f, 0.0f);
		//glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(6.5f, -5.5f, 0.0f);
		glEnd();
#endif

#if(false)
		glLineWidth(1.0f);
		glColor3f(0.0f, 0.0f, 0.0f);
		glBegin(GL_LINE_LOOP);
		glVertex3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.f, 2.f, 0.0f);
		glVertex3f(0.f, -0.5f, 0.0f);
		glVertex3f(5.f, 0.f, 0.f);
		glEnd();
#endif

#if(false)
		glClear(GL_COLOR_BUFFER_BIT);
		//color de dibujo
		glColor3f(0.0, 0.0, 0.0);
		//grosor de l�nea
		glLineWidth(2.0);
		//se activa el patr�n de l�nea
		glEnable(GL_LINE_STIPPLE);
		for (int i = 1; i < 7; i++) {
			glTranslatef(1.0, 0.0, 0.0);
			glLineStipple(i, 0xAAAA);
			glBegin(GL_LINES);
			glVertex3f(-3.5f, -2.0f, 0.0f);
			glVertex3f(-3.5f, 3.0f, 0.0f);
			glEnd();
		}
		glDisable(GL_LINE_STIPPLE);
#endif

#if(false)
		glBegin(GL_TRIANGLES);
		glColor3f(1.f, 0.f, 0.f);
		glVertex3f(-6.6f, -4.4f, 0.f);
		glColor3f(0.f, 1.f, 0.f);
		glVertex3f(6.6f, -4.4f, 0.f);
		glColor3f(0.f, 0.f, 1.f);
		glVertex3f(0.f, 6.6f, 0.f);
		glEnd();
#endif

#if(true)
		
		////activar el culling
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		////GL_CW sentido horario, GL_CCW sentido antihorario
		glFrontFace(GL_CCW);
		
		//Carcassa
		glBegin(GL_QUADS);
		glColor3f(0.1f, 0.1f, 0.1f);

		glVertex3f(-2.5f, 5.0f, 0.0f);
		glVertex3f(-2.5f, -6.0f, 0.0f);
		glVertex3f(2.5f, -6.0f, 0.0f);
		glVertex3f(2.5f, 5.0f, 0.0f);


		//Pantalla
		glColor3f(0.3f, 0.3f, 0.7f);

		glVertex3f(-2.0f, 4.0f, 0.0f);
		glVertex3f(-2.0f, -4.0f, 0.0f);
		glVertex3f(2.0f, -4.0f, 0.0f);
		glVertex3f(2.0f, 4.0f, 0.0f);


		//Altaveu
		glColor3f(0.3f, 0.3f, 0.3f);

		glVertex3f(-1.0f, 4.6f, 0.0f);
		glVertex3f(-1.0f, 4.3f, 0.0f);
		glVertex3f(1.0f, 4.3f, 0.0f);
		glVertex3f(1.0f, 4.6f, 0.0f);


		glEnd();

		//Boto back
		glBegin(GL_TRIANGLES);
		glColor3f(0.3f, 0.3f, 0.3f);

		glVertex3f(-1.0f, -4.3f, 0.0f);
		glVertex3f(-1.5f, -4.6f, 0.0f);
		glVertex3f(-1.0f, -4.9f, 0.0f);


		glEnd();

		//Boto Opcions
		glBegin(GL_QUADS);
		glColor3f(0.3f, 0.3f, 0.3f);

		glVertex3f(0.8f, -4.3f, 0.0f);
		glVertex3f(0.8f, -4.9f, 0.0f);
		glVertex3f(1.3f, -4.9f, 0.0f);
		glVertex3f(1.3f, -4.3f, 0.0f);


		glEnd();

		//Boto Menu
		glBegin(GL_POLYGON);

		glColor3f(0.3f, 0.3f, 0.3f);

		glVertex3f(-0.2f, -4.3f, 0.f);
		glVertex3f(-0.4f, -4.5f, 0.f);



		glVertex3f(-0.4f, -4.7f, 0.f);
		glVertex3f(-0.2f, -4.9f, 0.f);


		glVertex3f(0.2f, -4.9f, 0.f);
		glVertex3f(0.4f, -4.7f, 0.f);


		glVertex3f(0.4f, -4.5f, 0.f);
		glVertex3f(0.2f, -4.3f, 0.f);


		glEnd();

		//Cara
		glBegin(GL_POLYGON);

		glColor3f(1.f, 1.f, 0.1f);

		glVertex3f(-0.4f, 1.0f, 0.f);
		glVertex3f(-0.8f, 0.4f, 0.f);


		
		glVertex3f(-0.8f, -0.4f, 0.f);
		glVertex3f(-0.4f, -1.0f, 0.f);

		
		glVertex3f(0.4f, -1.0f, 0.f);
		glVertex3f(0.8f, -0.4f, 0.f);

		
		glVertex3f(0.8f, 0.4f, 0.f);
		glVertex3f(0.4f, 1.0f, 0.f);

		
		glEnd();

		//Ojo izquierdo
		glBegin(GL_QUADS);
		glColor3f(0.1f, 0.5f, 1.f);

		glVertex3f(-0.6f, 0.4f, 0.f);
		glVertex3f(-0.6f, 0.f, 0.f);
		glVertex3f(-0.2f, 0.f, 0.f);
		glVertex3f(-0.2f, 0.4f, 0.f);

		//Ojo derecho
		glColor3f(0.1f, 0.5f, 1.f);

		glVertex3f(0.2f, 0.4f, 0.f);
		glVertex3f(0.2f, 0.f, 0.f);
		glVertex3f(0.6f, 0.f, 0.f);
		glVertex3f(0.6f, 0.4f, 0.f);


		//Boca
		glColor3f(1.f, 0.f, 0.f);

		glVertex3f(-0.6f, -0.2f, 0.0f);
		glVertex3f(-0.2f, -0.6f, 0.0f);
		glVertex3f(0.2f, -0.6f, 0.0f);
		glVertex3f(0.6f, -0.2f, 0.0f);


		glEnd();

		glDisable(GL_CULL_FACE);

#endif

#if(false)
		glBegin(GL_QUADS);
		glColor3f(0.f, 0.f, 0.1f);
		glVertex3f(-1.0f, 2.f, 0.f);
		glVertex3f(-2.0f, 1.f, 0.f);

		glColor3f(0.f, 0.f, 0.1f);
		glVertex3f(2.0f, 1.f, 0.f);
		glVertex3f(1.0f, 2.f, 0.f);
		glEnd();
#endif

#if(false)
		glBegin(GL_QUAD_STRIP);
		glColor3f(0.f, 0.f, 1.f);
		glVertex3f(-2.0f, -1.f, 0.f);
		glVertex3f(-2.0f, 1.f, 0.f);

		glColor3f(0.f, 1.f, 0.f);
		glVertex3f(-1.0f, -2.f, 0.f);
		glVertex3f(-1.0f, 2.f, 0.f);

		glColor3f(1.f, 0.f, 0.f);
		glVertex3f(1.0f, -2.f, 0.f);
		glVertex3f(1.0f, 2.f, 0.f);

		glColor3f(0.5f, 0.5f, 0.5f);
		glVertex3f(2.0f, -1.f, 0.f);
		glVertex3f(2.0f, 1.f, 0.f);

		glEnd();
#endif

#if(false)
		glBegin(GL_TRIANGLE_STRIP);
		glColor3f(0.f, 0.f, 1.f);
		glVertex3f(-2.0f, -1.f, 0.f);
		glVertex3f(-1.0f, -2.f, 0.f);
		glVertex3f(-2.0f, 1.f, 0.f);

		glColor3f(0.f, 1.f, 0.f);
		glVertex3f(-2.0f, 1.f, 0.f);
		glVertex3f(-1.0f, -2.f, 0.f);
		glVertex3f(-1.0f, 2.f, 0.f);

		glColor3f(1.f, 0.f, 0.f);
		glVertex3f(-1.0f, 2.f, 0.f);
		glVertex3f(-1.0f, -2.f, 0.f);
		glVertex3f(1.0f, -2.f, 0.f);

		glColor3f(0.f, 0.f, 1.f);
		glVertex3f(1.0f, -2.f, 0.f);
		glVertex3f(-1.0f, 2.f, 0.f);
		glVertex3f(1.0f, 2.f, 0.f);

		glColor3f(0.f, 1.f, 0.f);
		glVertex3f(1.0f, 2.f, 0.f);
		glVertex3f(1.0f, -2.f, 0.f);
		glVertex3f(2.0f, -1.f, 0.f);

		glColor3f(1.f, 0.f, 0.f);
		glVertex3f(2.0f, -1.f, 0.f);
		glVertex3f(2.0f, 1.f, 0.f);
		glVertex3f(1.0f, 2.f, 0.f);

		glEnd();
#endif

#if(false)
		glBegin(GL_TRIANGLE_FAN);
		glColor3f(1.f, 1.f, 1.f);
		glVertex3f(0.f, 0.f, 0.f);
		glColor3f(0.f, 0.f, 1.f);
		glVertex3f(-2.0f, 1.f, 0.f);
		glVertex3f(-2.0f, -1.f, 0.f);

		glColor3f(0.f, 1.f, 0.f);
		glVertex3f(-2.0f, -1.f, 0.f);
		glVertex3f(-1.0f, -2.f, 0.f);

		glColor3f(1.f, 0.f, 0.f);
		glVertex3f(-1.0f, -2.f, 0.f);
		glVertex3f(1.0f, -2.f, 0.f);

		glColor3f(0.f, 0.f, 1.f);
		glVertex3f(1.0f, -2.f, 0.f);
		glVertex3f(2.0f, -1.f, 0.f);

		glColor3f(0.f, 1.f, 0.f);
		glVertex3f(2.0f, -1.f, 0.f);
		glVertex3f(2.0f, 1.f, 0.f);

		glColor3f(1.f, 0.f, 0.f);
		glVertex3f(2.0f, 1.f, 0.f);
		glVertex3f(1.0f, 2.f, 0.f);

		glColor3f(0.f, 0.f, 1.f);
		glVertex3f(1.0f, 2.f, 0.f);
		glVertex3f(-1.0f, 2.f, 0.f);

		glColor3f(0.f, 1.f, 0.f);
		glVertex3f(-1.0f, 2.f, 0.f);
		glVertex3f(-2.0f, 1.f, 0.f);

		glEnd();
#endif

		//intercambia el framebuffer
		glfwSwapBuffers(window);
		//comprueba que algun disparador se halla activado (tales como el teclado, raton, etc)
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}