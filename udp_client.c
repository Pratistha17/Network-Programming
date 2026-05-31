#include <stdio.h>
#include <string.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);

    SOCKET s = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(5000);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    sendto(s, "Hello Server", 12, 0, (struct sockaddr*)&server, sizeof(server));

    char buf[1024];
    int len = sizeof(server);
    recvfrom(s, buf, 1024, 0, (struct sockaddr*)&server, &len);
    printf("Server: %s\n", buf);

    closesocket(s);
    WSACleanup();
    return 0;
}