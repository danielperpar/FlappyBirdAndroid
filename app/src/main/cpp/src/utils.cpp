#include "utils.h"
#include <android/log.h>
#include <GLES2/gl2.h>
#include <sstream>

void CheckGLError()
{
    GLenum err = glGetError();
    if (err == GL_NO_ERROR)
        return;

    switch (err) {

        case GL_INVALID_ENUM:
            __android_log_print(ANDROID_LOG_ERROR, "FlappyBirdAndroid",
                                "GL_INVALID_ENUM: GLenum argument out of range");
            break;

        case GL_INVALID_VALUE:
            __android_log_print(ANDROID_LOG_ERROR, "FlappyBirdAndroid",
                                "GL_INVALID_VALUE: numeric argument out of range");
            break;

        case GL_INVALID_OPERATION:
            __android_log_print(ANDROID_LOG_ERROR, "FlappyBirdAndroid",
                                "GL_INVALID_OPERATION: operation illegal in current state");
            break;

        case GL_INVALID_FRAMEBUFFER_OPERATION:
            __android_log_print(ANDROID_LOG_ERROR, "FlappyBirdAndroid",
                                "GL_INVALID_FRAMEBUFFER_OPERATION: framebuffer object is not complete");
            break;

        case GL_OUT_OF_MEMORY:
            __android_log_print(ANDROID_LOG_ERROR, "FlappyBirdAndroid",
                                "GL_OUT_OF_MEMORY: not enough memory left to execute command");
            break;

        default:
            __android_log_print(ANDROID_LOG_ERROR, "FlappyBirdAndroid", "unlisted error");
            break;
    }
}

std::string stringValue(unsigned int value)
{
    std::ostringstream os ;
    os << value ;
    return os.str() ;
}

unsigned int atoi(std::string &alphaString)
{
    std::stringstream ss;
    ss << alphaString;
    unsigned int value;
    ss >> value;
    return value;
}
