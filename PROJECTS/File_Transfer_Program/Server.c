#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#pragma comment(lib, "Ws2_32.lib")

#define PORT 5555
#define BUFFER_SIZE 65536
#define MAX_FILENAME 256

typedef struct {
    char command[10];
    char filename[MAX_FILENAME];
    long long filesize;
} FileTransferHeader;

void handle_client(SOCKET client_socket) {
    FileTransferHeader header;
    char buffer[BUFFER_SIZE];
    HANDLE file_handle;
    long long bytes_transferred = 0;
    int bytes_recv;

    // Receive command and filename
    bytes_recv = recv(client_socket, (char*)&header, sizeof(header), 0);
    if (bytes_recv == SOCKET_ERROR) {
        printf("recv failed: %d\n", WSAGetLastError());
        closesocket(client_socket);
        return;
    }

    printf("Command: %s, Filename: %s\n", header.command, header.filename);

    if (strcmp(header.command, "UPLOAD") == 0) {
        // Server receives file from client
        printf("Receiving file: %s (Size: %lld bytes)\n", header.filename, header.filesize);

        file_handle = CreateFileA(header.filename, GENERIC_WRITE, 0, NULL,
                                  CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (file_handle == INVALID_HANDLE_VALUE) {
            printf("Failed to create file\n");
            send(client_socket, "FAIL", 4, 0);
            closesocket(client_socket);
            return;
        }

        send(client_socket, "READY", 5, 0);

        // Receive file data
        while (bytes_transferred < header.filesize) {
            int to_recv = (int)((header.filesize - bytes_transferred > BUFFER_SIZE) ?
                               BUFFER_SIZE : (header.filesize - bytes_transferred));

            bytes_recv = recv(client_socket, buffer, to_recv, 0);
            if (bytes_recv <= 0) break;

            DWORD bytes_written;
            WriteFile(file_handle, buffer, bytes_recv, &bytes_written, NULL);
            bytes_transferred += bytes_recv;

            // Print progress
            double progress = (double)bytes_transferred / header.filesize * 100;
            printf("\rProgress: %.2f%% (%lld/%lld bytes)", progress, bytes_transferred, header.filesize);
        }
        printf("\n");

        CloseHandle(file_handle);
        printf("File received successfully\n");
        send(client_socket, "OK", 2, 0);

    } else if (strcmp(header.command, "DOWNLOAD") == 0) {
        // Server sends file to client
        printf("Sending file: %s\n", header.filename);

        file_handle = CreateFileA(header.filename, GENERIC_READ, 0, NULL,
                                  OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (file_handle == INVALID_HANDLE_VALUE) {
            printf("File not found\n");
            send(client_socket, "FAIL", 4, 0);
            closesocket(client_socket);
            return;
        }

        // Get actual file size
        LARGE_INTEGER file_size;
        GetFileSizeEx(file_handle, &file_size);
        header.filesize = file_size.QuadPart;

        // Send file size to client
        send(client_socket, (char*)&header.filesize, sizeof(header.filesize), 0);

        // Send file data
        DWORD bytes_read;
        while (ReadFile(file_handle, buffer, BUFFER_SIZE, &bytes_read, NULL) && bytes_read > 0) {
            send(client_socket, buffer, bytes_read, 0);
            bytes_transferred += bytes_read;

            double progress = (double)bytes_transferred / header.filesize * 100;
            printf("\rProgress: %.2f%% (%lld/%lld bytes)", progress, bytes_transferred, header.filesize);
        }
        printf("\n");

        CloseHandle(file_handle);
        printf("File sent successfully\n");
    }

    closesocket(client_socket);
}

int main() {
    WSADATA wsa_data;
    SOCKET listen_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    int client_addr_len = sizeof(client_addr);

    printf("Initializing Winsock...\n");
    if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0) {
        printf("WSAStartup failed: %d\n", WSAGetLastError());
        return 1;
    }

    listen_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listen_socket == INVALID_SOCKET) {
        printf("socket failed: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORT);

    if (bind(listen_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        printf("bind failed: %d\n", WSAGetLastError());
        closesocket(listen_socket);
        WSACleanup();
        return 1;
    }

    if (listen(listen_socket, SOMAXCONN) == SOCKET_ERROR) {
        printf("listen failed: %d\n", WSAGetLastError());
        closesocket(listen_socket);
        WSACleanup();
        return 1;
    }

    printf("Server listening on port %d...\n", PORT);

    while (1) {
        client_socket = accept(listen_socket, (struct sockaddr*)&client_addr, &client_addr_len);
        if (client_socket == INVALID_SOCKET) {
            printf("accept failed: %d\n", WSAGetLastError());
            continue;
        }

        printf("Client connected: %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
        handle_client(client_socket);
    }

    closesocket(listen_socket);
    WSACleanup();
    return 0;
}