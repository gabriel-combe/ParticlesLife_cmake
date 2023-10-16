#include "Sandbox.h"

double camZoom = 75.0f;

// Private Functions
void Sandbox::initGLFW() {
	// Init GLFW
	if(!glfwInit()) {
		std::cout << "ERROR::GLFW_INIT_FAILED" << "\n";
		glfwTerminate();
	}
}

void Sandbox::initWindow(const char* name, bool resizable) {
	// Specify GLFW version
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, this->GL_VERSION_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, this->GL_VERSION_MINOR);
	glfwWindowHint(GLFW_RESIZABLE, resizable);
	glfwWindowHint(GLFW_MAXIMIZED, GL_TRUE);

	// Create window object
	this->window = glfwCreateWindow(this->WINDOW_WIDTH, this->WINDOW_HEIGHT, name, NULL, NULL);
	if(this->window == NULL){
		std::cout << "ERROR::GLFW_WINDOW_INIT_FAILED" << "\n";
		glfwTerminate();
	}
	
	glfwGetFramebufferSize(this->window, &this->framebufferWidth, &this->framebufferHeight);

	// Register framebuffer_size_callback for resizing
	glfwSetFramebufferSizeCallback(this->window, Sandbox::framebuffer_size_callback);

	// Register callback function for mouse scroll
	glfwSetScrollCallback(this->window, Sandbox::mouseScrollCallback);

	glfwMakeContextCurrent(this->window);
}

void Sandbox::initGLAD() {
	// Initializing GLAD before any call of OpenGL function
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to Initialize GLAD" << std::endl;
		glfwTerminate();
	}
}

void Sandbox::initOpenGLOptions() {
	// Enable Depth testing
	glEnable(GL_DEPTH_TEST);

	// Set Cursor visibility mode
	//glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Sandbox::initImGui() {
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(this->window, true);
	ImGui_ImplOpenGL3_Init(this->GLSL_VERSION);

	// Setup Dear ImGui style
	ImGui::StyleColorsClassic();

	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 0.2f;
	}
}

void Sandbox::initParticles() {
	// Create the clusters
	this->clusters.push_back(Cluster(this->nb_particle, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)));
	this->clusters.push_back(Cluster(this->nb_particle, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)));
	this->clusters.push_back(Cluster(this->nb_particle, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)));
	//this->clusters.push_back(Cluster(this->nb_particle, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));

	this->vertices = this->clusters[0].getParticles();
	for (int i = 1; i < this->clusters.size(); i++)
		append(this->vertices, this->clusters[i].getParticles());

	// Create buffers
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);

	// Bind buffers
	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	
	// Store vertices in the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * this->vertices.size(), &this->vertices[0], GL_STATIC_DRAW);

	// Position Attribute
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Color Attribute
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(4 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

void Sandbox::initParticleEditor() {
	// Initialize the Particle Editor
	this->particleEditor.ParticleEditorInitialize();
}

void Sandbox::initShaders() {
	// Build and Compile shader program
	this->shaders.push_back(new Shader("shaders/vertex_shader.vs", "shaders/fragment_shader.fs"));
}

Sandbox::Sandbox(
	const char* name,
	const int WINDOW_WIDTH, const int WINDOW_HEIGHT,
	const int GL_VERSION_MAJOR, const int GL_VERSION_MINOR,
	const char* GLSL_VERSION,
	bool resizable
) :
	WINDOW_WIDTH(WINDOW_WIDTH),
	WINDOW_HEIGHT(WINDOW_HEIGHT),
	GL_VERSION_MAJOR(GL_VERSION_MAJOR),
	GL_VERSION_MINOR(GL_VERSION_MINOR),
	GLSL_VERSION(GLSL_VERSION){

	// Init Variables
	this->window = NULL;
	this->framebufferWidth = this->WINDOW_WIDTH;
	this->framebufferHeight = this->WINDOW_HEIGHT;

	this->dt = 0.0f;
	this->curTime = 0.0f;
	this->lastTime = 0.0f;

	this->lastMouseX = 0.0f;
	this->lastMouseY = 0.0f;
	this->mouseX = 0.0f;
	this->mouseY = 0.0f;
	this->mouseOffsetX = 0.0f;
	this->mouseOffsetY = 0.0f;
	this->firstMouse = true;

	this->focusedShader = 0;
	this->VAO = 0;
	this->VBO = 0;
	this->nb_particle = 500;

	this->loadLayout = true;

	this->initGLFW();
	this->initWindow(name, resizable);
	this->initGLAD();
	this->initOpenGLOptions();

	this->initParticles();
	this->initImGui();
	this->initParticleEditor();
	this->initShaders();
}

Sandbox::~Sandbox() {
	// De-allocate ressources
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);

	for(int i = 0; i < this->shaders.size(); i++)
		this->shaders[i]->programDelete();

	// Cleanup ImGui
	ImGui_ImplGlfw_Shutdown();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();

	// clean/delete all GLFW's resources allocated
	glfwDestroyWindow(this->window);
	glfwTerminate();
}

