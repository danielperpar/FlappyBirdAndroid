package com.anative.application.flappybirdandroid;

public class Timer {

    private long mCurrent = 0;
    private long mPrevious = 0;

    public Timer(){
        mCurrent = 0;
        mPrevious = 0;
    }

    public void start(){
        reset();
        mCurrent = System.currentTimeMillis();
        mPrevious = mCurrent;
    }

    //returns elapsed time in seconds since the last call to getTime()
    public float getDeltaTime(){
        mPrevious = mCurrent;
        mCurrent = System.currentTimeMillis();
        return (mCurrent - mPrevious) * 0.001f;
    }

    public void reset(){
        mCurrent = 0;
        mPrevious = 0;
    }
}
