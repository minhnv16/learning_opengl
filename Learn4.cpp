#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

glm::mat4x4 matMVP[] = { glm::mat4x4(1.0f) , glm::mat4x4(1.0f) , glm::mat4x4(1.0f) , glm::mat4x4(1.0f) };
unsigned int aMvpLocation[4];

extern unsigned int aSelectedVecColorLocation;
extern unsigned int aNormalVecColorLocation;
unsigned int selectedId;


extern glm::vec4 vecSelectedColor;// = glm::vec4(1.f, 0.f, 0.f, 1.f);
extern glm::vec4 vecNormalColor;// = glm::vec4(0.f, 0.f, 1.f, 1.f);

extern GLuint shaderProgram;
extern GLuint shaderProgram2;


struct Position {
	float fX = 0.f;
	float fY = 0.f;
	float fZ = 0.f;
	Position() {};
	Position(float x, float y, float z) {
		fX = x; fY = y; fZ = z;
	}
};

struct VertexAtt {
	Position posData;
	float fSelected = 0;
	float nObjectId = 0;

	VertexAtt() {};
	VertexAtt(const Position& pos,const float &selected, const float& objId= 0 ) {
		posData = pos;
		fSelected = selected;
		nObjectId = objId;
	}



};


void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void key_callback_learn4(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (action == GLFW_PRESS) {
		if (key >= 320 && key <= 323) {
			selectedId = key - 320;
		}
		if (key == 32) {
			glm::vec4 tmp = vecSelectedColor;
			vecSelectedColor = vecNormalColor;
			vecNormalColor = tmp;
			glUniform4fv(aSelectedVecColorLocation, 1, glm::value_ptr(vecSelectedColor));
			glUniform4fv(aNormalVecColorLocation, 1, glm::value_ptr(vecNormalColor));

		}

		if (key >= 262 && key <= 265) {

			switch (key)
			{
				case 262://key right
					matMVP[selectedId] = glm::translate(matMVP[selectedId], glm::vec3(0.1f, 0.0f, 0));
					break;				
				case 263://key lef
					matMVP[selectedId] = glm::translate(matMVP[selectedId], glm::vec3(-0.1f, 0.0f, 0));

					break;
				case 264://key down
					matMVP[selectedId] = glm::translate(matMVP[selectedId], glm::vec3(0.0f, -0.1f, 0));

					break;
				case 265://key up
					matMVP[selectedId] = glm::translate(matMVP[selectedId], glm::vec3(0.0f, +0.1f, 0));

					break;

			default:
				break;
			}
			glUniformMatrix4fv(aMvpLocation[selectedId], 1, GL_FALSE, glm::value_ptr(matMVP[selectedId]));

		}

		//if (key == 262) { //key right
		//	unsigned int aMvpLocation = glGetUniformLocation(shaderProgram, "mvp1");
		//	//glm::mat4x4 matMVP = glm::mat4x4(1.0f);
		//	l4_matMVP1 = glm::translate(l4_matMVP1, glm::vec3(0.1f, 0.1f, 0));
		//	//matMVP2 = glm::scale(matMVP2, glm::vec3(1.1f, 1.1f, 0));
		//	glUniformMatrix4fv(aMvpLocation, 1, GL_FALSE, glm::value_ptr(l4_matMVP1));
		//}

		//else if (key == 263) {//key lef
		//	unsigned int aMvpLocation = glGetUniformLocation(shaderProgram, "mvp2");
		//	l4_matMVP2 = glm::translate(l4_matMVP2, glm::vec3(0.1f, 0.1f, 0));
		//	glUniformMatrix4fv(aMvpLocation, 1, GL_FALSE, glm::value_ptr(l4_matMVP2));

		//}
		//else if (key == 264) {//key down
		//	unsigned int aMvpLocation = glGetUniformLocation(shaderProgram, "mvp3");
		//	l4_matMVP3 = glm::translate(l4_matMVP3, glm::vec3(0.1f, 0.1f, 0));
		//	glUniformMatrix4fv(aMvpLocation, 1, GL_FALSE, glm::value_ptr(l4_matMVP3));

		//}
		//else if (key == 265) {//key up
		//	unsigned int aMvpLocation = glGetUniformLocation(shaderProgram, "mvp0");
		//	l4_matMVP0 = glm::translate(l4_matMVP0, glm::vec3(0.1f, 0.1f, 0));
		//	glUniformMatrix4fv(aMvpLocation, 1, GL_FALSE, glm::value_ptr(l4_matMVP0));

		//}
	}
	else if (action == GLFW_RELEASE) {

	}
	std::cout << "key:" << key << std::endl;

}

