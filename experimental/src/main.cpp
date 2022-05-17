#include <AbsGL.h>

int main(int argc, char** argv)
{
	using namespace absGL;

    Renderer* renderer = new Renderer("Experimental", 800, 600);
    InputHandler* inputHandler = new InputHandler();
    GLFWwindow* window = renderer->GetWindow();

    while (!renderer->ShouldClose())
    {
        
        inputHandler->ProcessInputs(window);

        renderer->StartRender();
        renderer->Render();
        renderer->EndRender();
    }

    delete renderer;

	return 0;
}