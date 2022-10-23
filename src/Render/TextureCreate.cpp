
#include "TextureCreate.h"
namespace Render {

	TextureCreate::TextureCreate(GLint& Width,GLint& Heathe, unsigned char* data) {
		GLuint textureId;
		glGenTextures(1, &textureId);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureId);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Heathe, 0, GL_RGB, GL_UNSIGNED_BYTE, data );

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);

		
		
		glBindTexture(GL_TEXTURE_2D, 0);

		idTexture = textureId;
		is_Succses = true;

    }

	TextureCreate::~TextureCreate() {
		glDeleteTextures(1, &idTexture);
	}

	GLuint TextureCreate::GetUseTexture() {
		return idTexture;
	}

}