int learn4() {

	int test = sizeof(Position);
	test = sizeof(VertexAtt);
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
	glfwSetKeyCallback(window, key_callback_learn4);

	//init glew
	GLenum err = glewInit();

	if (GLEW_OK != err) {
		glfwTerminate();
		return -1;
	}

	VertexAtt vertices[] = {
		//location						//selected		//obj id
		VertexAtt(Position(0.f,0.f,0.f),			0,	0),

		VertexAtt(Position(0.25f, 0.0f, 0.0f),		1,	0),
		VertexAtt(Position(0.25f, 0.25f, 0.0f),		1,	0),
		VertexAtt(Position(0.5f,  0.25f, 0.0f),		1,	0),
		VertexAtt(Position(0.5f,  0.0f, 0.0f),		1,	0),
		VertexAtt(Position(0.375f,  0.125f, 0.0f),  1,	0),

		VertexAtt(Position(-0.25f, 0.0f, 0.0f),		0,	1),
		VertexAtt(Position(-0.25f, 0.25f, 0.0f),	0,	1),
		VertexAtt(Position(-0.5f,  0.25f, 0.0f),	0,	1),
		VertexAtt(Position(-0.5f,  0.0f, 0.0f),		0,	1),
		VertexAtt(Position(-0.375f,  0.125f, 0.0f),	0,	1),


		VertexAtt(Position(-0.25f, -0.1f, 0.0f),		2,	2),
		VertexAtt(Position(-0.25f, -0.25f, 0.0f),		2,	2),
		VertexAtt(Position(-0.5f,  -0.25f, 0.0f),		2,	2),
		VertexAtt(Position(-0.5f,  -0.1f, 0.0f),		2,	2),

		VertexAtt(Position(0.25f, -0.1f, 0.0f),			2,	3),
		VertexAtt(Position(0.25f, -0.25f, 0.0f),		2,	3),
		VertexAtt(Position(0.5f,  -0.25f, 0.0f),		2,	3),
		VertexAtt(Position(0.5f,  -0.1f, 0.0f),			2,	3),

	};




	GLuint elements[] = {
	1,2,3,4,5,
	0,
	6,7,8, 9, 10,
	0,
	11, 12, 13, 14,
	0,
	15,16,17,18
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
		in float isSelected;		
		in float inObjId;		

		out vec4 oColor; 

		uniform mat4 mvp0;
		uniform mat4 mvp1;
		uniform mat4 mvp2;
		uniform mat4 mvp3;

		uniform vec4 uSelectedColor;
		uniform vec4 uNormalColor;

		void main()
		{
			if(isSelected == 0){
				oColor = uSelectedColor; // vec4(1.0f, 0.0f, 0.0f, 1.f);
			}
			else if(isSelected == 1){
				oColor = uNormalColor; // vec4(0.0f, 1.0f, 0.0f, 1.f);
			}
			else {
				oColor = vec4(0.0f, 1.0f, 0.0f, 1.f);
			}

			if(inObjId==0){
				gl_Position = mvp0 * vec4(aPos.x, aPos.y, aPos.z, 1.0);

			}
			else if(inObjId==1){
				gl_Position = mvp1 * vec4(aPos.x, aPos.y, aPos.z, 1.0);

			}
			else if(inObjId==2){
				gl_Position = mvp2 * vec4(aPos.x, aPos.y, aPos.z, 1.0);

			}
			else if(inObjId==3){
				gl_Position = mvp3 * vec4(aPos.x, aPos.y, aPos.z, 1.0);

			}

			else {
				gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);

			}
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
	glVertexAttribPointer(aPosLocation, 3, GL_FLOAT, GL_FALSE, sizeof(VertexAtt), 0);
	glEnableVertexAttribArray(aPosLocation);


	unsigned int aPosSelected = glGetAttribLocation(shaderProgram, "isSelected");
	glVertexAttribPointer(aPosSelected, 1, GL_FLOAT, GL_FALSE, sizeof(VertexAtt), (void*)sizeof(Position));
	glEnableVertexAttribArray(aPosSelected);

	unsigned int aPosObjId = glGetAttribLocation(shaderProgram, "inObjId");
	glVertexAttribPointer(aPosObjId, 1, GL_FLOAT, GL_FALSE, sizeof(VertexAtt), (void*) (sizeof(Position)+sizeof(float)));
	glEnableVertexAttribArray(aPosObjId);

	aMvpLocation[0] = glGetUniformLocation(shaderProgram, "mvp0");
	aMvpLocation[1] = glGetUniformLocation(shaderProgram, "mvp1");
	aMvpLocation[2] = glGetUniformLocation(shaderProgram, "mvp2");
	aMvpLocation[3] = glGetUniformLocation(shaderProgram, "mvp3");

	aSelectedVecColorLocation = glGetUniformLocation(shaderProgram, "uSelectedColor");
	aNormalVecColorLocation = glGetUniformLocation(shaderProgram, "uNormalColor");


	glEnable(GL_PRIMITIVE_RESTART);
	//glPrimitiveRestartIndex(0);

	int n = 0;
	while (!glfwWindowShouldClose(window))
	{

		if (n < 2) {
			glUniform4fv(aSelectedVecColorLocation, 1, glm::value_ptr(vecSelectedColor));
			glUniform4fv(aNormalVecColorLocation, 1, glm::value_ptr(vecNormalColor));

			for (int i = 0; i < 4; i++) {
				glUniformMatrix4fv(aMvpLocation[i], 1, GL_FALSE, glm::value_ptr(matMVP[i]));

			}

		}

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glDrawElements(GL_LINE_LOOP, sizeof(elements) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();

		n++;
	}


	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);
	glfwTerminate();

}

