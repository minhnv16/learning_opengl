
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
//			gl_Position = vec4(position, 0.0, 1.0);

char const* VertexShaderSource = R"GLSL(
		#version 130
		in vec2 position;
		void main()
		{
			gl_Position = vec4(position, 0.0, 1.0);
		}
	)GLSL";
//			outColor = vec4(1.0, 0.0, 0.0, 1.0);

char const* FragmentShaderSource = R"GLSL(
		#version 130
		out vec4 aoutColor1;
		void main()
		{
			aoutColor1 = vec4(1.0, 1.0, 0.0, 1.0);
		}
	)GLSL";

void PrintOpenGLErrors(char const* const Function, char const* const File, int const Line)
{
	bool Succeeded = true;

	GLenum Error = glGetError();
	if (Error != GL_NO_ERROR)
	{
		//char const* ErrorString = (char const*)gluErrorString(Error);
		//if (ErrorString)
		//	std::cerr << ("OpenGL Error in %s at line %d calling function %s: '%s'", File, Line, Function, ErrorString) << std::endl;
		//else
		//	std::cerr << ("OpenGL Error in %s at line %d calling function %s: '%d 0x%X'", File, Line, Function, Error, Error) << std::endl;
	}
}

void key_handle(GLFWwindow* window, int key, int scan, int action, int mode) {
	std::cout << "key:" << key << std::endl;
	if (key == 32) {
		std::cout << "key: = space" << key << std::endl;

	}
}


void PrintShaderInfoLog(GLint const Shader)
{
	int InfoLogLength = 0;
	int CharsWritten = 0;

	glGetShaderiv(Shader, GL_INFO_LOG_LENGTH, &InfoLogLength);

	if (InfoLogLength > 0)
	{
		GLchar* InfoLog = new GLchar[InfoLogLength];
		glGetShaderInfoLog(Shader, InfoLogLength, &CharsWritten, InfoLog);
		std::cout << "Shader Info Log:" << std::endl << InfoLog << std::endl;
		delete[] InfoLog;
	}
}

int glew_main1()
{
	GLFWwindow* window;

	if (!glfwInit())
		return -1;

	window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_handle);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
		glfwTerminate();
		return -1;
	}






	GLfloat const Vertices[] = {
		0.0f, 0.5f,
		0.5f, -0.5f,
		-0.5f, -0.5f
	};

	GLuint const Elements[] = {
		0, 1, 2
	};

	//GLuint VAO;
	//glGenVertexArrays(1, &VAO);
	//glBindVertexArray(VAO);

	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Elements), Elements, GL_STATIC_DRAW);

	GLint Compiled;
	GLuint VertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShader, 1, &VertexShaderSource, NULL);
	glCompileShader(VertexShader);
	glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &Compiled);
	if (!Compiled)
	{
		std::cerr << "Failed to compile vertex shader!" << std::endl;
		PrintShaderInfoLog(VertexShader);
	}

	GLuint FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShader, 1, &FragmentShaderSource, NULL);
	glCompileShader(FragmentShader);
	glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &Compiled);
	if (!Compiled)
	{
		std::cerr << "Failed to compile fragment shader!" << std::endl;
		PrintShaderInfoLog(FragmentShader);
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
	//glDeleteVertexArrays(1, &VAO);

	glfwTerminate();
	return 0;
}