#include <AbsGL.h>

int main(int argc, char** argv)
{
	using namespace absGL;

    Renderer* renderer = new Renderer("Experimental", 800, 600);
    InputHandler* inputHandler = new InputHandler();
    GLFWwindow* window = renderer->GetWindow();
    Shader* defaultShader = new Shader("src/shaders/vert/v_default.glsl", "src/shaders/frag/f_default.glsl");

    float vertices[] = {
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
    };

    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    Model m(vertices, indices);

    while (!renderer->ShouldClose())
    {
        
        inputHandler->ProcessInputs(window);

        renderer->StartRender();
        renderer->Render();
        m.Render(defaultShader);
        renderer->EndRender();
    }

    if(renderer)
        delete renderer;

    if (inputHandler)
        delete inputHandler;

	return 0;
}