/*===============================================
*   文件名称：client.c
*   描    述：TCP客户端，与服务器双向通讯
================================================*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1024
#define SERVER_IP "127.0.0.1"   // 服务器IP（本机测试）
#define SERVER_PORT 8080        // 服务器端口

int main()
{
    int sock_fd;
    struct sockaddr_in server_addr;
    char send_buf[BUFFER_SIZE] = {0};
    char recv_buf[BUFFER_SIZE] = {0};

    // 1. 创建客户端套接字
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        perror("socket failed");
        return -1;
    }

    // 2. 配置服务器地址
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
        perror("invalid server ip");
        close(sock_fd);
        return -1;
    }

    // 3. 连接服务器
    if (connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect failed");
        close(sock_fd);
        return -1;
    }
    printf(" 成功连接到服务器 %s:%d\n", SERVER_IP, SERVER_PORT);
    printf(" 输入消息发送，输入 exit 断开连接\n\n");

    // 4. 循环通讯
    while (1) {
        // 清空缓冲区
        memset(send_buf, 0, BUFFER_SIZE);
        memset(recv_buf, 0, BUFFER_SIZE);

        // 从键盘输入要发送的内容
        printf("请输入：");
        fgets(send_buf, BUFFER_SIZE, stdin);

        // 去掉 fgets 自动读取的换行符
        send_buf[strcspn(send_buf, "\n")] = 0;

        // 如果输入 exit 则退出
        if (strcmp(send_buf, "exit") == 0) {
            printf("主动断开连接\n");
            break;
        }

        // 发送数据到服务器
        send(sock_fd, send_buf, strlen(send_buf), 0);

        // 接收服务器返回的数据
        int recv_len = recv(sock_fd, recv_buf, BUFFER_SIZE - 1, 0);
        if (recv_len <= 0) {
            printf("❌ 服务器断开连接\n");
            break;
        }

        // 打印服务器响应
        printf("服务器回复：%s\n", recv_buf);
    }

    // 5. 关闭套接字
    close(sock_fd);
    return 0;
}
