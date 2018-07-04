#ifndef FLAPPYBIRDANDROID_RESOURCEMANAGER_H
#define FLAPPYBIRDANDROID_RESOURCEMANAGER_H

#include "shader.h"
#include "texture2D.h"
#include <string>
#include <map>
#include <GLES2/gl2.h>

struct AAssetManager;
class Sound;
class ResourceManager final
{
public:
    static void LoadShader(AAssetManager *assetManager, const std::string &shaderName, const std::string &vertexShaderPath, const std::string &fragmentShaderPath);
    static void LoadTextureFromFile(AAssetManager *assetManager, const std::string &textureName, const std::string &texturePath);
    static void LoadProperties(AAssetManager *assetManager, const std::string &propertiesFilePath);
    static void LoadSound(AAssetManager *assetManager, const std::string &soundPath);
    static const Shader& GetShader(const std::string &shaderName);
    static const Texture2D& GetTexture(const std::string &textureName);
    static const std::string& GetPropString(const std::string &propKeyString);
    static int GetPropInt(const std::string &propKeyInt);
    static float GetPropFloat(const std::string &propKeyFloat);
    static Sound *GetSound(const std::string &soundPath);
    static void Clear();
    static void ClearShaders();
    static void ClearTextures();
    static void ClearSounds();

private:
    ResourceManager();
    static std::map<std::string, Shader> mShaders;
    static std::map<std::string, Texture2D> mTextures;
    static std::map<std::string, std::string> mProperties;
    static std::map<std::string, Sound*> mSounds;

    static int StringToInt(const std::string &str);
    static float StringToFloat(const std::string &str);

    //methods to supply to "funopen" function used in texture load
    static int AndroidRead(void* cookie, char* buf, int size);
    static int AndroidWrite(void* cookie, const char* buf, int size);
    static fpos_t AndroidSeek(void* cookie, fpos_t offset, int whence);
    static int AndroidClose(void* cookie);

    static std::string ReadShaderFromFile(AAssetManager *assetManager, const std::string &filePath);
};

#endif //FLAPPYBIRDANDROID_RESOURCEMANAGER_H