// WindowClose accessor
int Sandbox::getWindowShouldClose() {
	return glfwWindowShouldClose(this->window);
}

// WindowClose modifier
void Sandbox::setWindowShouldClose() {
	glfwSetWindowShouldClose(this->window, true);
}

// Functions
void Sandbox::updateDt() {
	this->curTime = static_cast<float>(glfwGetTime());
	this->dt = this->curTime - this->lastTime;
	this->lastTime = this->curTime;
	//std::cout << this->dt << std::endl;
}

void Sandbox::updateMouseInput() {
	glfwGetCursorPos(this->window, &this->mouseX, &this->mouseY);

	if(this->firstMouse) {
		this->lastMouseX = this->mouseX;
		this->lastMouseY = this->mouseY;
		this->firstMouse = false;
	}

	// Compute offset
	this->mouseOffsetX = this->mouseX - this->lastMouseX;
	this->mouseOffsetY = this->lastMouseY - this->mouseY;

	// Set last X and Y
	this->lastMouseX = this->mouseX;
	this->lastMouseY = this->mouseY;

	// Process mouse mouvement
	this->camera.ProcessMouseMovement(this->mouseOffsetX, this->mouseOffsetY);
}

void Sandbox::updateKeyboardInput() {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		this->resetTime = static_cast<float>(glfwGetTime());
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		this->camera.ProcessKeyboard(Camera_Movement::FORWARD, this->dt);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		this->camera.ProcessKeyboard(Camera_Movement::BACKWARD, this->dt);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		this->camera.ProcessKeyboard(Camera_Movement::LEFT, this->dt);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		this->camera.ProcessKeyboard(Camera_Movement::RIGHT, this->dt);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		this->camera.ProcessKeyboard(Camera_Movement::UP, this->dt);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		this->camera.ProcessKeyboard(Camera_Movement::DOWN, this->dt);
}

