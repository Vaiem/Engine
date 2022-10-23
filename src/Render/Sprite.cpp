#include "Sprite.h"

#include "ShaderCreate.h"
#include "glm-master/glm/mat4x4.hpp"
#include "glm-master/glm/vec3.hpp"
namespace Render {

	Sprite::Sprite(const std::shared_ptr<TextureCreate> texture2D,
		const std::shared_ptr<ShaderCreate> ShaderProg,
		const glm::vec2& position,
		const glm::vec2& Size,
		const float rotation)
		: m_pTexture(texture2D),
		  m_pShader(ShaderProg),
		  m_rotation(rotation),
		  m_position(position),
		  m_Size(Size)
		  
	{
		const GLfloat VertexCoords[] = {
		0.0f, 0.0f, 
		0.0f, 1.0f, 
		1.0f,1.0f,

		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f,0.0f,
		};

		const GLfloat TextureCoords[] = {
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f,1.0f,

		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f,0.0f,
		};
	
		//refactor
		
		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		glGenBuffers(1, &m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(VertexCoords), VertexCoords, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);		
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	

		glGenBuffers(1, &m_TBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_TBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(TextureCoords), TextureCoords, GL_STATIC_DRAW);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}


	void Sprite::Render() const
	{
		m_pShader->UseProgram();

	}

	void Sprite::setPosition(const glm::vec2& position) 
	{
		m_position = position;
	}

	void Sprite::setRotation(const float rotation) 
	{
		m_rotation = rotation;
	}

	void Sprite::setSize(const glm::vec2& Size) 
	{
		m_Size = Size;
	}

	Sprite::~Sprite()
	{
		glDeleteBuffers(1, &m_VBO);
		glDeleteBuffers(1, &m_TBO);
		glDeleteVertexArrays(1, &m_VAO);
	}
}