#include "kernel/types.h"
#include "user/user.h"
#include "kernel/stat.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

void dfs(char *path, char *file)
{
    char buf[512]; char *p; 
    int fd; 
    struct stat st;
    struct dirent de;

    fd=open(path, O_RDONLY); //open也能打开目录吗？open有什么文件是不能打开的吗？
    //如果path="./a.txt"的话path中的"."是哪个目录？
    fstat(fd, &st);
    strcpy(buf, path); p = buf + strlen(buf);
    *p = '/', p++, *p = '\0';
    
    while(read(fd, &de, sizeof(de)) == sizeof(de))
    {
        // 双重过滤：有效条目 + 非特殊目录
        if(de.inum == 0 || strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0) continue;
        // 处理正常目录项
        memmove(p, de.name, strlen(de.name)); //添加路径名称
        p[strlen(de.name)] = '\0'; //字符串结束标志
        stat(buf, &st);
        if(st.type == T_DIR) dfs(buf, file);
        else 
        {
            if(strcmp(p, file) == 0) fprintf(1, "%s\n", buf);
        }
    }
    close(fd);
    return;
}

int main(int argc, char *argv[])
{
    if(argc != 3) 
    {
        fprintf(2, "usage: find <dir> <file>\n");
        exit(1);
    }
    else
    {
        dfs(argv[1], argv[2]);
        exit(0);
    }
}