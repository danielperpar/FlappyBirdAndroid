package com.anative.application.flappybirdandroid;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.DisplayMetrics;

public class MainActivity extends AppCompatActivity {

    static {
        System.loadLibrary("native-flappybird");
    }

    private GLView mGLView;
    private Game mGame;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        DisplayMetrics metrics = new DisplayMetrics();
        getWindowManager().getDefaultDisplay().getMetrics(metrics);
        String internalPath = getFilesDir().getAbsolutePath();
        mGame = new Game(metrics.widthPixels, metrics.heightPixels, getAssets(), internalPath);
        mGLView = new GLView(this, mGame);
        setContentView(mGLView);
    }

    @Override
    protected void onResume(){
        if(mGLView != null) {
            mGLView.onResume();
        }
        super.onResume();
    }

    @Override
    protected void onPause(){
        if(mGLView != null) {
            mGLView.onPause();
            mGLView.getRenderer().getTimer().reset();
        }
        super.onPause();
    }

    @Override
    protected void onDestroy(){
        mGame.destroyNativeObject();
        super.onDestroy();
    }
}
