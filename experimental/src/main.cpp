#include <AbsGL.h>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>

void processInput(GLFWwindow* window);

int main(int argc, char** argv)
{
	using namespace absGL;

    Renderer* renderer = new Renderer();
    GLFWwindow* window = renderer->GetWindow();

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        renderer->StartRender();
        renderer->Render();
        renderer->EndRender();

        glfwPollEvents();
    }

    glfwTerminate();

	return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}