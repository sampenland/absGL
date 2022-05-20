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
        Vec3(.1f, .1f, .1f),
        Vec3(.5f, .25f, .15f),
        Vec3(0.5, 0.5, 0.5)
    );

    PointLight* pointLight = new PointLight(
        Vec3(0, 1, 0),
        Vec3(.53f, .35f, .35f),
        Vec3(.7f, .7f, .7f),
        Vec3(0.5, 0.5, 0.5),
        PointLightDistances::DISTANCE_2
    );

    SpotLight* spotLight = new SpotLight(
        Vec3(1, 1, 1),
        Vec3(-0.3, -1, 0),
        Vec3(.53f, .35f, .35f),
        Vec3(.5f, .25f, .15f),
        Vec3(0.5, 0.5, 0.5),
        SpotLightDistances::DISTANCE_7,
        22.5f,
        7.5f
    );

    const float spacing = 0.28f;

    // Create a template for a cube
    Model* cube = new Model("src/models/cubes/grass_cube.obj", defaultShader, 8);

    for (int i = -5; i < 5; i++)
    {
        for (int j = -5; j < 5; j++)
        {
            float x = i * (0.25f + spacing);
            float z = j * (0.25f + spacing);

            // Copy template into its own Model for rendering
            Model* m = new Model(*cube);
            m->SetPosition(x, 0, z);
        }
    }

    while (!renderer->ShouldClose())
    {
        
        inputHandler->ProcessInputs(window);

        renderer->StartRender();
        dirLight->UpdateShader(*defaultShader);
        pointLight->UpdateShader(*defaultShader);
        spotLight->UpdateShader(*defaultShader);
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