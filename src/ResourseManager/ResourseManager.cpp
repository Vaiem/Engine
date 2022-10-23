#include <glad/glad.h>
#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <sstream>
#include "ResourseManager.h"
#include "../Render/ShaderCreate.h"
#include "../Render/TextureCreate.h"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"

 ResourseManager::ResourseManager(const std::string& PathExe) {
	size_t toch = PathExe.find_last_of("/ \\");
	m_Path = PathExe.substr(0, toch);
}

 std::string ResourseManager::GetFile(const std::string& NameShaderPath) {
	 std::ifstream f;
	 f.open(m_Path + "/" + NameShaderPath.c_str(),std::ios::in|std::ios::binary);
	 if (!f.is_open())
	 {
		 std::cerr << "ERR::GETFFILE\n";
		 return "";
	 }
	 std::stringstream buffer;
	 buffer << f.rdbuf();
	 return buffer.str();
}

 std::shared_ptr<Render::ShaderCreate> ResourseManager::shaderLoad(const std::string& shaderName, const std::string& vertexName,
	 const std::string& fragmentName) {

      auto vertexShader = GetFile(vertexName);
	  if (vertexShader == "")
	  {
		  is_CompileShader = false;
		  std::cerr << "non vertexShader\n";
		  return nullptr;
	  }

	  auto fragmentShader = GetFile(fragmentName);
	  if (fragmentShader == "")
	  {

		  is_CompileShader = false;
		  std::cerr << "non fragmentShader\n";
		  return nullptr;
	  }

	  std::shared_ptr<Render::ShaderCreate> pShaderProgram(new Render::ShaderCreate(vertexShader, fragmentShader));
	  if (pShaderProgram->is_Sucsess)
	  {
		  mapShader.emplace(shaderName, pShaderProgram);
	      return pShaderProgram;

	  }
	  return nullptr;
 }


 std::shared_ptr<Render::ShaderCreate> ResourseManager::GetShaderLoad(const std::string NameShader) {
	 
	 DictionarySourses::const_iterator it = mapShader.find(NameShader);
	 if (it != mapShader.end())
	 {
		 return it->second;
	 }
	 return nullptr;
 }


 std::shared_ptr<Render::TextureCreate> ResourseManager::TextureLoad(const std::string& NameTexture, const std::string& TexturePath)
 {
	 int chanels = 0;
	 GLint Width = 0;
	 GLint Height = 0;
	 std::string path(m_Path + "/" + TexturePath);
	 
	 stbi_set_flip_vertically_on_load(true);
	 unsigned char* data = stbi_load(path.c_str(), &Width, &Height, &chanels, 0);

	 if (!data)
	 {
		 std::cerr << "ERR::TEXTURELOAd";
		 return nullptr;
	 }
	
	 
	 std::shared_ptr<Render::TextureCreate> pNewTexture(new Render::TextureCreate(Width, Height,data));
 

	 mapTex.emplace(NameTexture, pNewTexture);

	 stbi_image_free(data);

	 return pNewTexture;
 }


 std::shared_ptr<Render::TextureCreate> ResourseManager::GetTextureLoad(const std::string& NameShader)
 {
	 auto pTexture = mapTex.find(NameShader);
	 if (pTexture != mapTex.end())
	 {
		 return pTexture->second;
	 }
	 std::cout << "ERRGETTEXTURE::GetTextureLoad\n";
	 return nullptr;
 }