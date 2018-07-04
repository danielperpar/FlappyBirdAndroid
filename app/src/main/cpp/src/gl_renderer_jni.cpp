#include "gl_renderer_jni.h"
#include <GLES2/gl2.h>
#include <android/log.h>

#ifdef __cplusplus
extern "C" {
#endif



JNIEXPORT void JNICALL Java_com_anative_application_flappybirdandroid_GLRenderer_initOpenGL
        (JNIEnv *env, jobject obj, jint screenWidth, jint screenHeight){

    const GLubyte *version = glGetString(GL_VERSION);
    __android_log_print(ANDROID_LOG_INFO, "OPENGLES VERSION", "%s", version);
    glViewport(0, 0, screenWidth, screenHeight);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.5f, 0.5f, 1.0f, 1.0f);
}

#ifdef __cplusplus
}
#endif