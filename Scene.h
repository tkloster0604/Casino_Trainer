#pragma once
#include "main.h"

class Scene {
    public:
        GLFWwindow* window;

        int width, height;
        double prevTime;

        void initialize_scene();
        void draw_scene();
};