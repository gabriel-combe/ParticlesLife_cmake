#pragma once

#ifndef SANDBOX_H
#define SANDBOX_H

#include "Libs.h"
#include "utils.h"

class Sandbox {
private:
// Variables
	// Window
	GLFWwindow* window;
	const int WINDOW_WIDTH;
	const int WINDOW_HEIGHT;
	int framebufferWidth;
	int framebufferHeight;

	// OpenGL Context
	const int GL_VERSION_MAJOR;
	const int GL_VERSION_MINOR;

	// GLSL Version
	const char* GLSL_VERSION;

	// Delta Time
	float dt;
	float curTime;
	float lastTime;
	float resetTime;

	// Mouse Input
	double lastMouseX;
	double lastMouseY;
	double mouseX;
	double mouseY;
	double mouseOffsetX;
	double mouseOffsetY;
	bool firstMouse;

	// Camera
	Camera camera = Camera(glm::vec3(0.0f, 0.0f, 4.0f));

	// Shaders
	std::vector<Shader*> shaders;
	int focusedShader;

	// Particles
	std::vector<Cluster> clusters;
	std::vector<glm::vec4> vertices; //test
	unsigned int nb_particle;
	unsigned int VAO, VBO;

	// Particle Editor
	ParticleEditor particleEditor;
	bool loadLayout;

// Private Functions
	void initGLFW();
	void initWindow(const char* name, bool resizable);
	void initGLAD();
	void initOpenGLOptions();
	void initParticles();
	void initImGui();
	void initParticleEditor();
	void initShaders();


public:
// Constructor/Destructor
	Sandbox(
		const char* name, 
		const int WINDOW_WIDTH, const int WINDOW_HEIGHT,
		const int GL_VERSION_MAJOR, const int GL_VERSION_MINOR,
		const char* GLSL_VERSION,
		bool resizable
	);

	virtual ~Sandbox();

// WindowClose accessor
	int getWindowShouldClose();

// WindowClose modifier
	void setWindowShouldClose();

// Functions
	void updateDt();
	void updateMouseInput();
	void updateKeyboardInput();
	void updateInput();
	void updateImGui();
	void updateParticles();
	void updateParticleEditor();
	void update();
	void renderShaders();
	void renderImGui();
	void render();

// Callback Functions
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
};

#endif // !SANDBOX_H