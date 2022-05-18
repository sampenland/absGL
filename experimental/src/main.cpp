#include <AbsGL.h>

int main(int argc, char** argv)
{
	using namespace absGL;

    Renderer* renderer = new Renderer("Experimental", 800, 600);
    renderer->HideMouse(true);
    InputHandler* inputHandler = new InputHandler();
    GLFWwindow* window = renderer->GetWindow();
    Shader* defaultShader = new Shader("src/shaders/vert/v_default.glsl", "src/shaders/frag/f_default.glsl");
    
    Model m("src/models/cube.obj", defaultShader);

    while (!renderer->ShouldClose())
    {
        
        inputHandler->ProcessInputs(window);

        renderer->StartRender();
        renderer->Render();
        renderer->EndRender();
    }

    if(renderer)
        delete renderer;

    if (inputHandler)
        delete inputHandler;

    if (defaultShader)
        delete defaultShader;

	return 0;
}