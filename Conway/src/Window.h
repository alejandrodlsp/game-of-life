#pragma once

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct WindowProps
{
	int width;
	int height;
	const char* name;
};

class Window
{
public:
	Window(){}
	~Window()
	{
		Shutdown();
	}

	void Init(WindowProps props)
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		mWindowProps.width = props.width;
		mWindowProps.height = props.height;
		mWindowProps.name = props.name;

		mNativeWindow = glfwCreateWindow(props.width, props.height, props.name, NULL, NULL);
		if (mNativeWindow == NULL)
		{
			std::cout << "ERROR: Could not create GLFW window" << std::endl;
			Shutdown();
			return;
		}

		glfwMakeContextCurrent(mNativeWindow);
		bool gladResult = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		if (!gladResult)
		{
			std::cout << "ERROR: Could not initialize glad context" << std::endl;
			Shutdown();
			return;
		}

		glViewport(0, 0, props.width, props.height);
		glfwSetWindowUserPointer(mNativeWindow, &mWindowProps);

		glfwSetFramebufferSizeCallback(mNativeWindow, [](GLFWwindow* window, int width, int height)
			{
				WindowProps* wd = static_cast<WindowProps*>(glfwGetWindowUserPointer(window));
				wd->width = width;
				wd->height = height;
				glViewport(0, 0, width, height);
			});
	}

	void Shutdown()
	{
		glfwTerminate();
	}

	void Update()
	{
		glfwSwapBuffers(mNativeWindow);
	}

	bool ShouldClose()
	{
		glfwPollEvents();
		return glfwWindowShouldClose(mNativeWindow);
	}

	GLFWwindow* GetNative() { return mNativeWindow; }

private:
	WindowProps mWindowProps;
	GLFWwindow* mNativeWindow;
};