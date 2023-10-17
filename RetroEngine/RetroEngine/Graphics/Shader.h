#pragma once
#include <string>

#include "../../glad/glad.h"

namespace RetroEngine::Graphics
{
	class Shader
	{
	private:

		unsigned int vertexShader, fragmentShader;
		unsigned int shaderProgram;

	public:

		Shader();

		       void UseProgram() const;

		static void CreateShader(Shader*, const std::string&, const std::string&);
		static void DisposeShader(const Shader*);

	private:

		static unsigned int CreateShader(GLenum, const std::string&);

		static void         PrintCompilationStatus(unsigned int);
		static void         PrintProgramLinkingStatus(unsigned int);
	};
}
