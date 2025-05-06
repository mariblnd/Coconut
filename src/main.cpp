#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "glbasimac/glbi_engine.hpp"
#include "glbasimac/glbi_set_of_points.hpp"
#include "glbasimac/glbi_convex_2D_shape.hpp"
#include <iostream>
#include <cmath>

using namespace glbasimac;

/* Minimal time wanted between two images */
static const double FRAMERATE_IN_SECONDS = 1. / 30.;
static float aspectRatio = 1.0f;

/* OpenGL Engine */
GLBI_Engine myEngine;

GLBI_Convex_2D_Shape carre;

static float rouge = 0.2f;
static float vert = 0.0f;
static float bleu = 0.0f;

std::vector<float> create_points_for_circle(float ray){

	std::vector<float> coord_pts;
	std::vector<float> center = {0.0f, 0.0f};	

	int nb_de_points = 30;

	for(int i = 0; i < nb_de_points; i++){
		float x = center[0] + ray * cos((i*2*M_PI)/nb_de_points);
		float y = center[1] + ray * sin((i*2*M_PI)/nb_de_points);
		coord_pts.push_back(x);
		coord_pts.push_back(y);
	}
	return coord_pts;
}


/* Error handling function */
void onError(int error, const char* description) {
	std::cout << "GLFW Error ("<<error<<") : " << description << std::endl;
}

/* Espace virtuel */
static const float GL_VIEW_SIZE = 1.0;
// L'univers 2D visible a une taille de 1.0 en x et en y

// Je n'ai pas le droit de le mettre dans le main
void onWindowResized(GLFWwindow* /*window*/, int width, int height)
{
  aspectRatio = width / (float) height;
  glViewport(0, 0, width, height);
  if( aspectRatio > 1.0){
	myEngine.set2DProjection(-GL_VIEW_SIZE * aspectRatio/ 2.,
		GL_VIEW_SIZE * aspectRatio / 2. ,
		-GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.);
  }
  else
  {
	myEngine.set2DProjection(-GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.,
		-GL_VIEW_SIZE / (2. * aspectRatio),
	   GL_VIEW_SIZE / (2. * aspectRatio));
  }
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_A && action == GLFW_PRESS){
		glfwSetWindowShouldClose(window, 1);
	}	
        
}

void initScene(){
	std::vector<float> coords = {
		-0.05f,  0.05f,
		-0.05f, -0.05f,
		 0.05f, -0.05f,
		 0.05f,  0.05f
	};
	carre.initShape(coords);
	carre.changeNature(GL_TRIANGLE_FAN);
}

void renderScene() {
	int rows = 20;
	int cols = 20;
	float squareSize = 0.1f;

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			float x = -1.0f + j * squareSize;
			float y =  1.0f - i * squareSize;

			if ((i + j) % 2 == 0)
				glColor3f(1.0f, 1.0f, 1.0f); // blanc
			else
				glColor3f(0.0f, 0.0f, 0.0f); // noir

			glPushMatrix();
			glTranslatef(x + squareSize / 2.0f, y - squareSize / 2.0f, 0.0f);
			carre.drawShape();
			glPopMatrix();
		}
	}
}




int main() {
	
    // Initialize the library
    if (!glfwInit()) {
        return -1;
    }

    /* Callback to a function if an error is rised by GLFW */
	glfwSetErrorCallback(onError);

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(1000, 1000, "Coconut", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }


    // Make the window's context current
    glfwMakeContextCurrent(window);

	//Callback
	glfwSetWindowSizeCallback(window, onWindowResized);
	glfwSetKeyCallback(window, key_callback);
	
	

	// Intialize glad (loads the OpenGL functions)
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		return -1;
	}

	
	// Initialize Rendering Engine
	myEngine.initGL();

    initScene();

	onWindowResized(window,1000,1000);

	


	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{

		/* Get time (in second) at loop beginning */
		double startTime = glfwGetTime();

		/* Render here */
		glClearColor(rouge,vert,bleu,1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		renderScene();
		
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		/* Elapsed time computation from loop begining */
		double elapsedTime = glfwGetTime() - startTime;
		/* If to few time is spend vs our wanted FPS, we wait */
		while(elapsedTime < FRAMERATE_IN_SECONDS)
		{
			glfwWaitEventsTimeout(FRAMERATE_IN_SECONDS-elapsedTime);
			elapsedTime = glfwGetTime() - startTime;
		}
	}

	// Intialize glad (loads the OpenGL functions)
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		return -1;
	}

    glfwTerminate();
    return 0;
}




   