#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void apply(char *buf, int argc, char *argv[])
{
    char line[512];
    strcpy(line, buf);
    if(fork()!=0)
    {
        wait(0);
    }
    else
    {
        char *NewArgvs[argc+1];
        for(int i=1; i<argc; i++) NewArgvs[i-1]=argv[i];
        NewArgvs[argc-1]=line;
        NewArgvs[argc]=0;
        exec(argv[1], NewArgvs);
        exit(0);
    }
}

int main(int argc, char *argv[])
{ 
    char buf[512]; 
    char *p=buf; *p='\0'; 
    while(read(0, p, 1)) 
    {
        if(*p!='\n') p++;
        else
        {
            *p='\0';
            apply(buf, argc, argv);
            p=buf; *p='\0';
        }
    }
    if(p!=buf)
    {
        *p='\0';
        apply(buf, argc, argv);
    }
    exit(0);
}