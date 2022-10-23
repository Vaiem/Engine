#include"ShaderCreate.h"
#include <iostream>
#include <string>
#include <glm-master/glm/gtc/type_ptr.hpp>

namespace Render {
	ShaderCreate::ShaderCreate(const std::string& VertexShader,const std::string& FragmentShader) {
		GLuint VertexShaderid;
		if (!ShaderCompile(VertexShader, GL_VERTEX_SHADER, VertexShaderid))
		{
			std::cerr << "ERR::SHADER::SHADERCREATEVERTEX\n";
			return;
		}

		GLuint FragmentShaderid;
		if (!ShaderCompile(FragmentShader, GL_FRAGMENT_SHADER, FragmentShaderid))
		{
			std::cerr << "ERR::SHADER::SHADERCREATEFRAGMENT\n";
			glDeleteShader(VertexShaderid);
			return;
		}

		GLuint programShader = glCreateProgram();
		glAttachShader(programShader, VertexShaderid);
		glAttachShader(programShader, FragmentShaderid);
		glLinkProgram(programShader);

		GLint sucsses;
		glGetProgramiv(programShader,GL_LINK_STATUS, &sucsses);
		if (!sucsses)
		{
			std::cerr << "ERR::PROGRMASHADER\n";
			is_Sucsess = false;
			
		}
		else
		{
			is_Sucsess = true;
		}
		ShaderDelet(VertexShaderid, FragmentShaderid);
		programShaderID = programShader;
		

	}
	
	bool ShaderCreate::ShaderCompile(const std::string& shader, GLenum TypeShader, GLuint& idShader) {
		idShader = glCreateShader(TypeShader);
		const char* shaderC = shader.c_str();
		
		glShaderSource(idShader, 1, &shaderC, nullptr);
		glCompileShader(idShader);
		
		GLint sucsses;
		glGetShaderiv(idShader, TypeShader, &sucsses);
		if (!sucsses)
		{
			
			std::cerr << "ERR::SHADER::SHADERCOMPILE\n";
			return false;
		}
		return true;
	}

	GLuint ShaderCreate::CreateVertexBufferObject(GLfloat arrayData[],GLsizeiptr size) {
		GLuint idvbo = 0;
		glGenBuffers(1, &idvbo);
		glBindBuffer(GL_ARRAY_BUFFER, idvbo);
		glBufferData(GL_ARRAY_BUFFER, size, arrayData, GL_STATIC_DRAW);
		return idvbo;
	}

	 

	GLuint ShaderCreate::CreateVertexArrayObject(GLuint vbo, GLuint cbo) {
		GLuint vao = 0;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, cbo);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
		return vao;
	}

	void ShaderCreate::ShaderDelet(GLuint idShaderVertex, GLuint idShaderFragment) {
		glDeleteShader(idShaderVertex);
		glDeleteShader(idShaderFragment);
	}

	void ShaderCreate::UseProgram() {
		if (programShaderID)
		{
			glUseProgram(programShaderID);

		}
		
	}

	void ShaderCreate::SetInit(const std::string& name, GLint idSlot)
	{
		glUniform1i(glGetUniformLocation(programShaderID, name.c_str()), idSlot);
	}


	void ShaderCreate::SetMatrix4(const std::string& Name, const glm::mat4& Matrix)
	{
		glUniformMatrix4fv(glGetUniformLocation(programShaderID, Name.c_str()), 1, GL_FALSE, glm::value_ptr(Matrix));
	}


	ShaderCreate::~ShaderCreate() {
		glDeleteProgram(programShaderID);
	}
}