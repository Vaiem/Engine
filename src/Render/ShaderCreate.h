#pragma once
#include <glad/glad.h>
#include <string>
#include <glm-master/glm/mat4x4.hpp>

namespace Render {
	class ShaderCreate
	{
	public:
		ShaderCreate(const std::string& VertexShader, const std::string& FragmentShader);
		~ShaderCreate();
		bool ShaderCompile(const std::string& shader, GLenum Typeshader, GLuint& idShader);
		void ShaderDelet(GLuint idVertexSahder, GLuint idFragmentShader);
		GLuint CreateVertexBufferObject(GLfloat arrayData[], GLsizeiptr size);
		GLuint CreateVertexArrayObject(GLuint vbo, GLuint cbo);
		GLuint GetProgramId() const { return programShaderID; }
		void SetInit(const std::string& name, GLint idSlot);
		void SetMatrix4(const std::string& Name, const glm::mat4& Matrix);
		void UseProgram();
		bool is_Sucsess = false;
	private:
		GLuint programShaderID = 0;
		
		
	};
	
}


