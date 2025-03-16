#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    if(argc == 2)
    {
        sleep(atoi(argv[1]));
        exit(0);  //xv6中的程序为什么需要确保 main函数 调用 exit() 退出程序？
    }
    else 
    {
        fprintf(2, "usage: sleep number\n");
        exit(1);
    }
}