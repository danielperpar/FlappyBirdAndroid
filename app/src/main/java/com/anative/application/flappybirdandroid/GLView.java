package com.anative.application.flappybirdandroid;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.Log;
import android.view.MotionEvent;


public class GLView extends GLSurfaceView {

    private static final String TAG = "GLView";
    private GLRenderer mRenderer;
    private Game mGame;
    private boolean mTap = false;

    public GLView(Context context,Game game){
        super(context);
        mGame = game;
        try{
            setEGLContextClientVersion(2);
            mRenderer = new GLRenderer(mGame);
            game.setGLRenderer(mRenderer);
            setRenderer(mRenderer);
            setRenderMode(GLSurfaceView.RENDERMODE_CONTINUOUSLY);
        }catch(Exception e){
            Log.e("GLESNativeAndroid", "Unable to create GLES context!", e);
        }
    }


    @Override
    public boolean onTouchEvent(MotionEvent e)
    {
        switch(e.getAction()){
            case MotionEvent.ACTION_DOWN: {
                if(!mTap) {
                    mTap = true;
                    mGame.screenTouched();
                }
                break;
            }
            case MotionEvent.ACTION_UP:{
                mTap = false;
                break;
            }
        }
        return true;
    }

    public GLRenderer getRenderer(){
        return mRenderer;
    }

}
