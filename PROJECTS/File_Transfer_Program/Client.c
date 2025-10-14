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

long long get_file_size(const char* filename) {
    HANDLE file_handle = CreateFileA(filename, GENERIC_READ, 0, NULL,
                                      OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (file_handle == INVALID_HANDLE_VALUE) return -1;

    LARGE_INTEGER file_size;
    GetFileSizeEx(file_handle, &file_size);
    CloseHandle(file_handle);
    return file_size.QuadPart;
}

void upload_file(SOCKET socket, const char* filename) {
    FileTransferHeader header;
    char buffer[BUFFER_SIZE];
    HANDLE file_handle;
    long long bytes_sent = 0;
    DWORD bytes_read;

    long long filesize = get_file_size(filename);
    if (filesize == -1) {
        printf("File not found: %s\n", filename);
        return;
    }

    strcpy_s(header.command, sizeof(header.command), "UPLOAD");
    strcpy_s(header.filename, sizeof(header.filename), filename);
    header.filesize = filesize;

    // Send header
    send(socket, (char*)&header, sizeof(header), 0);

    // Wait for server ready
    char response[10];
    recv(socket, response, 10, 0);
    if (strcmp(response, "READY") != 0) {
        printf("Server not ready\n");
        return;
    }

    printf("Uploading: %s (Size: %lld bytes)\n", filename, filesize);

    file_handle = CreateFileA(filename, GENERIC_READ, 0, NULL,
                              OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (file_handle == INVALID_HANDLE_VALUE) {
        printf("Failed to open file\n");
        return;
    }

    // Send file data
    while (ReadFile(file_handle, buffer, BUFFER_SIZE, &bytes_read, NULL) && bytes_read > 0) {
        send(socket, buffer, bytes_read, 0);
        bytes_sent += bytes_read;

        double progress = (double)bytes_sent / filesize * 100;
        printf("\rProgress: %.2f%% (%lld/%lld bytes)", progress, bytes_sent, filesize);
    }
    printf("\n");

    CloseHandle(file_handle);

    // Wait for confirmation
    memset(response, 0, sizeof(response));
    recv(socket, response, 10, 0);
    if (strcmp(response, "OK") == 0) {
        printf("Upload successful\n");
    }
}

void download_file(SOCKET socket, const char* filename) {
    FileTransferHeader header;
    char buffer[BUFFER_SIZE];
    HANDLE file_handle;
    long long bytes_received = 0;
    int bytes_recv;

    strcpy_s(header.command, sizeof(header.command), "DOWNLOAD");
    strcpy_s(header.filename, sizeof(header.filename), filename);
    header.filesize = 0;

    // Send request
    send(socket, (char*)&header, sizeof(header), 0);

    // Receive file size
    long long filesize;
    bytes_recv = recv(socket, (char*)&filesize, sizeof(filesize), 0);
    if (bytes_recv <= 0 || filesize <= 0) {
        printf("File not found on server\n");
        return;
    }

    printf("Downloading: %s (Size: %lld bytes)\n", filename, filesize);

    file_handle = CreateFileA(filename, GENERIC_WRITE, 0, NULL,
                              CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (file_handle == INVALID_HANDLE_VALUE) {
        printf("Failed to create file\n");
        return;
    }

    // Receive file data
    while (bytes_received < filesize) {
        int to_recv = (int)((filesize - bytes_received > BUFFER_SIZE) ?
                           BUFFER_SIZE : (filesize - bytes_received));

        bytes_recv = recv(socket, buffer, to_recv, 0);
        if (bytes_recv <= 0) break;

        DWORD bytes_written;
        WriteFile(file_handle, buffer, bytes_recv, &bytes_written, NULL);
        bytes_received += bytes_recv;

        double progress = (double)bytes_received / filesize * 100;
        printf("\rProgress: %.2f%% (%lld/%lld bytes)", progress, bytes_received, filesize);
    }
    printf("\n");

    CloseHandle(file_handle);
    printf("Download successful\n");
}

int main() {
    WSADATA wsa_data;
    SOCKET connect_socket;
    struct sockaddr_in server_addr;
    char command[20], filename[MAX_FILENAME], server_ip[20];

    printf("Initializing Winsock...\n");
    if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0) {
        printf("WSAStartup failed: %d\n", WSAGetLastError());
        return 1;
    }

    printf("Enter server IP (default 127.0.0.1): ");
    fgets(server_ip, sizeof(server_ip), stdin);
    server_ip[strcspn(server_ip, "\n")] = 0;
    if (strlen(server_ip) == 0) strcpy_s(server_ip, sizeof(server_ip), "127.0.0.1");

    connect_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (connect_socket == INVALID_SOCKET) {
        printf("socket failed: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(server_ip);
    server_addr.sin_port = htons(PORT);

    printf("Connecting to server %s:%d...\n", server_ip, PORT);
    if (connect(connect_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        printf("connect failed: %d\n", WSAGetLastError());
        closesocket(connect_socket);
        WSACleanup();
        return 1;
    }

    printf("Connected to server\n\n");

    while (1) {
        printf("\nCommands: UPLOAD <filename> | DOWNLOAD <filename> | EXIT\n");
        printf(">> ");

        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0;

        if (sscanf_s(command, "%s %s", command, (unsigned)sizeof(command), filename, (unsigned)sizeof(filename)) < 1) {
            continue;
        }

        if (strcmp(command, "EXIT") == 0) {
            break;
        } else if (strcmp(command, "UPLOAD") == 0) {
            upload_file(connect_socket, filename);
        } else if (strcmp(command, "DOWNLOAD") == 0) {
            download_file(connect_socket, filename);
        } else {
            printf("Unknown command\n");
        }
    }

    closesocket(connect_socket);
    WSACleanup();
    printf("Disconnected\n");
    return 0;
}
/*
Examples of What Uses a HANDLE
Resource	How You Get It	What You Do With It	How You Release It
File	CreateFile()	ReadFile(), WriteFile()	CloseHandle()
Process	CreateProcess()	WaitForSingleObject(), TerminateProcess()	CloseHandle()
Thread	CreateThread()	WaitForSingleObject()	CloseHandle()
Mutex/Event/Semaphore	CreateMutex(), CreateEvent()	WaitForSingleObject(), SetEvent()	CloseHandle()


revc(): Receive data from a connected socket.
*/