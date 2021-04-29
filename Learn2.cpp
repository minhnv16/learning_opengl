#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


extern glm::mat4x4 matMVP2 = glm::mat4x4(1.0f);
extern GLuint shaderProgram;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void key_callback_learn2(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (action == GLFW_PRESS) {
		unsigned int aMvpLocation = glGetUniformLocation(shaderProgram, "mvp");
		//glm::mat4x4 matMVP = glm::mat4x4(1.0f);
		matMVP2 = glm::translate(matMVP2, glm::vec3(0.1f, 0.1f, 0));
		//matMVP2 = glm::scale(matMVP2, glm::vec3(1.1f, 1.1f, 0));

		glUniformMatrix4fv(aMvpLocation, 1, GL_FALSE, glm::value_ptr(matMVP2));
	}
	else if (action == GLFW_RELEASE) {

	}
	std::cout << "key:" << key << std::endl;

}

int learn2() {

	GLFWwindow* window = 0;
	if (GLFW_FALSE == glfwInit()) {
		return -1;
	}

	int nWidth = 600, nHeight = 600;
	//get_resolution(nWidth, nHeight);
	window = glfwCreateWindow(nWidth, nHeight, "Test OpenGL", NULL /* glfwGetPrimaryMonitor()*/, NULL);

	if (!window) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback_learn2);

	//init glew
	GLenum err = glewInit();

	if (GLEW_OK != err) {
		glfwTerminate();
		return -1;
	}

	float vertices[] = {
	0.f,0.f,0.f, 1.f,0.f,0.f,1.f,

	0.25f, 0.0f, 0.0f,  1.f,0.f,0.f,1.f,
	0.25f, 0.25f, 0.0f, 0.f,1.f,0.f,1.f,
	0.5f,  0.25f, 0.0f, 0.f,0.f,1.f,1.f,
	0.5f,  0.0f, 0.0f,  1.f,0.f,1.f,1.f,
	0.375f,  0.125f, 0.0f,  1.f,1.f,0.f,1.f,

	-0.25f, 0.0f, 0.0f,		1.f,0.f,1.f,1.f,
	-0.25f, 0.25f, 0.0f,	0.f,1.f,0.f,1.f,
	-0.5f,  0.25f, 0.0f,	0.f,0.f,1.f,1.f,
	-0.5f,  0.0f, 0.0f,		1.f,1.f,0.f,1.f,
	-0.375f,  0.125f, 0.0f,	0.f,1.f,1.f,1.f,

	};

	GLuint elements[] = {
	1,2,3,4,5,
	0,
	6,7,8, 9, 10,
	};



	//vertex buffer objects
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	//Element Buffer Object
	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);


	char const* VertexShaderSource = R"GLSL(
		#version 330
		uniform mat4 mvp;
		in vec3 aPos;
		in vec4 aColor;
		
		out vec4 oColor; 
		void main()
		{
			gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
			oColor = aColor;
		}
		)GLSL";

	GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &VertexShaderSource, NULL);
	glCompileShader(vertexShader);
	GLint compiled_status = -1;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compiled_status);
	if (!compiled_status)
	{
		char infoLog[512] = { 0 };
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}


	char const* FragmentShaderSource = R"GLSL(
		#version 330

		out vec4 FragColor;
		in vec4 oColor; 

		void main()
		{
			FragColor = oColor;
		}
		)GLSL";

	GLuint fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &FragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	compiled_status = -1;
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compiled_status);
	if (!compiled_status)
	{
		char infoLog[512] = { 0 };
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}


	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &compiled_status);
	if (!compiled_status) {
		char infoLog[512] = { 0 };
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "program \n" << compiled_status << std::endl;
	}


	//linking vertex attribute
	unsigned int aPosLocation = glGetAttribLocation(shaderProgram, "aPos");
	glVertexAttribPointer(aPosLocation, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), 0);
	glEnableVertexAttribArray(aPosLocation);

	unsigned int aPosColor = glGetAttribLocation(shaderProgram, "aColor");
	glVertexAttribPointer(aPosColor, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(aPosColor);

	unsigned int aMvpLocation = glGetUniformLocation(shaderProgram, "mvp");
	glUniformMatrix4fv(aMvpLocation, 1, GL_FALSE, glm::value_ptr(matMVP2));





	glEnable(GL_PRIMITIVE_RESTART);
	glPrimitiveRestartIndex(0);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glDrawElements(GL_LINE_LOOP, sizeof(elements) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

