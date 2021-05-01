#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"



extern glm::mat4x4 matMVP2;// = glm::mat4x4(1.0f);

extern unsigned int aVecColorLocation;
extern unsigned int aSelectedVecColorLocation;
extern unsigned int aNormalVecColorLocation;

extern glm::vec4 vecSelectedColor;// = glm::vec4(1.f, 0.f, 0.f, 1.f);
extern glm::vec4 vecNormalColor;// = glm::vec4(0.f, 0.f, 1.f, 1.f);

extern GLuint shaderProgram;
extern GLuint shaderProgram2;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void key_callback_learn3(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (action == GLFW_PRESS) {
		if (key == 32) {
			glm::vec4 tmp = vecSelectedColor;
			vecSelectedColor = vecNormalColor;
			vecNormalColor = tmp;
			glUniform4fv(aSelectedVecColorLocation, 1, glm::value_ptr(vecSelectedColor));
			glUniform4fv(aNormalVecColorLocation, 1, glm::value_ptr(vecNormalColor));

		}

		else if (key == 262) { //key right
			unsigned int aMvpLocation = glGetUniformLocation(shaderProgram, "mvp");
			//glm::mat4x4 matMVP = glm::mat4x4(1.0f);
			matMVP2 = glm::translate(matMVP2, glm::vec3(0.1f, 0.1f, 0));
			//matMVP2 = glm::scale(matMVP2, glm::vec3(1.1f, 1.1f, 0));

			glUniformMatrix4fv(aMvpLocation, 1, GL_FALSE, glm::value_ptr(matMVP2));
		}

		else if (key == 263) {//key lef


		}
		else if (key == 264) {//key down


		}
		else if (key == 265) {//key up


		}
	}
	else if (action == GLFW_RELEASE) {

	}
	std::cout << "key:" << key << std::endl;

}

