#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    char buf[2];  //read(p1[0], buf, 1); 如果p1[0]中只有一个字符'@'的话，buf中的内容是{'@', 0}吗？
    int p1[2], p2[2];
    pipe(p1), pipe(p2);

    if(fork()!=0)
    {
        close(p1[0]), close(p2[1]);
        
        write(p1[1], "@", 1); //如果子进程先read，父进程后write会怎么样？
        read(p2[0], buf, 1);  //如果只往管道的写端写入1个字节，但是管道的读端要读2个字节，会怎么样？
        fprintf(1, "%d: received pong\n", getpid());
        
        close(p1[1]), close(p2[0]); //连接管道的文件描述符一定得手动关闭吗？
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