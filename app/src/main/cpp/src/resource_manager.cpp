#include <android/asset_manager.h>
#include <android/log.h>
#include "resource_manager.h"
#include <fstream>
#include <string>
#include <sstream>
#include "globals.h"
#include "sound.h"
#include <errno.h>
#include "stb_image.h"

#include <cstdlib>

std::map<std::string, Shader> ResourceManager::mShaders;
std::map<std::string, Texture2D> ResourceManager::mTextures;
std::map<std::string, std::string> ResourceManager::mProperties;
std::map<std::string, Sound*> ResourceManager::mSounds;

ResourceManager::ResourceManager() {}

void ResourceManager::LoadShader(AAssetManager *assetManager, const std::string &shaderName, const std::string &vertexShaderPath, const std::string &fragmentShaderPath)
{
    if (mShaders.find(shaderName) != mShaders.end())
    {
        __android_log_print(ANDROID_LOG_ERROR, "MyFlappyBirdAndroid", "Shader with name: %s already in the resources map. Not loaded.", shaderName.c_str());
        return;
    }

    const std::string vertexShaderStr = ReadShaderFromFile(assetManager, vertexShaderPath);
    const std::string fragmentShaderStr = ReadShaderFromFile(assetManager, fragmentShaderPath);

    Shader shader = Shader(vertexShaderStr, fragmentShaderStr);
    mShaders.insert(std::map<std::string, Shader>::value_type(shaderName, shader));
}

void ResourceManager::LoadTextureFromFile(AAssetManager *assetManager, const std::string &textureName, const std::string &texturePath)
{
    if (mTextures.find(textureName) != mTextures.end())
    {
        __android_log_print(ANDROID_LOG_ERROR, "MyFlappyBirdAndroid", "Texture with name: %s already in the resources map. Not loaded", textureName.c_str());
        return;
    }

    AAsset *asset = AAssetManager_open(assetManager, texturePath.c_str(), AASSET_MODE_UNKNOWN);
    if(!asset)
    {
        __android_log_print(ANDROID_LOG_ERROR, "FlappyBirdAndroid", "Failed to open texture asset.");
    }
    FILE *fp = funopen(asset, AndroidRead, AndroidWrite, AndroidSeek, AndroidClose);

    int nChannels = 0;
    int width = 0;
    int height = 0;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *image = stbi_load_from_file(fp, &width, &height, &nChannels, 4);
    Texture2D texture = Texture2D(width, height, image);
    mTextures.insert(std::map<std::string, Texture2D>::value_type(textureName, texture));
    stbi_image_free(image);
    fclose(fp);
}

void ResourceManager::LoadProperties(AAssetManager *assetManager, const std::string &propertiesFilePath)
{

    AAsset *asset = AAssetManager_open(assetManager, propertiesFilePath.c_str(), AASSET_MODE_BUFFER);
    if(!asset)
    {
        __android_log_print(ANDROID_LOG_ERROR, "MyFlappyBirdAndroid", "Error opening properties file at: %s", propertiesFilePath.c_str());
        return;
    }

    long length = AAsset_getLength(asset);
    char *buffer = new char[length];
    AAsset_read(asset, buffer, length);
    AAsset_close(asset);
    std::stringstream ss;
    ss << buffer;
    delete[] buffer;

    std::string key;
    std::string value;
    while(std::getline(ss, key, ':'))
    {
        std::getline(ss, value);
        mProperties.insert(std::map<std::string, std::string>::value_type(key, value));
    }
}

void ResourceManager::LoadSound(AAssetManager *assetManager, const std::string &soundPath)
{
    std::map<std::string, Sound*>::iterator it = mSounds.find(soundPath);
    if(it != mSounds.end())
    {
        __android_log_print(ANDROID_LOG_ERROR, "MyFlappyBirdAndroid", "Sound %s already loaded.", soundPath.c_str());
        return;
    }

    AAsset *asset = AAssetManager_open(assetManager, soundPath.c_str(), AASSET_MODE_BUFFER);
    if(!asset)
    {
        __android_log_print(ANDROID_LOG_ERROR, "MyFlappyBirdAndroid", "Error opening sound file at: %s", soundPath.c_str());
        return;
    }

    long length = AAsset_getLength(asset);
    uint8_t *soundBuffer = new uint8_t[length];
    AAsset_read(asset, soundBuffer, length);
    AAsset_close(asset);
    Sound *sound = new Sound(soundPath);
    sound->SetSoundBuffer(soundBuffer);
    sound->SetBufferLength(length);

    mSounds.insert(std::map<std::string, Sound*>::value_type(soundPath, sound));
}