int learn3() {

	GLFWwindow* window = 0;
	if (GLFW_FALSE == glfwInit()) {
		return -1;
	}

	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	int nWidth = 800, nHeight = 800;
	//get_resolution(nWidth, nHeight);
	window = glfwCreateWindow(nWidth, nHeight, "Test OpenGL", NULL/*glfwGetPrimaryMonitor()*/, NULL);

	if (!window) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback_learn3);

	//init glew
	GLenum err = glewInit();

	if (GLEW_OK != err) {
		glfwTerminate();
		return -1;
	}
	GLint compiled_status = -1;

	float vertices[] = {
		//location				//selected					//selected
		0.f,0.f,0.f,			0.f,

		0.25f, 0.0f, 0.0f,		1.f,
		0.25f, 0.25f, 0.0f,		1.f,
		0.5f,  0.25f, 0.0f,		1.f,
		0.5f,  0.0f, 0.0f,		1.f,
		0.375f,  0.125f, 0.0f,  1.f,

		-0.25f, 0.0f, 0.0f,		0.f,
		-0.25f, 0.25f, 0.0f,	0.f,
		-0.5f,  0.25f, 0.0f,	0.f,
		-0.5f,  0.0f, 0.0f,		0.f,
		-0.375f,  0.125f, 0.0f,	0.f,

	};




	GLuint elements[] = {
	1,2,3,4,5,
	0,
	6,7,8, 9, 10,
	};







	//vertex buffer objects
	GLuint VBO;
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

		in vec3 aPos;
		uniform mat4 mvp;
		in float  isSelected;
		
		out vec4 oColor; 
		uniform vec4 uSelectedColor;
		uniform vec4 uNormalColor;

		void main()
		{
			if(isSelected==0.f){
				oColor = uSelectedColor; // vec4(1.0f, 0.0f, 0.0f, 1.f);
			}
			else{
				oColor = uNormalColor; // vec4(0.0f, 1.0f, 0.0f, 1.f);
			}
			gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);

		}
		)GLSL";

	GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &VertexShaderSource, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compiled_status);
	if (!compiled_status)
	{
		char infoLog[512] = { 0 };
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}


	char const* FragmentShaderSource = R"GLSL(
		#version 330
		uniform vec4 vecColor;


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
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
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
	glVertexAttribPointer(aPosLocation, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glEnableVertexAttribArray(aPosLocation);


	unsigned int aPosSelected = glGetAttribLocation(shaderProgram, "isSelected");
	glVertexAttribPointer(aPosSelected, 1, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(aPosSelected);

	unsigned int aMvpLocation = glGetUniformLocation(shaderProgram, "mvp");
	glUniformMatrix4fv(aMvpLocation, 1, GL_FALSE, glm::value_ptr(matMVP2));



	aVecColorLocation = glGetUniformLocation(shaderProgram, "vecColor");
	aSelectedVecColorLocation = glGetUniformLocation(shaderProgram, "uSelectedColor");
	aNormalVecColorLocation = glGetUniformLocation(shaderProgram, "uNormalColor");




	//float vertices2[] = {
	//	//location				//selected
	//	0.70f, 0.0f, 0.0f,		1.f,

	//	0.70f, 0.0f, 0.0f,		1.f,
	//	0.70f, 0.25f, 0.0f,		1.f,
	//	0.95f,  0.25f, 0.0f,	1.f,
	//	0.95f,  0.0f, 0.0f,		1.f,
	//};

	//GLuint elements2[] = {
	//	1,2,3,4, 0
	//};
	////vertex2 buffer objects
	//GLuint VBO2;
	//glGenBuffers(1, &VBO2);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);	
	//
	////Element Buffer Object
	//GLuint EBO2;
	//glGenBuffers(1, &EBO2);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements2), elements2, GL_STATIC_DRAW);

	//char const* VertexShaderSource2 = R"GLSL(
	//	#version 330
	//	in vec3 aPos;
	//	void main()
	//	{
	//		gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);

	//	}
	//	)GLSL";


	//GLuint vertexShader2;
	//vertexShader2 = glCreateShader(GL_VERTEX_SHADER);
	//glShaderSource(vertexShader2, 1, &VertexShaderSource2, NULL);
	//glCompileShader(vertexShader2);
	//compiled_status = -1;
	//glGetShaderiv(vertexShader2, GL_COMPILE_STATUS, &compiled_status);
	//if (!compiled_status)
	//{
	//	char infoLog[512] = { 0 };
	//	glGetShaderInfoLog(vertexShader2, 512, NULL, infoLog);
	//	std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	//}


	//char const* FragmentShaderSource2 = R"GLSL(
	//	#version 330
	//	//uniform vec4 vecColor;
	//	//in vec4 oColor; 
	//	out vec4 FragColor;
	//	void main()
	//	{
	//		FragColor = vec4(1.0f, 1.0f, 0.0f, 1.f);
	//	}
	//	)GLSL";

	//GLuint fragmentShader2;
	//fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(fragmentShader2, 1, &FragmentShaderSource2, NULL);
	//glCompileShader(fragmentShader2);
	//compiled_status = -1;
	//glGetShaderiv(fragmentShader2, GL_COMPILE_STATUS, &compiled_status);
	//if (!compiled_status)
	//{
	//	char infoLog[512] = { 0 };
	//	glGetShaderInfoLog(fragmentShader2, 512, NULL, infoLog);
	//	std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	//}

	//shaderProgram2 = glCreateProgram();
	//glAttachShader(shaderProgram2, vertexShader2);
	//glAttachShader(shaderProgram2, fragmentShader2);
	//glLinkProgram(shaderProgram2);
	//glGetProgramiv(shaderProgram2, GL_LINK_STATUS, &compiled_status);
	//if (!compiled_status) {
	//	char infoLog[512] = { 0 };
	//	glGetProgramInfoLog(shaderProgram2, 512, NULL, infoLog);
	//	std::cout << "program \n" << compiled_status << std::endl;
	//}

	////linking vertex attribute
	//unsigned int aPosLocation2 = glGetAttribLocation(shaderProgram2, "aPos");
	//glVertexAttribPointer(aPosLocation2, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	//glEnableVertexAttribArray(aPosLocation2);



	glEnable(GL_PRIMITIVE_RESTART);
	//glPrimitiveRestartIndex(0);

	int n = 0;
	while (!glfwWindowShouldClose(window))
	{

		if (n < 2) {
			glUniform4fv(aSelectedVecColorLocation, 1, glm::value_ptr(vecSelectedColor));
			glUniform4fv(aNormalVecColorLocation, 1, glm::value_ptr(vecNormalColor));

		}

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		glUseProgram(shaderProgram);
		glDrawElements(GL_LINE_LOOP, sizeof(elements) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);

		//glUseProgram(shaderProgram2);
		//glDrawElements(GL_LINE_LOOP, sizeof(elements2) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();

		n++;
	}

	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	//glDeleteBuffers(1, &VBO2);
	//glDeleteBuffers(1, &EBO2);
	glDeleteProgram(shaderProgram);
	glDeleteProgram(shaderProgram2);
	glfwTerminate();

}

