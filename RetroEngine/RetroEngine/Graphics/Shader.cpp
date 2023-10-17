#include "Shader.h"

#include <iostream>

#include "../../glad/glad.h"

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

	void Shader::CreateShader(Shader* shader, const string vertexShaderFilename, const string fragmentShaderFilename)
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

		const char* vertexShaderSource   = vsStr.c_str();
		const char* fragmentShaderSource = fsStr.c_str();

		shader->vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(shader->vertexShader, 1, &vertexShaderSource, nullptr);
		glCompileShader(shader->vertexShader);

		int success;
		char infoLog[512];
		glGetShaderiv(shader->vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader->vertexShader, 512, nullptr, infoLog);
			cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
		}

		shader->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(shader->fragmentShader, 1, &fragmentShaderSource, nullptr);
		glCompileShader(shader->fragmentShader);
		glGetShaderiv(shader->fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader->fragmentShader, 512, nullptr, infoLog);
			cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
		}

		shader->shaderProgram = glCreateProgram();
		glAttachShader(shader->shaderProgram, shader->vertexShader);
		glAttachShader(shader->shaderProgram, shader->fragmentShader);
		glLinkProgram(shader->shaderProgram);

		glGetProgramiv(shader->shaderProgram, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader->shaderProgram, 512, nullptr, infoLog);
			cout << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
		}
	}
	void Shader::DisposeShader(Shader* shader)
	{
		glDeleteShader(shader->vertexShader);
		glDeleteShader(shader->fragmentShader);
		glDeleteProgram(shader->shaderProgram);
	}
}
