//
// Created by Administrator on 2016/6/24.
//

#include "com_aven_ndk_Watcher.h"
#include "Parent.h"
#include <android/log.h>

#define  LOG_TAG    "ndk_demo"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR , LOG_TAG, __VA_ARGS__)

JNIEXPORT jboolean JNICALL Java_com_aven_ndk_Watcher_createWatcher
  (JNIEnv *env, jobject thiz, jstring user){
    LOGE("createWatcher");
    g_process = new Parent( env, thiz );
    g_userId  = "com.aven.ndk.shareId";
    g_process->catch_child_dead_signal();
    if( !g_process->create_child() )
    {
        LOGE("<<create child error!>>");
        return JNI_FALSE;
    }
    return JNI_TRUE;
  }


JNIEXPORT jboolean JNICALL Java_com_aven_ndk_Watcher_connectToMonitor
        (JNIEnv *, jobject){
    if( g_process != NULL )
    {
        if( g_process->create_channel() )
        {
            return JNI_TRUE;
        }

        return JNI_FALSE;
    }
}

JNIEXPORT jint JNICALL Java_com_aven_ndk_Watcher_sendMsgToMonitor
        (JNIEnv *, jobject, jstring){
    return 0;
}
