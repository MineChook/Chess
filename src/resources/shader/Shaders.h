#pragma once
#include <string>

struct ShaderSources
{
    std::string VertexSource;
    std::string FragmentSource;

    ShaderSources(std::string vertexSource, std::string fragmentSource);
};

ShaderSources ParseShader(const std::string& filePath);

unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);