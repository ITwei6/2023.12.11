#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <cstring>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;

//信号的捕捉，除了signal外还有sigaction

// void PrintPending()
// {
//     sigset_t set;//位图变量，输出型参数

//     sigpending(&set);//将penging表带出来

//     for(int signo=1;signo<=31;signo++)
//     {
//         if(sigismember(&set,signo))//如果signo信号在set表里就为真
//         cout<<"1";
//         else
//         cout<<"0";
//     }
//     cout<<endl;

// }
// void handler(int signo)
// {
//     cout<<"catch a signal,signal number is "<<signo<<endl;
//     //1.问题：验证什么时候信号由1变成0--->在捕捉处理之前就由1变成0了
//     while(true)
//     {
//       PrintPending();
//       sleep(1);
//     }
// }
//我们可以基于信号捕捉进行进程等待
// void handler(int signo)
// {

//   //收到信号后过5秒再捕捉处理
//    pid_t rid;
//    while(rid=waitpid(-1,nullptr,0)>0)
//    {
//         cout<<"l am process :"<<getpid()<<"catch a signal is "<<signo<<endl;
//    }
   
// }
// //验证：子进程退出会发送17号信号给父进程，进程等待可以放在信号捕捉里/进程也可以不需要等待，直接显示的忽略
// int main()
// {
//     signal(17,SIG_IGN);//捕捉17号信号
//     //如果我有十个进程，都退出发送信号呢？
    
//     for(int i=0;i<10;i++)//同时创建10个子进程
//     {

//     pid_t id=fork();
//     if(id==0)//子进程
//     {
//        while(true)
//        {
//         cout<<"l am a child process "<<getpid()<<endl;
//         sleep(5);
//         break;
//        }
//        cout<<"child quit!!!"<<endl;
//        exit(0);
//        //进程退出会发送17号信号给父进程
//     }

//     sleep(1);//每个1秒创建一个子进程
//     }
//     //父进程
   
//    while(true)
//    {
//     cout<<"l am father process"<<getpid()<<endl;
//     sleep(1);
//    }
// }


//一：验证什么时候pengding表里信号标识由1变成0，执行信号捕捉方法之前，先清0
//二：验证信号处理过程中，该信号会被屏蔽，防止被嵌套调用
// int main()
// {
//    struct sigaction act,oact;
//    memset(&act,0,sizeof(act));
//    memset(&oact,0,sizeof(oact));//初始化

//    act.sa_handler=handler;//act里面的函数指针就是要捕捉使用的方法
//    sigaction(2,&act,&oact);//输入型参数和输出型参数 
//    //sigaction里的sa_mask是一个位图,用来屏蔽其他信号的
//    sigemptyset(&act.sa_mask);
//    sigaddset(&act.sa_mask,1);
//    sigaddset(&act.sa_mask,3);
//    sigaddset(&act.sa_mask,7);


//    while(true)
//    {
//     cout<<"l am a process "<<getpid()<<endl;
//     sleep(1);
//    }
// }
volatile int flag=0;

void handler(int signo)
{
    cout<<"catch a signal "<<signo<<endl;
    flag=1;
}
//三：验证volatile的作用--保证内存的可见性

int main()
{

    signal(2,handler);
    while(!flag);

    cout<<"process quit normal"<<endl;
  
}