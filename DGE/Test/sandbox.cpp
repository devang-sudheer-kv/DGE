#include "sandbox.h"

SandboxLayer::SandboxLayer() : triangleVBO(0), triangleEBO(0), vao(0), wallTexture(0), buffer(0)
{
	setName("Sandbox");
}

void SandboxLayer::onAttach()
{
    MSG("Attached");

    float vertices[] = {
        0.5f, 0.5f, 0.0f, 1.0f, 1.0f, // top right 
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f, 0.0, 1.0f, // top left
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f // bottom right
    };
    unsigned int indices[] = {
        0, 1, 2,
        0, 3, 1
    };
    {
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(1, &triangleVBO);
        glGenBuffers(1, &triangleEBO);

        glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangleEBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int w, h, nrChannels;
    unsigned char* data = stbi_load("res/wall.jpg", &w, &h, &nrChannels, 0);
    glGenTextures(1, &wallTexture);
    glBindTexture(GL_TEXTURE_2D, wallTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    std::string vert_source_str = readFile("shader/triangle.vert");
    std::string frag_source_str = readFile("shader/triangle.frag");
    const char* vert_source = vert_source_str.c_str();
    const char* frag_source = frag_source_str.c_str();
    shaderProgram.compile(vert_source, frag_source);
    shaderProgram.use();

    //MSG_DBG(vert_source);
    //MSG_DBG(frag_source);
}

void SandboxLayer::onDetach()
{
	MSG("Detached");
}

void SandboxLayer::onUpdate()
{
    shaderProgram.use();

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}