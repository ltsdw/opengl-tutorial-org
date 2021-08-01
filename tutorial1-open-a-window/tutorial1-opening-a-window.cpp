// include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// include GLEW. Always include it before gl.h and glfw3.h, since it's a bit magic.
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>


int main(int argc, char* args[])
{
    // initialize glfw
    glewExperimental = true; // nedeed for core profile

    if (!glfwInit())
    {
        fprintf(stderr, "failed to initialize glfw\n");

        return EXIT_FAILURE;
    }

    // profiling to the window
    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialising
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // opengl 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // we don't want old opengl

    // open a window and create its OpenGL contex
    GLFWwindow* window;
    window = glfwCreateWindow(800, 600, "Tutorial 01", NULL, NULL);

    if (!window)
    {
        fprintf(stderr, "failed to open glfw window."
                        "If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");

        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window); // initialize glew
    glewExperimental = true; // needed in core profile

    if (glewInit() != GLEW_OK)
    {
        fprintf(stderr, "failed to initialize glew.\n");
        return EXIT_FAILURE;
    }

    // ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    do
    {
        // clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so it's there nonetheless.
        glClear(GL_COLOR_BUFFER_BIT);

        // draw nothing, see you in tutorial 2 !

        // swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

        sleep(1);

    } // check if the ESC key was pressed or the window was closed
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(window));

    return EXIT_SUCCESS;
}
