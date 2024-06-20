#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

// #pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSA startup failed!\n");
        return 1;
    }

    // 创建套接字
    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) {
        printf("Socket creation failed!\n");
        WSACleanup();
        return 2;
    }

    // 设置服务器地址
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(80); // HTTP默认端口
    serverAddr.sin_addr.s_addr = inet_addr("211.152.51.146"); // 替换为实际的服务器IP地址或域名

    // 连接服务器
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        printf("Connection failed!\n");
        closesocket(clientSocket);
        WSACleanup();
        return 3;
    }

    // 构建HTTP请求头
    char request[1024];
    sprintf(request, "GET /s.jsp?keyword=%%BB%%EC%%C4%%FD%%CD%%C1%%0A&pageNum=1 HTTP/1.1\r\nHost: www.csres.com\r\n\r\n"); // 替换为实际的请求路径和主机名

    // 发送请求
    if (send(clientSocket, request, strlen(request), 0) == SOCKET_ERROR) {
        printf("Failed to send request!\n");
        closesocket(clientSocket);
        WSACleanup();
        return 4;
    }

    // 接收响应
    char response[4096];
    int bytesRead;
    while ((bytesRead = recv(clientSocket, response, sizeof(response), 0)) > 0) {
        // 处理响应数据，例如打印到控制台
        printf("%.*s", bytesRead, response);
    }

    // 关闭套接字
    closesocket(clientSocket);
    WSACleanup();

    return 0;
}