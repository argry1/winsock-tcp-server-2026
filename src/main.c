#include <winsock2.h>
#include <stdio.h>
#include <string.h>

#pragma comment(lib, "ws2_32.lib")


int main(){
    WSADATA wsadata;
    int res = WSAStartup(MAKEWORD(2, 2), &wsadata);
    if (res != 0){
        return 1;
    }
    SOCKET server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server == INVALID_SOCKET){
        WSACleanup();
        return 1;
    }

    struct sockaddr_in addr; // sockaddr неисп. нет полей для порта и ip
    {
        memset(&addr, 0, sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = INADDR_ANY;
        addr.sin_port = htons(8080);
        //addr.sin_zero(8байт) - для совпадения с размером sockaddr_in - sockaddr со старой версией
    };

    if (bind(server, (struct sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR){
        closesocket(server);
        WSACleanup();
        return 1;
    }
    if (listen(server, SOMAXCONN) == SOCKET_ERROR){
        //listen(socket, число значение очереди - (SOMAXCONN - на усмотрение ОС))
        closesocket(server);
        WSACleanup();
        return 1;
    }

    struct sockaddr_in client_addr;
    int client_len = sizeof(client_addr);
    SOCKET client = accept(server, (struct sockaddr*)&client_addr, &client_len);
    if (client == INVALID_SOCKET){
        closesocket(server);
        WSACleanup();
        return 1;
    }

    char buffer[4096];
    int bytes = recv(client, buffer, sizeof(buffer) - 1, 0);
    if (bytes > 0){
        buffer[bytes] = '\0';
        send(client, buffer, bytes, 0);
    }
    else if (bytes == 0) {
        printf("Client closed connection\n");
    }

    closesocket(client);
    closesocket(server);
    WSACleanup();
    return 0;
}
