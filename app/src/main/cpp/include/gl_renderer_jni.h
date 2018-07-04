#ifndef FLAPPYBIRDANDROID_GLRENDERERJNI_H
#define FLAPPYBIRDANDROID_GLRENDERERJNI_H

#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Class:     com_anative_application_flappybirdandroid_Game
 * Method:    initOpenGL
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_com_anative_application_flappybirdandroid_GLRenderer_initOpenGL
(JNIEnv *, jobject, jint, jint);

#ifdef __cplusplus
}
#endif
#endif //FLAPPYBIRDANDROID_GLRENDERERJNI_H