void Sandbox::updateInput() {
	ImGuiIO& io = ImGui::GetIO();

	glfwPollEvents();

	// Update keyboard only if we are not on a ImGui window
	if(!io.WantCaptureKeyboard)
		this->updateKeyboardInput();

	// Update mouse only if we are not on a ImGui window and we left click
	if (!io.WantCaptureMouse && glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		this->updateMouseInput();
		glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	} else {
		this->firstMouse = true;
		glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}

void Sandbox::updateImGui() {
	// ImGui new frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	// Create the docking environment
	ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus |
		ImGuiWindowFlags_NoBackground;

	// Get viewport info
	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize(viewport->Size);
	ImGui::SetNextWindowViewport(viewport->ID);

	// Dock Style
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

	// Create docking space
	ImGui::Begin("DockSpace", NULL, windowFlags);
	ImGui::PopStyleVar(3);
	ImGuiID dockSpaceID = ImGui::GetID("WindowDockSpace");

	if(loadLayout) {
		loadLayout = false;

		ImGui::DockBuilderRemoveNode(dockSpaceID); //Clear out existing layout
		ImGui::DockBuilderAddNode(dockSpaceID, ImGuiDockNodeFlags_DockSpace); //Add empty node
		ImGui::DockBuilderSetNodeSize(dockSpaceID, ImVec2(this->framebufferWidth, this->framebufferHeight)); //Set dock space size

		ImGuiID dockMain = dockSpaceID;
		ImGuiID dockEditor;

		ImGui::DockBuilderSplitNode(dockMain, ImGuiDir_Left, 0.2f, &dockEditor, &dockMain); //Split dock space in left and right part

		ImGui::DockBuilderDockWindow("Particle Editor", dockEditor); //Dock the node Editor to the down part

		ImGui::DockBuilderFinish(dockMain);
	}

	ImGui::DockSpace(dockSpaceID, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode | ImGuiDockNodeFlags_NoDockingInCentralNode);
	ImGui::End();
}

void Sandbox::updateParticles() {
	this->clusters[0].rule(this->clusters[0], -0.032f, this->dt);
	this->clusters[0].rule(this->clusters[1], -0.017f, this->dt);
	this->clusters[0].rule(this->clusters[2], 0.034f, this->dt);

	this->clusters[1].rule(this->clusters[1], -0.01f, this->dt);
	this->clusters[1].rule(this->clusters[0], -0.034f, this->dt);

	this->clusters[2].rule(this->clusters[2], 0.015f, this->dt);
	this->clusters[2].rule(this->clusters[0], -0.02f, this->dt);

	this->vertices = this->clusters[0].getParticles();
	for (int i = 1; i < this->clusters.size(); i++)
		append(this->vertices, this->clusters[i].getParticles());

	this->vertices.push_back(glm::vec4(-2.0f, -2.0f, 0.0f, 1.0f));
	this->vertices.push_back(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	this->vertices.push_back(glm::vec4(2.0f, -2.0f, 0.0f, 1.0f));
	this->vertices.push_back(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	this->vertices.push_back(glm::vec4(-2.0f, 2.0f, 0.0f, 1.0f));
	this->vertices.push_back(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	this->vertices.push_back(glm::vec4(2.0f, 2.0f, 0.0f, 1.0f));
	this->vertices.push_back(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	// Store vertices in the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * this->vertices.size(), &this->vertices[0], GL_STATIC_DRAW);
}

void Sandbox::updateParticleEditor() {
	// Show NodeEditor
	this->particleEditor.ParticleEditorShow();
}

void Sandbox::update() {
	// Update Delta Time
	this->updateDt();

	// Update Input
	this->updateInput();

	// Update Particles
	this->updateParticles();

	// Update ImGui
	this->updateImGui();

	// Update Node Editor
	this->updateParticleEditor();
}

void Sandbox::renderShaders() {
	// projection matrice
	glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)this->WINDOW_WIDTH / (float)this->WINDOW_HEIGHT, 0.1f, 100.0f);

	// view matrice
	glm::mat4 view = this->camera.GetViewMatrix();

	// Use the Program shader
	this->shaders[this->focusedShader]->use();

	this->shaders[this->focusedShader]->setFloat("iTime", this->curTime - this->resetTime);
	this->shaders[this->focusedShader]->setDVec2("iResolution", this->framebufferWidth, this->framebufferHeight);

	this->shaders[this->focusedShader]->setMat4("projection", projection);
	this->shaders[this->focusedShader]->setMat4("view", view);
}

void Sandbox::renderImGui() {
	// Render ImGui data
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	// Update and Render additional Platform Windows
	// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	}
}

void Sandbox::render() {
	// Update frame buffer size
	glfwGetFramebufferSize(this->window, &this->framebufferWidth, &this->framebufferHeight);

	// Clear the buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Render Shaders
	this->renderShaders();

	// Draw points
	glPointSize(4.0f);
	glBindVertexArray(this->VAO);
	glDrawArrays(GL_POINTS, 0, this->vertices.size()/2);

	// Render ImGui windows
	this->renderImGui();

	// Swap front and back buffers
	glfwSwapBuffers(this->window);
}

// Callback Functions
void Sandbox::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void Sandbox::mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	ImGuiIO& io = ImGui::GetIO();
	if(io.WantCaptureMouse) return;

	if (yoffset < 0.0f) camZoom *= 1.02;
	if (yoffset >= 0.0f) camZoom *= 0.98;
}