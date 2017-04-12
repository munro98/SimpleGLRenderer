#pragma once

#include "imgui.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>


namespace SimpleGUI {
	void mouseButtonCallback(GLFWwindow*, int button, int action, int mods);
	void scrollCallback(GLFWwindow*, double xoffset, double yoffset);
	void keyCallback(GLFWwindow*, int key, int scancode, int action, int mods);
	void charCallback(GLFWwindow*, unsigned int c);
	bool init(GLFWwindow* window, bool install_callbacks=false);
	void shutdown();
	void newFrame();
	void render();
}