const Shader& ResourceManager::GetShader(const std::string &shaderName)
{
    std::map<std::string, Shader>::iterator it = mShaders.find(shaderName);
    if (it == mShaders.end())
    {
        __android_log_print(ANDROID_LOG_ERROR, "MyFlappyBirdAndroid", "No shader in the resources with the name: %s", shaderName.c_str());
    }
    return (*it).second;
}

const Texture2D& ResourceManager::GetTexture(const std::string &textureName)
{
    std::map<std::string, Texture2D>::iterator it = mTextures.find(textureName);
    if (it == mTextures.end())
    {
        __android_log_print(ANDROID_LOG_ERROR, "MyFlappyBirdAndroid", "No texture in the resources with the name: %s", textureName.c_str());
    }
    return (*it).second;
}

const std::string& ResourceManager::GetPropString(const std::string &propKeyString)
{
    std::map<std::string, std::string>::iterator it = mProperties.find(propKeyString);
    if (it == mProperties.end())
    {
        __android_log_print(ANDROID_LOG_ERROR, "MyFlappyBirdAndroid", "No property found with the name: %s", propKeyString.c_str());
        return propKeyString;
    }
    return (*it).second;
}

int ResourceManager::GetPropInt(const std::string &propKeyInt)
{
    std::map<std::string, std::string>::iterator it = mProperties.find(propKeyInt);
    if (it == mProperties.end())
    {
        __android_log_print(ANDROID_LOG_ERROR, "MyFlappyBirdAndroid", "No property found with the name: %s", propKeyInt.c_str());
        return -1;
    }
    return StringToInt((*it).second);
}

float ResourceManager::GetPropFloat(const std::string &propKeyFloat)
{
    std::map<std::string, std::string>::iterator it = mProperties.find(propKeyFloat);
    if (it == mProperties.end())
    {
        __android_log_print(ANDROID_LOG_ERROR, "MyFlappyBirdAndroid", "No property found with the name: %s", propKeyFloat.c_str());
        return -1.0f;
    }
    return StringToFloat((*it).second);
}

Sound *ResourceManager::GetSound(const std::string &soundPath)
{
    return mSounds[soundPath];
}

void ResourceManager::Clear()
{
    ClearShaders();
    ClearTextures();
    mProperties.clear();
    ClearSounds();

}

void ResourceManager::ClearShaders()
{
    //OpenGL context is destoyed and resources are freed on Activity onDestroy().
    //It's not required to delete program manually
    mShaders.clear();
}

void ResourceManager::ClearTextures()
{
    //OpenGL context is destoyed and resources are freed on Activity onDestroy().
    //It's not required to delete texture manually
    mTextures.clear();
}

void ResourceManager::ClearSounds()
{
    for(auto it : mSounds)
    {
        DELETE_PTR(it.second);
    }

    mSounds.clear();
}

int ResourceManager::StringToInt(const std::string &str)
{
    std::stringstream in(str);
    int value = 0;
    in >> value;
    return value;
}

float ResourceManager::StringToFloat(const std::string &str)
{
    std::stringstream in(str);
    float value = 0.0f;
    in >> value;
    return value;
}

int ResourceManager::AndroidRead(void* cookie, char* buf, int size) {
    return AAsset_read((AAsset*)cookie, buf, size);
}

int ResourceManager::AndroidWrite(void* cookie, const char* buf, int size) {
    return EACCES; // can't provide write access to the apk
}

fpos_t ResourceManager::AndroidSeek(void* cookie, fpos_t offset, int whence) {
    return AAsset_seek((AAsset*)cookie, offset, whence);
}

int ResourceManager::AndroidClose(void* cookie) {
    AAsset_close((AAsset*)cookie);
    return 0;
}

std::string ResourceManager::ReadShaderFromFile(AAssetManager *assetManager, const std::string &filePath)
{
    AAsset *asset = AAssetManager_open(assetManager, filePath.c_str(), AASSET_MODE_BUFFER);
    size_t length = AAsset_getLength(asset);
    char *buffer = new char[length];
    AAsset_read(asset, buffer, length);
    std::string shaderStr = std::string(buffer, length);
    AAsset_close(asset);
    DELETE_PTR_ARRAY(buffer);
    return shaderStr;
}