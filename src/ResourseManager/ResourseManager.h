#pragma once
#include <glad/glad.h>
#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <map>


namespace Render{
	class ShaderCreate;
	class TextureCreate;
}

class ResourseManager
{
public:
	ResourseManager(const std::string& path);
	~ResourseManager() = default;

	std::string GetFile(const std::string& PathExe);

	std::shared_ptr<Render::ShaderCreate> GetShaderLoad(const std::string NameShader);

	std::shared_ptr<Render::ShaderCreate> shaderLoad(const std::string& shaderName,
		const std::string& vertexName,
		const std::string& fragmentName);

	std::shared_ptr<Render::TextureCreate> TextureLoad(const std::string& TextureName,const std::string& TexturePath);

	std::shared_ptr<Render::TextureCreate> GetTextureLoad(const std::string& NameShader);

 private:
	 typedef std::map<std::string, std::shared_ptr<Render::ShaderCreate>> DictionarySourses;
	 DictionarySourses mapShader;

	 typedef std::map<std::string, std::shared_ptr<Render::TextureCreate>> DictionaryTexture;
	 DictionaryTexture mapTex;

	 bool is_CompileShader = false;
	 std::string m_Path;
};

