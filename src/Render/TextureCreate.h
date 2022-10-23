#pragma once

#include <glad/glad.h>

namespace Render{
	class TextureCreate {
		public:
			  TextureCreate(GLint& Width, GLint& Heathe, unsigned char* data);
			  GLuint GetUseTexture();
			  ~TextureCreate();
		private:
			GLuint idTexture  = 0;
			bool is_Succses = false;
	};
}