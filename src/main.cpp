#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "stb_image.h"
#include <iostream>
#include <vector>
#include <color.hpp>

#include "Shader.h"
#include "Texture.h"

#define log(x) std::cout << x << std::endl;

// GLM:
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


// settings
int SCREEN_WIDTH = 1000;
int SCREEN_HEIGHT = 850;
glm::vec3 pos = glm::vec3(0.0f, 0.0f, -3.0f);
glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);


// methods
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);


int main()
{

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "LearnOpenGL", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to init GLAD" << std::endl;
		return -1;
	}

	std::cout <<
		dye::aqua("OpenGL, nikeedev project;\n") <<
		"GLFW version: " <<
		dye::yellow(glfwGetVersionString()) <<
		"\nOpenGL Version: " <<
		dye::red(glGetString(GL_VERSION)) <<
		"\nVendor: " <<
		dye::bright_white(glGetString(GL_VENDOR)) <<
		"\nGPU (OpenGL Renderer): " <<
		dye::purple(glGetString(GL_RENDERER)) <<
		"\nGLSL Version: " <<
		dye::blue(glGetString(GL_SHADING_LANGUAGE_VERSION)) << "\n" << std::endl;

	// load icon

	GLFWimage images[1] = {};
	images[0].pixels = stbi_load("other/nikee.png", &images[0].width, &images[0].height, 0, 4); //rgba channels 
	glfwSetWindowIcon(window, 1, images);
	stbi_image_free(images[0].pixels);

	// Vertex


	Shader ourShader("other/shader.vert", "other/shader.frag"); // you can name your shader files however you like


	// setting up vertex data
	// 
	//float vertices[] = {
	//	 0.5f, -0.5f, 0.0f,	  /*  1.0f, 0.0f, 0.0f, */ // bottom-right
	//   -0.5f, -0.5f, 0.0f,  /*  0.0f, 1.0f, 0.0f, */ // bottom-left
	//	 0.0f,  0.5f, 0.0f,   /*  0.0f, 0.0f, 1.0f  */ // top
	//};


	float vertices[] = {
		// positions          // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	/* triangle stuff */

	unsigned int VAO, VBO, EBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute: 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// texture attribute:
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	///////////////
	// 
	// textures
	//
	std::vector<Texture> textures = { Texture("other/container.jpg", GL_RGB, GL_RGB), Texture("other/awesomeface.png", GL_RGB, GL_RGBA) };

	ourShader.use();
	ourShader.setInt("texture1", 0);
	ourShader.setInt("texture2", 1);

	//
	//
	//
	//////////////

	// cube positions	
	std::vector<glm::vec3> cubePositions = {
		glm::vec3(0.0f,  0.0f,  3.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.6f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f),
		glm::vec3(-1.3f,  5.0f, -1.5f),
	};

	float rotation_speed = 0.3f;

	std::cout << "Number of \"stuff\" in the array: " << cubePositions.size() << std::endl;

	// loop
	while (!glfwWindowShouldClose(window))
	{
		glfwGetWindowSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

		// Input stuff here:
		processInput(window);

		// Rendering stuff here:
		glClearColor(0.39f, 0.58f, 0.92f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		/*glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1.ID);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2.ID);*/

		for (int i = 0; i < textures.size(); i++) {
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, textures[i].ID);
		}

		// render container
		ourShader.use();


		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		auto pitch_rot = glm::angleAxis(rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
		auto yaw_rot = glm::angleAxis(rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));

		glm::quat rotate = glm::normalize(yaw_rot * pitch_rot);

		// note that we're translating the scene in the reverse direction of where we want to move
		view = glm::translate(view, pos);
		projection = glm::perspective(glm::radians(90.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.01f, 100.0f);

		ourShader.setMat4("view", view);
		ourShader.setMat4("projection", projection);
		ourShader.setMat42QuatCast("rotate", rotate);


		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBindVertexArray(VAO);

		for (int i = 0; i < cubePositions.size() - 1; i++) {
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			//if (i % 3 == 0)  // every 3rd iteration (including the first) we set the angle using GLFW's time function.
			angle = (float)glfwGetTime() * 55.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			ourShader.setMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		// Update stuff here:
		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	float speed = 0.01f,
		rotate_speed = 0.005f;

	// Key controls pos
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		pos.y += speed;
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		pos.y -= speed;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		pos.x += speed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		pos.x -= speed;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		pos.z += speed;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		pos.z -= speed;

	std::printf("\nX:%i, Y:%i, Z:%i", pos.x / 100000, pos.y / 100000, pos.z / 100000);

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		rotation.y += rotate_speed;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		rotation.y -= rotate_speed;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		rotation.x += rotate_speed;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		rotation.x -= rotate_speed;

}

