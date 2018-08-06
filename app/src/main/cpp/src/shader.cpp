#include "shader.h"
#include <glm/gtc/type_ptr.hpp>
#include <cstdlib>
#include <android/log.h>


Shader::Shader(const std::string &vertexShader, const std::string &fragmentShader)
{
	Compile(vertexShader.c_str(), fragmentShader.c_str());
}

Shader::~Shader() {}

GLuint Shader::GetShaderId() const
{
    return mId;
}

void Shader::Use() const
{
	glUseProgram(this->mId);
}

void Shader::SetFloat(const char *name, float value) const
{
	Use();
	glUniform1f(glGetUniformLocation(this->mId, name), value);
}

void Shader::SetInteger(const char *name, int value) const
{
	Use();
	glUniform1i(glGetUniformLocation(this->mId, name), value);
}

void Shader::SetVector2f(const char *name, float x, float y) const
{
	Use();
	glUniform2f(glGetUniformLocation(this->mId, name), x, y);
}

void Shader::SetVector2fv(const char *name, const glm::vec2 &vec2) const
{
	Use();
	glUniform2f(glGetUniformLocation(this->mId, name), vec2.x, vec2.y);
}

void Shader::SetVector3f(const char *name, float x, float y, float z) const
{
	Use();
	glUniform3f(glGetUniformLocation(this->mId, name), x, y, z);
}

void Shader::SetVector3fv(const char *name, const glm::vec3 &vec3) const
{
	Use();
	glUniform3f(glGetUniformLocation(this->mId, name), vec3.x, vec3.y, vec3.z);
}

void Shader::SetVector4f(const char *name, float x, float y, float z, float w) const
{
	Use();
	glUniform4f(glGetUniformLocation(this->mId, name), x, y, z, w);
}

void Shader::SetVector4fv(const char *name, const glm::vec4 &vec4) const
{
	Use();
	glUniform4f(glGetUniformLocation(this->mId, name), vec4.x, vec4.y, vec4.z, vec4.w);
}

void Shader::SetMatrix4(const char *name, const glm::mat4 &mat4) const
{
	Use();
	glUniformMatrix4fv(glGetUniformLocation(this->mId, name), 1, GL_FALSE, glm::value_ptr(mat4));
}

void Shader::Clear()
{
 	glDeleteProgram(mId);
}

void Shader::Compile(const char *vertexShaderCode, const char * fragmentShaderCode)
{
	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShader, 1, &vertexShaderCode, NULL);
	glCompileShader(vShader);
	CheckCompLinkErrors(vShader, "SHADER");

	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShader, 1, &fragmentShaderCode, NULL);
	glCompileShader(fShader);
	CheckCompLinkErrors(fShader, "SHADER");

	mId = glCreateProgram();

    glBindAttribLocation(mId, 0, "aPos");
    glBindAttribLocation(mId, 1, "aTexCoords");

	glAttachShader(mId, vShader);
	glAttachShader(mId, fShader);
	glLinkProgram(mId);
	CheckCompLinkErrors(mId, "PROGRAM");

	//Shaders are linked into the program, so we don't need them anymore.
	glDeleteShader(vShader);
	glDeleteShader(fShader);
}

void Shader::CheckCompLinkErrors(GLuint object, const std::string &type) const
{
	GLint success;
	const int logLength = 1024;

	if (type == "SHADER")
	{
		glGetShaderiv(object, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			GLchar log[logLength];
			glGetShaderInfoLog(object, logLength, NULL, log);
			__android_log_print(ANDROID_LOG_ERROR, "FlappyBirdAndroid", "Error in shader compilation: %s", log);
		}
	}
	else
	{
		glGetProgramiv(object, GL_LINK_STATUS, &success);
		if (!success)
		{
			GLchar log[logLength];
			glGetProgramInfoLog(object, logLength, NULL, log);
			__android_log_print(ANDROID_LOG_ERROR, "FlappyBirdAndroid", "Error in program linkage: %s", log);
		}
	}
}



