#include <iostream>

#include "Window.h"
#include "RenderQuad.h"
#include "Cell.h"

#define FRAME_RATE 100
bool simulating = false;

Window* window;
RenderQuad* quad;

float lastFrame = 0.0;
float deltaTime = 0.0;
float frameElapsed = FRAME_RATE;

void UpdateInput();

void Render();

int main()
{
	window = new Window();
	window->Init({ WINDOW_SIZE, WINDOW_SIZE, "Cellular automata" });

	Cell_Initialize();
	quad = new RenderQuad();

	quad->GetShader()->Bind();
	quad->GetShader()->SetUniformF("uBorderWidth", 0.002);
	quad->GetShader()->SetUniformI("uTableWidth", CELL_COUNT_X);
	quad->GetShader()->SetUniformI("uTableHeight", CELL_COUNT_Y);

	bool shouldClose = false;
	while (!shouldClose)
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		frameElapsed += deltaTime;

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		UpdateInput();

		if (frameElapsed * 1000 > FRAME_RATE)
		{
			frameElapsed = 0;
			if(simulating)
				Cell_Update();
			Render();
		}

		shouldClose = window->ShouldClose();
	}

	window->Shutdown();
}

void Render()
{
	Cell_GenerateCellTexture(GL_TEXTURE0);
	quad->Render(GL_TEXTURE0);
	window->Update();
}

void Paint(bool state)
{
	double xpos, ypos;
	glfwGetCursorPos(window->GetNative(), &xpos, &ypos);
	xpos /= WINDOW_SIZE;	// Normalize
	ypos /= WINDOW_SIZE;
	xpos = (xpos < 0) ? 0.0 : xpos; // Clamp
	ypos = (ypos < 0) ? 0.0 : ypos;
	int xcell = floor(xpos * CELL_COUNT_X);
	int ycell = floor(ypos * CELL_COUNT_Y);

	CellGrid[xcell][CELL_COUNT_Y - (ycell + 1)] = state;
	
	Render();
}

void UpdateInput()
{
	if (glfwGetMouseButton(window->GetNative(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		Paint(true);	
	if (glfwGetMouseButton(window->GetNative(), GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
		Paint(false);
	if (glfwGetKey(window->GetNative(), GLFW_KEY_1) == GLFW_PRESS)
		simulating = true;
	if (glfwGetKey(window->GetNative(), GLFW_KEY_2) == GLFW_PRESS)
		simulating = false;
}