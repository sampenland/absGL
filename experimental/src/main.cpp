#include <AbsGL.h>

int main(int argc, char** argv)
{
	using namespace absGL;

    Renderer* renderer = new Renderer("Experimental", 800, 600);
    renderer->SetCameraPosition(0, 1, 4);

    renderer->HideMouse(true);
    InputHandler* inputHandler = new InputHandler();
    GLFWwindow* window = renderer->GetWindow();
    Shader* defaultShader = new Shader("src/shaders/vert/v_default.glsl", "src/shaders/frag/f_default.glsl");
    
    DirectionalLight* dirLight = new DirectionalLight(
        Vec3(-0.2f, -1.0f, -0.3f),
        Vec3(.2f, .2f, .2f),
        Vec3(.5f, .25f, .15f),
        Vec3(0.5, 0.5, 0.5)
    );

    for (int i = -2; i < 2; i++)
    {
        for (int j = -2; j < 2; j++)
        {
            float x = i * 0.25f;
            float z = j * 0.25f;

            Model* m = new Model("src/models/cubes/grass_cube.obj", defaultShader);
            m->SetPosition(x, 0, z);
        }
    }

    while (!renderer->ShouldClose())
    {
        
        inputHandler->ProcessInputs(window);

        renderer->StartRender();
        dirLight->UpdateShader(*defaultShader);
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