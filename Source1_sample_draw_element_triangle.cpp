#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>


char const* VertexShaderSource = R"GLSL(
		#version 130
		in vec2 position;
		void main()
		{
			gl_Position = vec4(position, 0.0, 1.0);
		}
	)GLSL";

char const* FragmentShaderSource = R"GLSL(
		#version 130
		out vec4 outColor;
		void main()
		{
			outColor = vec4(1.0, 0.0, 0.0, 1.0);
		}
	)GLSL";


//char const* VertexShaderSource1 = R"GLSL(
//		#version 130 core
//		 in vec3 aPos;
//		void main()
//		{
//			gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
//		}
//	)GLSL";
//
//char const* FragmentShaderSource1 = R"GLSL(
//		#version 130 core
//		out vec4 FragColor;
//		void main()
//		{
//			FragColor = vec4(1.0f, 0.2f, 0.4f, 1.0f);
//		}
//	)GLSL";


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (action == GLFW_PRESS) {

	}
	else if (action == GLFW_RELEASE) {

	}
	std::cout << "key:" << key << std::endl;

}
void get_resolution(int & window_width, int &window_height) {
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	window_width = mode->width;
	window_height = mode->height;
}

int sample_draw_element_triangle() {

	GLFWwindow* window = 0;
	if (GLFW_FALSE == glfwInit()) {
		return -1;
	}

	int nWidth = 800, nHeight = 600;
	//get_resolution(nWidth, nHeight);
	window = glfwCreateWindow(nWidth, nHeight, "Test OpenGL", NULL /* glfwGetPrimaryMonitor()*/, NULL);

	if (!window) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);

	//init glew
	GLenum err = glewInit();

	if (GLEW_OK != err) {
		glfwTerminate();
		return -1;
	}

	GLfloat Vertices[] = {
		0.0f, 0.5f,
		0.5f, -0.5f,
		-0.5f, -0.5f,
		0.5f,  0.0f

	};
	GLuint Elements[] = {
		0,1,2 
	};

	//Vertex Array Object
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//Vertex Buffer Object
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Element Buffer Object
	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Elements), Elements, GL_STATIC_DRAW);


	GLint Compiled;
	GLuint VertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShader, 1, &VertexShaderSource, NULL);
	glCompileShader(VertexShader);
	glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &Compiled);
	if (!Compiled) {
		std::cerr << "error compile vertex shader source!" << std::endl;
		return -1;
	}

	GLuint FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShader, 1, &FragmentShaderSource, NULL);
	glCompileShader(FragmentShader);
	glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &Compiled);
	if (!Compiled) {
		std::cerr << "error compile fragment shader source!" << std::endl;
		return -1;
	}

	GLuint ShaderProgram = glCreateProgram();
	glAttachShader(ShaderProgram, VertexShader);
	glAttachShader(ShaderProgram, FragmentShader);
	glBindFragDataLocation(ShaderProgram, 0, "outColor");
	glLinkProgram(ShaderProgram);
	glUseProgram(ShaderProgram);

	GLint PositionAttribute = glGetAttribLocation(ShaderProgram, "position");
	glEnableVertexAttribArray(PositionAttribute);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(PositionAttribute, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		glDrawElements(GL_LINE_LOOP, 3, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteProgram(ShaderProgram);
	glDeleteShader(FragmentShader);
	glDeleteShader(VertexShader);

	glDeleteBuffers(1, &EBO);
	glDeleteBuffers(1, &VBO);
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}


