#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <vector>

namespace l5 {

//glm::mat4x4 matMVP[] = { glm::mat4x4(1.0f) , glm::mat4x4(1.0f) , glm::mat4x4(1.0f) , glm::mat4x4(1.0f) };
//unsigned int aMvpLocation[4];

unsigned int aSelectedVecColorLocation;
unsigned int aNormalVecColorLocation;
unsigned int selectedId;


glm::vec4 vecSelectedColor = glm::vec4(1.f, 0.f, 0.f, 1.f);
glm::vec4 vecNormalColor = glm::vec4(0.f, 0.f, 1.f, 1.f);

GLuint shaderProgram;
GLuint VAO;
GLuint VBO;
GLuint EBO;


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
	int nObjectId = 0;

	VertexAtt() {};
	VertexAtt(const Position& pos, const float& selected, const int& objId = 0) {
		posData = pos;
		fSelected = selected;
		nObjectId = objId;
	}
};


VertexAtt vertices[] = {
	//location						//selected		//obj id
	VertexAtt(Position(0.f,0.f,0.f),			0,	-1),

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


struct Object {
	VertexAtt* pPointer;
	int nNumOfVertex;
public:
	Object(VertexAtt* p = NULL, const int &n = 0) {
		pPointer = p;
		nNumOfVertex = n;
	}
};

std::vector<Object> g_vecObj;


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void key_callback_learn(GLFWwindow* window, int key, int scancode, int action, int mode) {


	Object obj;
	if (action == GLFW_PRESS) {
		if (key >= 320 && key <= 323) {
			selectedId = key - 320;
			if (selectedId <= g_vecObj.size()) {
			}
			else {
				return;
			}
		}
		obj = g_vecObj[selectedId];
		//std::cout << "selectedId :" << selectedId << std::endl;
		if (key == 32) {
			glm::vec4 tmp = vecSelectedColor;
			vecSelectedColor = vecNormalColor;
			vecNormalColor = tmp;
			glUniform4fv(aSelectedVecColorLocation, 1, glm::value_ptr(vecSelectedColor));
			glUniform4fv(aNormalVecColorLocation, 1, glm::value_ptr(vecNormalColor));

		}

		if (key >= 262 && key <= 265) {
			glm::vec2 trans;
			switch (key)
			{
			case 262://key right				
				trans = glm::vec2(0.1f, 0.0f);
				break;
			case 263://key lef
				trans = glm::vec2(-0.1f, 0.0f);
				break;
			case 264://key down
				trans = glm::vec2(0.0f, -0.1f);
				break;
			case 265://key up
				trans = glm::vec2(0.0f, 0.1f);
				break;
			default:
				break;
			}
			for (int i = 0; i < obj.nNumOfVertex; i++) {
				obj.pPointer[i].posData.fX += trans.x;
				obj.pPointer[i].posData.fY += trans.y;
			}
			int ofset = obj.pPointer - vertices;
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferSubData(GL_ARRAY_BUFFER, ofset * sizeof(VertexAtt), obj.nNumOfVertex * sizeof(VertexAtt), obj.pPointer);



		}
	}
}

int main() {

	int test = sizeof(Position);
	test = sizeof(VertexAtt);

	g_vecObj.push_back(Object(&vertices[1], 5));
	g_vecObj.push_back(Object(&vertices[6], 5));
	g_vecObj.push_back(Object(&vertices[11], 4));
	g_vecObj.push_back(Object(&vertices[15], 4));

	int ofset = &vertices[1] - vertices;
	ofset = &vertices[6] - vertices;
	ofset = &vertices[11] - vertices;
	ofset = &vertices[15] - vertices;


	GLFWwindow* window = 0;
	if (GLFW_FALSE == glfwInit()) {
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	int nWidth = 600, nHeight = 600;
	window = glfwCreateWindow(nWidth, nHeight, "Test OpenGL", NULL /* glfwGetPrimaryMonitor()*/, NULL);

	if (!window) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback_learn);

	glewExperimental = GL_TRUE;

	//init glew
	GLenum err = glewInit();

	if (GLEW_OK != err) {
		glfwTerminate();
		return -1;
	}

	//vertex array
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//vertex buffer objects
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	//Element Buffer Object
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(elements), elements);


	char const* VertexShaderSource = R"GLSL(
		#version 330 core
		in vec3 aPos;
		in float isSelected;
		out vec4 oColor; 

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
		#version 330 core
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

	glBindVertexArray(0);


	aSelectedVecColorLocation = glGetUniformLocation(shaderProgram, "uSelectedColor");
	aNormalVecColorLocation = glGetUniformLocation(shaderProgram, "uNormalColor");

	glUseProgram(shaderProgram);
	glEnable(GL_PRIMITIVE_RESTART);
	//glPrimitiveRestartIndex(0);

	glUniform4fv(aSelectedVecColorLocation, 1, glm::value_ptr(vecSelectedColor));
	glUniform4fv(aNormalVecColorLocation, 1, glm::value_ptr(vecNormalColor));

	glBindVertexArray(VAO);



	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawElements(GL_LINE_LOOP, sizeof(elements) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);
	glfwTerminate();
	return 0;
}


}

