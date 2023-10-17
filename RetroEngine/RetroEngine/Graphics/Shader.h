#pragma once
#include <string>

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

		static void CreateShader(Shader*, std::string, std::string);
		static void DisposeShader(Shader*);
	};
}
