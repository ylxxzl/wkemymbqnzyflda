/*===============================================
*   文件名称：open.c
*   创 建 者：     
*   创建日期：2026年04月14日
*   描    述：
================================================*/
#include <stdio.h>
#include <sys/types.h>
 #include <sys/stat.h>
 #include <fcntl.h>
#include<unistd.h>
#include<stddef.h>
#include<string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stddef.h>
#include <string.h>

int main(int argc, char *argv[])
{ 
    int fd;
    // 打开文件：读写 + 创建
    fd = open("open.txt", O_RDWR | O_CREAT, 0664);
    if (-1 == fd) {
        perror("open fail");
        return -1;
    }
    printf("fd is %d\n", fd);

  
    char buf1[64] = "看你雷霆";
    ssize_t ret1;      ret1 = write(fd, buf1, strlen(buf1));
    if (ret1 == -1) {  // 这里必须用 ret1
        perror("write file");
        close(fd);
        return -1;
    }


    lseek(fd, 0, SEEK_SET);


    int ret;
    char buf[1024] = {0};
    ret = read(fd, buf, 15);
    if (ret == -1) {         perror("read failed");
        close(fd);
        return -1;
    }

    printf("读取到内容：%s\n", buf);

    close(fd);
    return 0;
}
