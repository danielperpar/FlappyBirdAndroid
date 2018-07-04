package com.anative.application.flappybirdandroid;

import android.opengl.GLSurfaceView.Renderer;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class GLRenderer implements Renderer {

    private Game mGame;
    private Timer mTimer;
    private boolean isFirstCreation = true;


    public GLRenderer(Game game){
        mGame = game;
        mTimer = new Timer();
    }

    @Override
    public void onSurfaceCreated(GL10 unused, EGLConfig config) {
        initOpenGL(mGame.getWidth(), mGame.getHeight());
        if(isFirstCreation) {
            isFirstCreation = false;
            mGame.loadProperties();
            mGame.loadTexturesFromFile();
            mGame.initRendererObjects();
            mGame.initGameObjects();
            mGame.loadSoundEffects();
            mGame.startSoundManager();
        }
        else {
            mGame.clearTextures();
            mGame.clearShaders();
            mGame.loadTexturesFromFile();
            mGame.initRendererObjects();
        }
        mTimer.start();
    }

    @Override
    public void onSurfaceChanged(GL10 unused, int width, int height){
    //forced screenOrientation=portrait in the manifest
    }

    @Override
    public void onDrawFrame(GL10 unused) {

        float dt = mTimer.getDeltaTime();
        mGame.processInput();
        mGame.update(dt);
        mGame.render(dt);
    }

    public Timer getTimer(){
        return mTimer;
    }

    //native methods
    public native void initOpenGL(int screenWidth, int screenHeight);

}
