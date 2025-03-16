#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    char buf[2];
    int p1[2], p2[2];
    pipe(p1), pipe(p2);

    if(fork()!=0)
    {
        close(p1[0]), close(p2[1]);
        
        write(p1[1], "@", 1); //如果子进程先read，父进程后write会发生什么情况？
        read(p2[0], buf, 1);
        fprintf(1, "%d: received pong\n", getpid());
        
        close(p1[1]), close(p2[0]);
        wait(0);
        exit(0);
    }
    else
    {
        close(p1[1]), close(p2[0]);
        
        read(p1[0], buf, 1);
        fprintf(1, "%d: received ping\n", getpid());
        write(p2[1], buf, 1);
        
        close(p1[0]), close(p2[1]);
        exit(0);
    }
}