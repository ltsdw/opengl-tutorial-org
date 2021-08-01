// include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// include GLEW. Always include it before gl.h and glfw3.h, since it's a bit magic.
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>


// my includes
#include "../common/shader.hpp"
#include "../util/util.hpp"


void initializeVertexArray(GLuint* vertex_array_id)
{
    glGenVertexArrays(1, vertex_array_id);
    glBindVertexArray(*vertex_array_id);
}

void initializeVertexBuffer(size_t buffer_size, const GLfloat g_vertex_buffer_data[], GLuint* vertex_buffer)
{
    // generate 1 buffer, put the resulting identifier in vertex_buffer
    glGenBuffers(1, vertex_buffer);

    // the following commands will talk about our 'vertex_buffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, *vertex_buffer);

    // give our vertices to opengl
    glBufferData(GL_ARRAY_BUFFER, buffer_size, g_vertex_buffer_data, GL_STATIC_DRAW);
}

int main(int argc, char* argv[])
{
    char abs_path[200];

    absBinPath(abs_path, argv[0]);

    string str_abs_path(abs_path);

    string file1 = str_abs_path + "src" + "/" + "shaders" + "/" + "simplevertexshader.glsl";
    string file2 = str_abs_path + "src" + "/" + "shaders" + "/" + "simpleshader-fragmentshader.glsl";

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

    // create a Vertex Array Object and set it as the current one
    GLuint vertex_array_id;
    initializeVertexArray(&vertex_array_id);

    // an array of 3 vectors which represents 3 vertices
    static const GLfloat g_vertex_buffer_data[] = {
                                                    -1.0f, -1.0f, 0.0f,
                                                     1.0f, -1.0f, 0.0f,
                                                     0.0f,  1.0f, 0.0f
                                                  };

    GLuint vertex_buffer;
    initializeVertexBuffer(sizeof(g_vertex_buffer_data), g_vertex_buffer_data, &vertex_buffer);

    // create and compile our GLSL program from the shaders
    GLuint program_id = loadShaders(file1, file2);

    // ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    do
    {
        // clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so it's there nonetheless.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // 1st attribute buffer : vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
        glVertexAttribPointer(
                0,          // attribute 0. No particular reason for 0, but must match the layout in the shader.
                3,          // size
                GL_FLOAT,   // type
                GL_FALSE,   // normalized?
                0,          // stride
                (void*)0    // array buffer offset
        );

        // use shader
        glUseProgram(program_id);

        // draw the triangle
        glDrawArrays(GL_TRIANGLES, 0, 3); // starting from vertex 0; 3 vertices total -> 1 triangle
        glDisableVertexAttribArray(0);

        // swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

        //sleep(1);

    } // check if the ESC key was pressed or the window was closed
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(window));

    return EXIT_SUCCESS;
}
