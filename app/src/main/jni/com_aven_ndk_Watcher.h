/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
#include "ProcessBase.h"
/* Header for class com_aven_ndk_Watcher */

#ifndef _Included_com_aven_ndk_Watcher
#define _Included_com_aven_ndk_Watcher
#ifdef __cplusplus
/**
* 全局变量，代表应用程序进程.
*/
ProcessBase *g_process = NULL;

/**
* 应用进程的UID.
*/
const char* g_userId = NULL;

/**
* 全局的JNIEnv，子进程有时会用到它.
*/
JNIEnv* g_env = NULL;
extern "C" {
#endif
/*
 * Class:     com_aven_ndk_Watcher
 * Method:    createWatcher
 * Signature: (Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_aven_ndk_Watcher_createWatcher
  (JNIEnv *, jobject, jstring);

/*
 * Class:     com_aven_ndk_Watcher
 * Method:    connectToMonitor
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_com_aven_ndk_Watcher_connectToMonitor
  (JNIEnv *, jobject);

/*
 * Class:     com_aven_ndk_Watcher
 * Method:    sendMsgToMonitor
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_com_aven_ndk_Watcher_sendMsgToMonitor
  (JNIEnv *, jobject, jstring);

#ifdef __cplusplus
}
#endif
#endif
