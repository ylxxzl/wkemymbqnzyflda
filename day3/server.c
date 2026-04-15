/*===============================================
*   文件名称：server.c
*   描    述：TCP服务器 - 支持手动自由回复客户端
================================================*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1024
#define PORT 8080

int main(int argc, char *argv[])
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    char send_buf[BUFFER_SIZE] = {0};

    // 1. 创建套接字
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket fail");
        return -1;
    }

    // 2. 绑定地址
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, addrlen) < 0) {
        perror("bind fail");
        close(server_fd);
        return -1;
    }

    // 3. 监听
    if (listen(server_fd, 3) < 0) {
        perror("listen fail");
        close(server_fd);
        return -1;
    }
    printf("服务器启动成功，等待客户端连接...\n");

    // 4. 等待客户端连接
    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
    if (new_socket < 0) {
        perror("accept fail");
        close(server_fd);
        return -1;
    }
    printf("客户端已连接：%s:%d\n\n", inet_ntoa(address.sin_addr), ntohs(address.sin_port));

    // 5. 聊天循环
    while(1)
    {
        // 清空缓冲区
        memset(buffer, 0, BUFFER_SIZE);
        memset(send_buf, 0, BUFFER_SIZE);

        // 接收客户端消息
        int len = recv(new_socket, buffer, BUFFER_SIZE-1, 0);
        if(len <= 0) {
            printf("客户端断开连接\n");
            break;
        }
        printf("【客户端】：%s\n", buffer);

        // 输入服务器要回复的内容
        printf("【服务器回复】：");
        fgets(send_buf, BUFFER_SIZE, stdin);
        send_buf[strcspn(send_buf, "\n")] = 0;  // 去掉换行

        // 发送给客户端
        send(new_socket, send_buf, strlen(send_buf), 0);

        // 输入exit断开
        if(strcmp(send_buf, "exit") == 0) {
            printf("服务器主动断开连接\n");
            break;
        }
    }

    close(new_socket);
    close(server_fd);
    return 0;
}
