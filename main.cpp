#include "main.h"


static void error_callback(int error, const char* msg)
{
    fputs(msg, stderr);
}

Scene scene;

int main () {
    glfwSetErrorCallback(error_callback);

    if (!glfwInit()) exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_ALPHA_BITS, 0);

    scene.window = glfwCreateWindow(750,750, "Casino Trainer", NULL, NULL);
    if (!scene.window)  { glfwTerminate();  exit(-1); }
    
    glfwMakeContextCurrent(scene.window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { glfwTerminate(); exit(EXIT_FAILURE); }

    glfwSwapInterval(1);
    scene.initialize_scene();

    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
    printf("GLSL Version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    printf("Rendered by: %s\n", glGetString(GL_RENDERER));
    printf("\n");

    int major, minor, rev;
    glfwGetVersion(&major, &minor, &rev);
    printf("GLFW  Version: %d.%d.%d\n" ,  major, minor, rev);
    
    // Enter the event loop.
    while (!glfwWindowShouldClose(scene.window)) {
        glfwPollEvents();

        scene.draw_scene();
        glfwSwapBuffers(scene.window); 
    }

    glfwTerminate();
    return 0;
}