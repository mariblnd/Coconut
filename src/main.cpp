#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "glbasimac/glbi_engine.hpp"
#include "glbasimac/glbi_set_of_points.hpp"
#include "glbasimac/glbi_convex_2D_shape.hpp"

#include "Map.hpp"
#include "Tile.hpp"

#include <iostream>
#include <cmath>

using namespace glbasimac;

/* Minimal time wanted between two images */
static const double FRAMERATE_IN_SECONDS = 1. / 30.;
static float aspectRatio = 1.0f;

/* OpenGL Engine */
GLBI_Engine myEngine;



Map myMap(20,20); // Crée une carte de 20x20

GLBI_Convex_2D_Shape wallTiles;  
GLBI_Convex_2D_Shape emptyTiles;

std::vector<float> wallVertices;
std::vector<float> emptyVertices;


static float rouge = 0.0f;
static float vert = 0.0f;
static float bleu = 0.0f;


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

void initScene() {
    // Séparer les vertices selon le type
    for(const auto& current_tile : myMap.getTiles()) {
        auto tileVertices = current_tile.getVertices();
        if(current_tile.type == TileType::WALL) {
            wallVertices.insert(wallVertices.end(), tileVertices.begin(), tileVertices.end());
        } else {
            emptyVertices.insert(emptyVertices.end(), tileVertices.begin(), tileVertices.end());
        }
    }
    
    // Initialiser les deux formes
    wallTiles.changeNature(GL_TRIANGLE_FAN);
    wallTiles.initShape(wallVertices);
    
    emptyTiles.changeNature(GL_TRIANGLE_FAN);
    emptyTiles.initShape(emptyVertices);
}

void renderScene() {
    // WALL
    myEngine.setFlatColor(0.0f, 0.0f, 0.0f);
    wallTiles.drawShape();
    
    // EMPTY TILES
    myEngine.setFlatColor(0.5f, 0.5f, 0.5f);
    emptyTiles.drawShape();
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




   