//
// Created by Administrator on 2016/6/24.
//

#ifndef PROCCESSDAEMON_CHILD_H
#define PROCCESSDAEMON_CHILD_H

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

class Child : public ProcessBase
{
public:

Child( );

virtual ~Child();

virtual void do_work();

virtual bool create_child();

virtual void catch_child_dead_signal();

virtual void on_child_end();

bool create_channel();

private:

/**
* 处理父进程死亡事件
*/
void handle_parent_die();

/**
* 侦听父进程发送的消息
*/
void listen_msg();

/**
* 重新启动父进程.
*/
void restart_parent();

/**
* 处理来自父进程的消息
*/
void handle_msg( const char* msg );

/**
* 线程函数，用来检测父进程是否挂掉
*/
void* parent_monitor();

void start_parent_monitor();

/**
* 这个联合体的作用是帮助将类的成员函数做为线程函数使用
*/
union
{
void* (*thread_rtn)(void*);

void* (Child::*member_rtn)();
}RTN_MAP;
};


#endif //PROCCESSDAEMON_CHILD_H
