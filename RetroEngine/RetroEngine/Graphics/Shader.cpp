#include "Shader.h"

#include <iostream>

#include "../FileSystem/FileUtility.h"

using namespace std;

using namespace RetroEngine::FileSystem;

namespace RetroEngine::Graphics
{
	Shader::Shader() :
		vertexShader(0),
		fragmentShader(0),
		shaderProgram(0)
	{
	}

	void Shader::UseProgram() const
	{
		glUseProgram(shaderProgram);
	}

	void Shader::CreateShader(Shader* shader, const string& vertexShaderFilename, const string& fragmentShaderFilename)
	{
		const string vsStr = FileUtility::ReadFile(vertexShaderFilename);
		if (vsStr.empty())
		{
			cout << "Can't read Vertex Shader " << vertexShaderFilename << endl;
			return;
		}

		const string fsStr = FileUtility::ReadFile(fragmentShaderFilename);
		if (fsStr.empty())
		{
			cout << "Can't read Fragment Shader " << fragmentShaderFilename << endl;
			return;
		}
		
		shader->vertexShader   = CreateShader(GL_VERTEX_SHADER, vsStr);
		shader->fragmentShader = CreateShader(GL_FRAGMENT_SHADER, fsStr);

		shader->shaderProgram = glCreateProgram();
		glAttachShader(shader->shaderProgram, shader->vertexShader);
		glAttachShader(shader->shaderProgram, shader->fragmentShader);
		glLinkProgram(shader->shaderProgram);
		PrintProgramLinkingStatus(shader->shaderProgram);
	}

	void Shader::DisposeShader(const Shader* shader)
	{
		glDeleteShader(shader->vertexShader);
		glDeleteShader(shader->fragmentShader);
		glDeleteProgram(shader->shaderProgram);
	}

	unsigned int Shader::CreateShader(const GLenum type, const string& str)
	{
		const char* shaderSource = str.c_str();
		const unsigned int shader = glCreateShader(type);
		glShaderSource(shader, 1, &shaderSource, nullptr);
		glCompileShader(shader);
		PrintCompilationStatus(shader);
		return shader;
	}

	void Shader::PrintCompilationStatus(const unsigned int shader)
	{
		int success;
		char infoLog[512];
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, nullptr, infoLog);
			cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << endl;
		}
	}

	void Shader::PrintProgramLinkingStatus(const unsigned int shaderProgram)
	{
		int success;
		char infoLog[512];
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
			cout << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
		}
	}
}
