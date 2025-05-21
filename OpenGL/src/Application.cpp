//#include <GL/GL.h>
#include <gl/glew.h>
#include <glfw3.h>
#include <iostream>
#include <string>
#include <sstream>
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"




int main(void) {
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);


    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        std::cout << "Error" << std::endl;


    std::cout << glGetString(GL_VERSION) << std::endl;


    float positions[] = {
        -0.5f,-0.5f,
        0.5f,-0.5f,
        0.5f,0.5f,
        -0.5f,0.5f,
    };

    unsigned int indices[] = {
        0,1,2,
        2,3,0
    };
    {
        unsigned int vao;
        GLCall(glGenVertexArrays(1, &vao));
        GLCall(glBindVertexArray(vao));

        VertexArray va;
        VertexBuffer vb(positions, 4 * 2 * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(2);
		va.addBuffer(vb, layout);
        unsigned int buffer;
        GLCall(glEnableVertexAttribArray(0));
        GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0));

        IndexBuffer ib(indices, 6);

        unsigned int ibo;//index buffer object
        GLCall(glGenBuffers(1, &ibo));
        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
        GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW));

		Shader shader("res/shaders/basic.shader");
		shader.Bind();
        shader.SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);//.8f .3f .8f 1f
        va.Unbind();
        shader.Unbind();
        vb.UnBind();
		ib.UnBind();

        /* Loop until the user closes the window */
        float r = .0f;
        float increment = .5f;
        while (!glfwWindowShouldClose(window)) {
            /* Render here */
            GLCall(glClear(GL_COLOR_BUFFER_BIT));
            shader.Bind();
			shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);//.8f .3f .8f 1f
            GLCall(glBindVertexArray(vao));
            va.Bind();
            ib.Bind();
            GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
            if (r > 1.0f) increment = -0.05f;
            else if (r < .0f) increment = 0.05f;

            r += increment;


            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }


    }
    glfwTerminate();
    return 0;
}