#include <stdio.h>
#include <string.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);

    SOCKET s = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in server, client;
    server.sin_family = AF_INET;
    server.sin_port = htons(5000);
    server.sin_addr.s_addr = INADDR_ANY;

    bind(s, (struct sockaddr*)&server, sizeof(server));

    char buf[1024];
    int len = sizeof(client);

    printf("Server waiting...\n");

    recvfrom(s, buf, 1024, 0, (struct sockaddr*)&client, &len);
    printf("Client: %s\n", buf);

    sendto(s, "Hello Client", 12, 0, (struct sockaddr*)&client, len);

    closesocket(s);
    WSACleanup();
    return 0;
}