#include<chocolate_engine/engine.h>

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
float mouse_xpos, mouse_ypos;

enum Type { EMPTY, CIRCLE, CROSS };

class Case
{
private:
	int transShaderLoc = 0;
public:
	Type type = EMPTY;
	
	glm::vec2 Position = glm::vec2(0.0f, 0.0f);
	glm::vec2 Scale = glm::vec2(1.0f, 1.0f);

	void Draw(Texture emptyTex, Texture circleTex, Texture crossTex, Shader shader, VAO vao, GLsizeiptr indicesSize)
	{
		Renderer& renderer = Renderer::Get();


			shader.Activate();
			shader.setInt("tex0", 0);

			glActiveTexture(GL_TEXTURE0);
			if (type == CIRCLE)
			{
				circleTex.Bind();
			}
			else if (type == CROSS)
			{
				crossTex.Bind();
			}
			else
			{
				emptyTex.Bind();
			}


			renderer.objectMatrix = glm::mat4(1.0f);
			renderer.transformations = glm::mat4(1.0f);

			renderer.objectMatrix = glm::translate(renderer.objectMatrix, glm::vec3(Position, 0.0f));
			renderer.objectMatrix = glm::scale(renderer.objectMatrix, glm::vec3(Scale, 0.0f));
			renderer.transformations = renderer.projection * renderer.objectMatrix;


			transShaderLoc = glGetUniformLocation(shader.ID, "transformations");
			glUniformMatrix4fv(transShaderLoc, 1, GL_FALSE, glm::value_ptr(renderer.transformations));

			vao.Bind();
			glDrawElements(GL_TRIANGLES, indicesSize / sizeof(int), GL_UNSIGNED_INT, 0);
			vao.Unbind();
			circleTex.Unbind();
		
	}
};

int main()
{
	//CONSTANTS
	int WINDOW_WIDTH = 720;																				//Setting window size in pixels
	int WINDOW_HEIGHT = 720;

	// Engine init
	Engine& engine = Engine::Get();																		//Initializing engine
	engine.Init(WINDOW_WIDTH, WINDOW_HEIGHT, "Project0");
	glfwSetCursorPosCallback(engine.window, mouse_callback);

	// VAO
	VAO squareVAO;																						//Generating a VAO for a simple square
	squareVAO.Bind();
	VBO squareVBO(engine.squareVertices, engine.squareVerticesSize);
	EBO squareEBO(engine.squareIndices, engine.squareIndicesSize);
	squareVAO.LinkAttrib(squareVBO, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	squareVAO.LinkAttrib(squareVBO, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	//RENDERER
	Renderer& renderer = Renderer::Get();																//Instancing the renderer's singelton
	renderer.transformations = glm::mat4(1.0f);
	renderer.SetProjectionSize(3.0f, 3.0f, 10.0f);

	// SHADERS
	Shader unlitTextureShaderProgram("ressources/shaders/default.vert", "ressources/shaders/unlitTexture.frag");

	// TEXTURES
	Texture emptyTexture("ressources/textures/Transparent texture.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	emptyTexture.texUnit(unlitTextureShaderProgram, "tex0", 0);

	Texture circleTexture("ressources/textures/circle.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	circleTexture.texUnit(unlitTextureShaderProgram, "tex0", 0);

	Texture crossTexture("ressources/textures/cross.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	crossTexture.texUnit(unlitTextureShaderProgram, "tex0", 0);


	//COLORS
	glm::vec4 background_color = glm::vec4(0.02f, 0.031f, 0.063f, 1.0f);

	// GAME VARIABLES

	Case cases[9];
	glm::vec2 casesPositions[9] =
	{
		glm::vec2(-1.0f, 1.0f), glm::vec2(0.0f, 1.0f), glm::vec2(1.0f, 1.0f),
		glm::vec2(-1.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 0.0f),
		glm::vec2(-1.0f, -1.0f), glm::vec2(0.0f, -1.0f), glm::vec2(1.0f, -1.0f)
	};
	for (int i = 0; i < 9; i++) cases[i].Position = casesPositions[i];

	Type whosTurn = CIRCLE;

	glm::vec2 mousePos;
	int nearestCase = 0;


	//MAIN LOOP
	while (!glfwWindowShouldClose(engine.window))
	{
		// START LOOP
		engine.TimeTick();
		Renderer::ClearScreen(background_color);

		//FPS
		std::string FPS = std::to_string((1.0 / engine.deltaTime));
		std::string ms = std::to_string(engine.deltaTime * 1000);
		std::string newTitle = "Test - " + FPS + " FPS / " + ms + " ms.";
		glfwSetWindowTitle(engine.window, newTitle.c_str());

		// GAME LOGIC
		// Inputs
		mousePos = glm::vec2((mouse_xpos / WINDOW_WIDTH * 2 - 1) * (renderer.proj_width / 2), - (mouse_ypos / WINDOW_HEIGHT * 2 - 1) * (renderer.proj_height / 2));

		//Stuff

		float smallest = INFINITY;
		for (int i = 0; i < 9; i++)
		{
			glm::vec2 pos = cases[i].Position;

			float dist = abs(glm::length2(mousePos - pos));
			if (dist < smallest)
			{
				smallest = dist;

				nearestCase = i;
			}
		}

		for (int i = 0; i < 9; i++)
		{
			cases[i].type = EMPTY;
		}

		cases[nearestCase].type = whosTurn;

		//RENDER
		for (int i = 0; i < 9; i++)
		{
			cases[i].Draw(emptyTexture, circleTexture, crossTexture, unlitTextureShaderProgram, squareVAO, engine.squareIndicesSize);
		}

		// END LOOP
		glfwSwapBuffers(engine.window);
		glfwPollEvents();
	}

	//END
	ObjectsManager::DeleteAllObjects();

	glfwDestroyWindow(engine.window);
	glfwTerminate();
	return 0;
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	mouse_xpos = static_cast<float>(xposIn);
	mouse_ypos = static_cast<float>(yposIn);
}