#include "game_jni.h"
#include "game.h"
#include <jni.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include "resource_manager.h"
#include "globals.h"
#include "handle.h"
#include "glm/glm.hpp"
#include <string>

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL Java_com_anative_application_flappybirdandroid_Game_createNativeObject
  (JNIEnv *env, jobject obj, jint width, jint height, jobject assetManager, jstring internalPath){
    const char *path = env->GetStringUTFChars(internalPath, NULL);
    std::string pathStr(path);
    AAssetManager *mgr = AAssetManager_fromJava(env, assetManager);
    setHandle<Game>(env, obj, new Game(width, height, mgr, pathStr));
    env->ReleaseStringUTFChars(internalPath, path);
  }

JNIEXPORT void JNICALL Java_com_anative_application_flappybirdandroid_Game_destroyNativeObject
  (JNIEnv *env, jobject obj){

    ResourceManager::Clear();
    Game *game = getHandle<Game>(env, obj);
    DELETE_PTR(game);
  }

JNIEXPORT void JNICALL Java_com_anative_application_flappybirdandroid_Game_loadProperties
  (JNIEnv *env, jobject obj){

    Game *game = getHandle<Game>(env, obj);
    game->LoadProperties();
  }

JNIEXPORT void JNICALL Java_com_anative_application_flappybirdandroid_Game_loadTexturesFromFile
        (JNIEnv *env, jobject obj){
    Game *game = getHandle<Game>(env, obj);
    game->LoadTexturesFromFile();
}

JNIEXPORT void JNICALL Java_com_anative_application_flappybirdandroid_Game_initGameObjects
        (JNIEnv *env, jobject obj){

    Game *game = getHandle<Game>(env, obj);
    game->InitGameObjects();
}

JNIEXPORT void JNICALL Java_com_anative_application_flappybirdandroid_Game_initRendererObjects
        (JNIEnv *env, jobject obj){

    Game *game = getHandle<Game>(env, obj);
    game->InitRendererObjects();
}

JNIEXPORT void JNICALL Java_com_anative_application_flappybirdandroid_Game_processInput
  (JNIEnv *env, jobject obj){

    Game *game = getHandle<Game>(env, obj);
    game->ProcessInput();
  }

JNIEXPORT void JNICALL Java_com_anative_application_flappybirdandroid_Game_update
  (JNIEnv *env, jobject obj, jfloat dt){

    Game *game = getHandle<Game>(env, obj);
    game->Update(dt);
  }

JNIEXPORT void JNICALL Java_com_anative_application_flappybirdandroid_Game_render
  (JNIEnv *env, jobject obj, jfloat dt){

    Game *game = getHandle<Game>(env, obj);
    game->Render(dt);
}

JNIEXPORT void JNICALL Java_com_anative_application_flappybirdandroid_Game_screenTouched
        (JNIEnv *env, jobject obj){

    Game *game = getHandle<Game>(env, obj);
    game->TouchScreen();
}

JNIEXPORT void JNICALL Java_com_anative_application_flappybirdandroid_Game_clearTextures
        (JNIEnv *env, jobject obj) {

    ResourceManager::ClearTextures();
}

JNIEXPORT void JNICALL Java_com_anative_application_flappybirdandroid_Game_clearShaders
        (JNIEnv *env, jobject obj) {

    ResourceManager::ClearShaders();
}

JNIEXPORT void JNICALL Java_com_anative_application_flappybirdandroid_Game_loadSoundEffects
        (JNIEnv *env, jobject obj) {

    Game *game = getHandle<Game>(env, obj);
    game->LoadSoundEffects();
}


JNIEXPORT void JNICALL Java_com_anative_application_flappybirdandroid_Game_startSoundManager
        (JNIEnv *env, jobject obj){

    Game *game = getHandle<Game>(env, obj);
    game->StartSoundManager();
}

#ifdef __cplusplus
}
#endif
