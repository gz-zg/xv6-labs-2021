#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int buf[40], pos=0;

void work()
{
    int p[2]; 
    pipe(p);  //对于一个管道，如果没有任何文件描述符指向它的读端和写段的话，该管道是否就会自动关闭呢？
    for(int i=1;i<=pos;i++) write(p[1], &buf[i], sizeof(int));
    close(p[1]);

    int prime;
    if(read(p[0], &prime, sizeof(int))) fprintf(1, "prime %d\n", prime);
    if(fork()!=0)
    {
        close(p[0]);
        wait(0);
        exit(0);
    }   
    else
    {
        pos=0;
        int x;
        while(read(p[0], &x, sizeof(int)))
        {
            if(x%prime!=0)
            {
                pos++;
                buf[pos]=x;
            }
        }
        close(p[0]);
        if(pos>=1) work();
        else exit(0);
    }
}

int main(int argc, char *argv[])
{
    for(int i=2;i<=35;i++) pos++, buf[pos]=i;
    work();
    exit(0); //C语言标准要求 main函数 中必须在所有代码路径中显式返回整数值，虽然 work() 函数内部调用了 exit(0)，但编译器无法确定这一点，仍然会检查 main 的返回值， 因此，在 main 中显式返回 0 是必要的。
}