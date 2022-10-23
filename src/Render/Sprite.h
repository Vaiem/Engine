#pragma once

#include <map>
#include <string>
#include <glad/glad.h>
#include <glm-master/glm/vec2.hpp>
#include <memory>

namespace  Render
{
	class TextureCreate;
	class ShaderCreate;
	

class Sprite
{
public:
	
	Sprite(const std::shared_ptr<TextureCreate> texture2D,
		const std::shared_ptr<ShaderCreate> ShaderProg,
		const glm::vec2& position = glm::vec2(0.f),
		const glm::vec2& Size = glm::vec2(1.f),
		const float rotation = 0.f
		);

	void Render() const;
	void setRotation(const float rotation);
	void setPosition(const glm::vec2& position);
	void setSize(const glm::vec2& Size);
	~Sprite();

private:

	std::shared_ptr<TextureCreate> m_pTexture;
	std::shared_ptr<ShaderCreate> m_pShader;
	glm::vec2 m_position;
	glm::vec2 m_Size;
	float m_rotation;
	GLuint m_VAO;
	GLuint m_VBO;
	GLuint m_TBO;

};
}


