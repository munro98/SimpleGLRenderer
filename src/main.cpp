
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include<glm/glm.hpp>

#include "TriangleRenderer.hpp"
#include "SimpleGUI.hpp"
#include "Shader.hpp"
#include "OBJLoader.hpp"
#include "ModelShader.hpp"
#include "Camera.hpp"
#include "Loader.hpp"
#include "ModelRenderer.hpp"
#include "SkyboxRenderer.hpp"


using namespace std;


GLFWwindow* window;

static const float fovx = 80.0f;
static const float znear = 0.1f;
static const float zfar = 1000.0f;


bool leftMouseDown = false;
glm::vec2 mousePosition;


bool hasWindowFocus = true;


void windowFocusCallback(GLFWwindow* win, int focused) {
	if (focused)
	{
		hasWindowFocus = true;// The window gained input focus
	}
	else
	{
		hasWindowFocus = false;// The window lost input focus
	}
}

// Mouse Button callback
// Called for mouse movement event on since the last glfwPollEvents
void cursorPosCallback(GLFWwindow* win, double xpos, double ypos) {
	// cout << "Mouse Movement Callback :: xpos=" << xpos << "ypos=" << ypos << endl;
	mousePosition = glm::vec2(xpos, ypos);
}



// Mouse Button callback
// Called for mouse button event on since the last glfwPollEvents
void mouseButtonCallback(GLFWwindow *win, int button, int action, int mods) {
	// cout << "Mouse Button Callback :: button=" << button << "action=" << action << "mods=" << mods << endl;
	// send messages to the GUI manually
	SimpleGUI::mouseButtonCallback(win, button, action, mods);

	if (button == GLFW_MOUSE_BUTTON_LEFT)
		leftMouseDown = (action == GLFW_PRESS);
}


//Scroll callback
//Called for scroll event on since the last glfwPollEvents
void scrollCallback(GLFWwindow *win, double xoffset, double yoffset) {
	// cout << "Scroll Callback :: xoffset=" << xoffset << "yoffset=" << yoffset << endl;
}


//Keyboard callback
//Called for every key event on since the last glfwPollEvents
void keyCallback(GLFWwindow *win, int key, int scancode, int action, int mods) {
	// cout << "Key Callback :: key=" << key << "scancode=" << scancode
	// 	<< "action=" << action << "mods=" << mods << endl;

}


//Character callback
//Called for every character input event on since the last glfwPollEvents
void charCallback(GLFWwindow *win, unsigned int c) {
	// cout << "Char Callback :: c=" << char(c) << endl;

}



int main(int argc, char **argv) {

	//Initialize the GLFW library
	if (!glfwInit()) {
		cerr << "Error: Could not initialize GLFW" << endl;
		abort();
	}

	//glfwWindowHint(GLFW_SAMPLES, 4); // MSAA X 4
	//We want this version of gl
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Get the version for GLFW
	int glfwMajor, glfwMinor, glfwRevision;
	glfwGetVersion(&glfwMajor, &glfwMinor, &glfwRevision);

	//Create a windowed mode window and its OpenGL context
	window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
	if (!window) {
		cerr << "Error: Could not create GLFW window" << endl;
		abort();
	}

	// Make the window the current context.
	// If we have multiple windows we will need to switch contexts
	glfwMakeContextCurrent(window);


	// Initialize GLEW
	// must be done after making a GL context current (glfwMakeContextCurrent in this case)
	glewExperimental = GL_TRUE; // required for full GLEW functionality for OpenGL 3.0+
	GLenum err = glewInit();
	if (GLEW_OK != err) { // Problem: glewInit failed, something is seriously wrong.
		cerr << "Error: " << glewGetErrorString(err) << endl;
		abort(); // Unrecoverable error
	}

	//Print out this OpenGL verisions
	cout << "Using OpenGL " << glGetString(GL_VERSION) << endl;
	cout << "Using GLEW " << glewGetString(GLEW_VERSION) << endl;
	cout << "Using GLFW " << glfwMajor << "." << glfwMinor << "." << glfwRevision << endl;



	//Attach input callbacks to window
	glfwSetCursorPosCallback(window, cursorPosCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwSetScrollCallback(window, scrollCallback);
	glfwSetKeyCallback(window, keyCallback);
	glfwSetCharCallback(window, charCallback);
	glfwSetWindowFocusCallback(window, windowFocusCallback);

	


	// Initialize IMGUI
	if (!SimpleGUI::init(window, false)) {
		cerr << "Error: Could not initialize IMGUI" << endl;
		abort();
	}

	glm::mat4 projection = glm::perspective(80.0f, (float)640 / (float)480, 0.1f, 1000.0f);
	glm::mat4 model;

	Camera camera;
	SkyboxRenderer skyboxRenderer(projection);
	TriangleRenderer triangleRenderer;
	ModelRenderer ModelRenderer;

	Mesh* mesh = OBJLoader::loadObjModel("sphere");

	
	

	ModelShader shader = ModelShader("modelShader");
	shader.use();

	shader.loadProjectionMatrix(projection);
	shader.stop();

	Texture* texture2 = Loader::loadTexture("ground2048");

	while (!glfwWindowShouldClose(window)) {

		int width, height;
		glfwGetFramebufferSize(window, &width, &height);

		//Set viewport to be the whole window
		glViewport(0, 0, width, height);

		
		float xoffset = mousePosition.x - width / 2;
		float yoffset = mousePosition.y - height / 2;

		if (hasWindowFocus) {
			glfwSetCursorPos( window ,width / 2, height / 2);
		}

		float sensitivity = 0.1;
		xoffset = xoffset * sensitivity;
		yoffset = yoffset * sensitivity;
		camera.Rotate(xoffset, -yoffset);


		if (glfwGetKey(window, GLFW_KEY_A))
		{
			camera.Left();
		}

		if (glfwGetKey(window, GLFW_KEY_D))
		{
			camera.Right();
		}

		if (glfwGetKey(window, GLFW_KEY_W))
		{
			camera.Forward();
		}

		if (glfwGetKey(window, GLFW_KEY_S))
		{
			camera.Backward();
		}


		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		projection = glm::perspective(90.0f, (float)width / (float)height, 0.1f, 1000.0f);

		// Enable flags for normal rendering
		//glDisable(GL_CULL_FACE);
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);


		//triangleRenderer.render();

		//////////////////////////////////////////////////////
		glm::mat4 view;
		view = glm::lookAt(camera.GetPosition(), camera.GetPosition() + camera.GetFront(), camera.GetUp());


		shader.use();
		//Update uniforms
		shader.loadModelMatrix(model);
		shader.loadViewMatrix(view);
		shader.loadProjectionMatrix(projection);

		glBindVertexArray(mesh->getVaoID());


		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		//Bind texture
		glActiveTexture(GL_TEXTURE0);
		texture2->bind();

		glDrawElements(GL_TRIANGLES, mesh->getVertexCount(), GL_UNSIGNED_INT, 0);


		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		//*/
		glBindVertexArray(0);


		//glDisable(GL_DEPTH_TEST);

		skyboxRenderer.render(view, model);

		// Render GUI on top
		SimpleGUI::render();

		//Swap front and back buffers
		glfwSwapBuffers(window);

		//Poll for and process events
		glfwPollEvents();
	}

	glfwTerminate();
}
