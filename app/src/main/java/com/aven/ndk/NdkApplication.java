package com.aven.ndk;

import android.app.ActivityManager;
import android.app.Application;
import android.content.Context;
import android.text.TextUtils;
import android.util.Log;

/**
 * Created by Administrator on 2016/6/25.
 */
public class NdkApplication extends Application {

    @Override
    protected void attachBaseContext(Context base) {
        super.attachBaseContext(base);
    }

    @Override
    public void onCreate() {
        super.onCreate();
        String currentProcessName = getCurProcessName(this);
        Log.e("hyf" , "NdkApplication onCreate = " + currentProcessName);
        if(!TextUtils.isEmpty(currentProcessName) && currentProcessName.equals("com.aven.ndk")) {
            Watcher watcher = new Watcher(this);
            watcher.createAppMonitor("com.aven.ndk.shareId");
        }
    }

    String getCurProcessName (Context context) {
        int     pid = android.os.Process.myPid ();
        ActivityManager mActivityManager = (ActivityManager)getSystemService(Context.ACTIVITY_SERVICE);
        for(ActivityManager.RunningAppProcessInfo appProcess : mActivityManager.getRunningAppProcesses())  {
            if(appProcess.pid == pid){
                return appProcess.processName;
            }
        }
        return null ;
    }
}
