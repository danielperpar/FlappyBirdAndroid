package com.anative.application.flappybirdandroid;

import android.content.res.AssetManager;

import java.util.List;

public class Game {

    //handle to hold a pointer to the native c++ game
    private long nativeHandle;

    private int mWidth;
    private int mHeight;
    private AssetManager mAssetManager;
    private GLRenderer mRenderer;


    public Game(int width, int height, AssetManager mgr, String internalPath) {
        mWidth = width;
        mHeight = height;
        mAssetManager = mgr;

        createNativeObject(mWidth, mHeight, mAssetManager, internalPath);
    }

    public int getWidth(){
        return mWidth;
    }

    public int getHeight(){
        return mHeight;
    }

    public AssetManager getAssetManager(){
        return mAssetManager;
    }

    public GLRenderer getRenderer(){
        return mRenderer;
    }

    public void setGLRenderer(GLRenderer renderer){
        mRenderer = renderer;
    }

    // Native methods
    public native void createNativeObject(int screenWidth, int screenHeight, AssetManager mgr, String internalPath);
    public native void destroyNativeObject();
    public native void loadProperties();
    public native void loadTexturesFromFile();
    public native void initGameObjects();
    public native void initRendererObjects();
    public native void processInput();
    public native void update(float dt);
    public native void render(float dt);
    public native void screenTouched();
    public native void clearTextures();
    public native void clearShaders();
    public native void loadSoundEffects();
    public native void startSoundManager();

}
