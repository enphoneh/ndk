//
// Created by Administrator on 2016/6/24.
//

#include "Parent.h"
#include "Child.h"
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

extern ProcessBase* g_process;
extern const char* g_userId;
extern JNIEnv* g_env;

int ProcessBase::write_to_channel( void* data, int len )
{
    return write( m_channel, data, len );
}

int ProcessBase::read_from_channel( void* data, int len )
{
    return read( m_channel, data, len );
}

int ProcessBase::get_channel() const
{
    return m_channel;
}

void ProcessBase::set_channel( int channel_fd )
{
    m_channel = channel_fd;
}

ProcessBase::ProcessBase()
{

}

ProcessBase::~ProcessBase()
{
    close(m_channel);
}

Parent::Parent(JNIEnv *env, jobject jobj) : m_env(env)
{
    LOGE("<<new parent instance>>");
    m_jobj = env->NewGlobalRef(jobj);
}

Parent::~Parent()
{
    LOGE( "<<Parent::~Parent()>>" );
    g_process = NULL;
}

void Parent::do_work()
{
}

JNIEnv* Parent::get_jni_env() const
{
    return m_env;
}

jobject Parent::get_jobj() const
{
    return m_jobj;
}

/**
* 父进程创建通道,这里其实是创建一个客户端并尝试
* 连接服务器(子进程)
*/
bool ProcessBase::create_channel()
{
    int sockfd;
    sockaddr_un addr;
    while(true)
    {
        sockfd = socket( AF_LOCAL, SOCK_STREAM, 0 );
        if( sockfd < 0 )
        {
            LOGE("<<Parent create channel failed>>");
            return false;
        }
        memset(&addr, 0, sizeof(addr));
        addr.sun_family = AF_LOCAL;
        strcpy( addr.sun_path, PATH );

        if( connect( sockfd, (sockaddr*)&addr, sizeof(addr)) < 0 )
        {
            close(sockfd);
            sleep(1);
            continue;
        }
        set_channel(sockfd);
        LOGE("<<parent channel fd %d>>", m_channel );
        break;
    }
    return true;
}

/**
* 子进程死亡会发出SIGCHLD信号,通过捕捉此信号父进程可以
* 知道子进程已经死亡,此函数即为SIGCHLD信号的处理函数.
*/
static void sig_handler( int signo )
{
    pid_t pid;
    int status;
    //调用wait等待子进程死亡时发出的SIGCHLD
    //信号以给子进程收尸，防止它变成僵尸进程
    pid = wait(&status);
    if( g_process != NULL )
    {
        g_process->on_child_end();
    }
}

void Parent::catch_child_dead_signal()
{
    LOGE("<<process %d install child dead signal detector!>>", getpid());
    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = sig_handler;
    sigaction( SIGCHLD, &sa, NULL );
}

void Parent::on_child_end()
{
    LOGE("<<on_child_end:create a new child process>>");
    create_child();
}

bool Parent::create_child( )
{
    pid_t pid;
    pid_t second_pid;
    if( (pid = fork()) < 0 )
    {
        return false;
    }
    else if( pid == 0 ) //子进程
    {
        LOGE("<<In child process,pid=%d>>", getpid() );
        Child child;
//        ProcessBase& ref_child = child;
//        child.do_work();
    }
    else if( pid > 0 )  //父进程
    {
    }

    return true;
}
