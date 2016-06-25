//
// Created by Administrator on 2016/6/24.
//

#ifndef PROCCESSDAEMON_PARENT_H
#define PROCCESSDAEMON_PARENT_H
#include "ProcessBase.h"
#include <jni.h>
#include <sys/select.h>
#include <unistd.h>
#include <sys/socket.h>
#include <pthread.h>
#include <signal.h>
#include <sys/wait.h>
#include <android/log.h>
#include <sys/types.h>
#include <sys/un.h>
#include <errno.h>
#include <stdlib.h>
#ifdef __cplusplus

extern "C" {
#endif
    class Parent : public ProcessBase {
    public:

        Parent(JNIEnv *env, jobject jobj);

        virtual bool create_child();

        virtual void do_work();

        virtual void catch_child_dead_signal();

        virtual void on_child_end();

        virtual ~Parent();

        bool create_channel();

    /**
    * 获取父进程的JNIEnv
    */
        JNIEnv *get_jni_env() const;

    /**
    * 获取Java层的对象
    */
        jobject get_jobj() const;

    private:

        JNIEnv *m_env;

        jobject m_jobj;

    };
}

#endif //PROCCESSDAEMON_PARENT_H
