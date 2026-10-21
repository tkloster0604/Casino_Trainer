#include "Scene.h"

void Scene::initialize_scene() {
    glfwGetWindowSize(window, &width, &height);
    prevTime = glfwGetTime();
    printf("made \n");
    fflush(stdout);
};

void Scene::draw_scene() {
    // Set the viewport
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
};