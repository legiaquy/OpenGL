#include"libs.h"

Primitive test();

// About sending sizeof pointers and errors

void framebuffer_resize_callback(GLFWwindow* window, int fbW, int fbH) {
	glViewport(0, 0, fbW, fbH);
}

bool loadShaders(GLuint &program) {
	bool loadSuccess = true;
	char infoLog[512];
	GLint success;

	std::string temp = "";
	std::string src = "";

	std::ifstream in_file;

	//Vertex
	in_file.open("vertex_core.glsl");

	if (in_file.is_open()) {
		while (std::getline(in_file, temp))
			src += temp + "\n";
	}
	else {
		std::cout << "ERROR::LOADSHADERS::COULD_NOT_OPEN_VERTEX_FILE" << "\n";
		loadSuccess = false;
	}
	in_file.close();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const GLchar* vertSrc = src.c_str();
	glShaderSource(vertexShader, 1, &vertSrc, NULL);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::LOADSHADERS::COULD_NOT_COMPILE_VERTEX_SHADER" << "\n";
		std::cout << infoLog << "\n";
		loadSuccess = false;
	}

	temp = "";
	src = "";

	//Fragment
	in_file.open("fragment_core.glsl");

	if (in_file.is_open()) {
		while (std::getline(in_file, temp))
			src += temp + "\n";
	}
	else {
		std::cout << "ERROR::LOADSHADERS::COULD_NOT_OPEN_FRAGMENT_FILE" << "\n";
		loadSuccess = false;
	}
		in_file.close();

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar* fragSrc = src.c_str();
	glShaderSource(fragmentShader, 1, &fragSrc, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::LOADSHADERS::COULD_NOT_COMPILE_FRAGMENT_SHADER" << "\n";
		std::cout << infoLog << "\n";
		loadSuccess = false;
	}


	//Program
	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "ERROR::LOADSHADERS::COULD_NOT_LINK_PROGRAM" << "\n";
		std::cout << infoLog << "\n";
	}

	//End
	glUseProgram(0);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return loadSuccess;
}

void updateInput(GLFWwindow* window, Mesh &mesh) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		mesh.move(glm::vec3(0.f, 0.f, -0.01f));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		mesh.move(glm::vec3(0.f, 0.f, 0.01f));
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		mesh.move(glm::vec3(-0.01f, 0.f, 0.f));
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		mesh.move(glm::vec3(0.01f, 0.f, 0.f));
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		mesh.rotate(glm::vec3(0.f, -1.f, 0.f));
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		mesh.rotate(glm::vec3(0.f, 1.f, 0.f));
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		mesh.rotate(glm::vec3(-1.f, 0.f, 0.f));
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		mesh.rotate(glm::vec3(1.f, 0.f, 0.f));
	}
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
		mesh.scaleUp(glm::vec3(0.01f));
	}
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
		mesh.scaleUp(glm::vec3(-0.01f));
	}

}
int main() {
	//Init GLFW
	glfwInit();
	
	//Create window
	const int WINDOW_WIDTH = 640;
	const int WINDOW_HEIGHT = 480;
	int framebufferWidth = 0;
	int framebufferHeight = 0;

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);


	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Shining Hamburger", NULL, NULL);
	
	glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
	glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);
	
	//glViewport(0, 0, framebufferWidth, framebufferHeight);

	glfwMakeContextCurrent(window); //IMPORTANT!!

	//Init flew (Needs Window and Opengl COntext)
	glewExperimental = GL_TRUE;

	//Error
	if (glewInit() != GLEW_OK) {
		std::cout << "ERROR::MAIN.CPP::GLEW_INIT_FAILED" << "\n";
		glfwTerminate();
	}

	//OPENGL OPTIONS
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//SHADER INIT
	Shader core_program("vertex_core.glsl", "fragment_core.glsl");

	//MODEL MESH
	Mesh test(&Cube(),
		glm::vec3(0.f),
		glm::vec3(0.f),
		glm::vec3(1.f)
	);

	//TEXTURE INIT

	//Texture 0
	Texture texture0("images/burger.png", GL_TEXTURE_2D, 0);

	//Texture 1
	Texture texture1("images/container.png", GL_TEXTURE_2D, 1);


	//INIT MATRICES
	glm::vec3 camPosition(0.f, 0.f, 1.5f);
	glm::vec3 worldUp = glm::vec3(0.f, 1.f, 0.f);
	glm::vec3 camFront = glm::vec3(0.f, 0.f, -1.f);
	glm::mat4 ViewMatrix(1.f);
	ViewMatrix = glm::lookAt(camPosition, camPosition + camFront, worldUp);

	float fov = 90.f;
	float nearPlane = 0.1f;
	float farPlane = 1000.f;
	glm::mat4 ProjectionMatrix(1.f);

	ProjectionMatrix = glm::perspective(
		glm::radians(fov),
		static_cast<float>(framebufferWidth) / framebufferHeight,
		nearPlane,
		farPlane
	);

	//LIGHTS
	glm::vec3 lightPos0(0.f, 0.f, -1.f);

	//INIT UNIFORMS
	core_program.setMat4fv(ViewMatrix, "ViewMatrix");
	core_program.setMat4fv(ProjectionMatrix, "ProjectionMatrix");

	core_program.setVec3f(lightPos0, "lightPos0");
	core_program.setVec3f(camPosition, "cameraPos");

	//Main loop
	while (!glfwWindowShouldClose(window)) {
		//UPDATE INPUT 
		glfwPollEvents();
		updateInput(window, test);


		//UPDATE
		//updateInput(window);

		//DRAW
		//Clear
		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		

		//Update uniforms
		core_program.setli(texture0.getTextureUnit(), "texture0");
		core_program.setli(texture1.getTextureUnit(), "texture1");


		//Update framebuffer size and projection matrix
		glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);

		ProjectionMatrix = glm::perspective(
			glm::radians(fov),
			static_cast<float>(framebufferWidth) / framebufferHeight,
			nearPlane,
			farPlane
		);

		core_program.setMat4fv(ProjectionMatrix, "ProjectionMatrix");

		//Use a Program
		core_program.use();

		//Activate texture
		texture0.bind();
		texture1.bind();

		//Draw
		test.render(&core_program);

		//End Draw
		glfwSwapBuffers(window);
		glFlush();

		glBindVertexArray(0);
		glUseProgram(0);
		glActiveTexture(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	//END OF PROGRAM
	glfwDestroyWindow(window);
	glfwTerminate();

	//Delete VAO and Buffers

	return 0;
}