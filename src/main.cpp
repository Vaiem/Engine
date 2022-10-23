#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <glm-master/glm/vec2.hpp>
#include <glm-master/glm/mat4x4.hpp>
#include <glm-master/glm/gtc/matrix_transform.hpp>
#include "Render/ShaderCreate.h"
#include "ResourseManager/ResourseManager.h"
#include "Render/TextureCreate.h"

/*GLfloat Point[] = {
    0.0f, 0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    -0.5f,-0.5f, 0.0f
};*/

GLfloat Point[] = {
    0.0f, 50.f, 0.0f,
    50.f, -50.f, 0.0f,
    -50.f,-50.f, 0.0f
};

GLfloat Colors[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f
};

GLfloat Texture[] = {
     0.5f, 1.0f,  
     1.0f, 0.0f,  
     0.0f, 0.0f
};



int width_X = 800;
int height_Y = 600;

void WindowReSizeCallback(GLFWwindow* pWindow, int width, int height) {
    width_X = width;
    height_Y = height;
    glViewport(0, 0, width, height);
}

int main(int argc, char** argv)
{
    
   
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* pWindow = glfwCreateWindow(width_X, height_Y, "MyEngine", NULL, NULL);
    if (!pWindow)
    {
        glfwTerminate();
        return -1;
    }

    glfwSetWindowSizeCallback(pWindow, WindowReSizeCallback);

    /* Make the window's context current */
    glfwMakeContextCurrent(pWindow);

    if (!gladLoadGL())
    {
        std::cout << "Error Gl";
        return -1;
    }
    std::cout << "Rendereer " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "Version openGl" << GLVersion.major << GLVersion.minor << std::endl;

    glClearColor(1,1,0,1);

  

    {
        ResourseManager resourseManage(argv[0]);
        auto pShaderProgram = resourseManage.shaderLoad("Default", "res/shaders/vertex.txt", "res/shaders/fragment.txt");
        if (pShaderProgram == nullptr)
        {
            std::cout << "ResourseManager::main.cpp" << std::endl;
            return 0;
        }
        //"C:\Engine\Engine\build\bin\Debug\res/Texture/map_16x16.png"
        auto pTexture = resourseManage.TextureLoad("defTextur", "res/Texture/map_16x16.png");
        if (pTexture == nullptr)
        {
            std::cout << "ResourseManager::main.cpp::TEXTUR" << std::endl;
            return 0;
        }

        //

        GLuint vbo = 0;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Point), Point, GL_STATIC_DRAW);

        GLuint cbo = 0;
        glGenBuffers(1, &cbo);
        glBindBuffer(GL_ARRAY_BUFFER, cbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);

        GLuint tbo = 0;
        glGenBuffers(1, &tbo);
        glBindBuffer(GL_ARRAY_BUFFER, tbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Texture), Texture, GL_STATIC_DRAW);

        GLuint vao = 0;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, cbo);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);


        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, tbo);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

        
        glBindTexture(GL_TEXTURE_2D, (*pTexture).GetUseTexture());
        pShaderProgram->SetInit("ourTexture", 0);

       
        GLfloat NextPosition = 100.f;

        glm::mat4 ModMatrix_1 = glm::mat4(1.f);
        ModMatrix_1 = glm::translate(ModMatrix_1, glm::vec3(100.f, 200.f, 0.f));
        
        glm::mat4 ModMatrix_2 = glm::mat4(1.f);
        ModMatrix_2 = glm::translate(ModMatrix_2, glm::vec3(590.f, 200.f, 0.f));

        glm::mat4 progectMatrix = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, -100.0f, 100.0f);
      
         pShaderProgram->UseProgram();
        (*pShaderProgram).SetMatrix4("projectionMat", progectMatrix);
        
        while (!glfwWindowShouldClose(pWindow))
        {
           
            glClear(GL_COLOR_BUFFER_BIT);

            pShaderProgram->UseProgram();         
            
            glBindVertexArray(vao);

            (*pShaderProgram).SetMatrix4("modelMat", ModMatrix_1);
            glDrawArrays(GL_TRIANGLES, 0, 3);
            
            
            (*pShaderProgram).SetMatrix4("modelMat", ModMatrix_2);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            glfwSwapBuffers(pWindow);

            
            glfwPollEvents();
        }
    }
   
    glfwTerminate();
    return 0;
}