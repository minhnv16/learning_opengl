#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);


int learning() {

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


	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.0f, 0.0f,
		 0.0f,  0.5f, 0.0f,

	};

	GLuint Elements[] = {
		0,1,2
	};


	//size_t nNum = 1000000000;
	//float* arrVrt = (float*)malloc(nNum * sizeof(float));
	//if (arrVrt) {
	//	memset(arrVrt, 0, nNum * sizeof(float));
	//}


	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);


	//vertex buffer objects
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	char const* VertexShaderSource = R"GLSL(

		#version 130
		 in vec3 aPos;
		void main()
		{
			gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
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
			#version 130
			out vec4 FragColor;
			void main()
			{
				FragColor = vec4(1.0f, 1.0f, 0.0f, 0.5f);
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


	GLuint shaderProgram;
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

	//glUseProgram(shaderProgram);

	//glBindVertexArray(VAO);

	//linking vertex attribute

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), 0);
	glEnableVertexAttribArray(0);



	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);

		glDrawArrays(GL_TRIANGLES, 0, 4);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


}