#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>



#pragma coment(lib, "Ws2_32.lib")

#define PORT 5555
#define BUFFER_SIZE 65536
#define MAX_FILENAME 256

typedef struct
{
    char command[10];
    char filename[MAX_FILENAME];
    long long filesize;

}FileTransferHeader;

void handle_client(SOCKET client_socket)
{
    FileTransferHeader header;
    char buffer[BUFFER_SIZE];
    HANDLE file_handle;
    long long bytes_transferred = 0;
    int bytes_recv;

    bytes_recv = recv(client_socket, (char*)&header, sizeof(header), 0);
    if(bytes_recv == SOCKET_ERROR)
    {
        printf("recv failed: %d\n", WSAGetLastError());
        closesocket(client_socket);
        return;
    }

    printf("Command: %s, Filename: %s\n", header.command, header.filename);

    if(strcmp(header.command, "UPLOAD") == 0)
    {
        printf("Recieving file %s (Size %lld bytes)\n", header.filename, header.filesize);

        file_handle = CreateFileA(header.filename, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

        if(file_handle == INVALID_HANDLE_VALUE)
        {
            printf("Failed to create file\n");
            send(client_socket, "FAIL", 4, 0);
            closesocket(client_socket); //close the client socket
            return;
        }

        send(closesocket, "READY", 5, 0);

        while(bytes_transferred < header.filesize)
        {
            int to_recv = (int)((header.filesize - bytes_transferred) > BUFFER_SIZE)? BUFFER_SIZE : (header.filesize - bytes_transferred);

            bytes_recv = recv(client_socket, buffer, to_recv, 0);

            if(bytes_recv <= 0)
            {
                break;
            }

            DWORD bytes_written;

            WriteFile(file_handle, buffer, bytes_recv, &bytes_written, NULL);
            bytes_transferred += bytes_recv;

            //print the progress
            double progress = (double)bytes_transferred/ header.filesize * 100;
            printf("\rProgress: %.2f%% (%lld/%lld bytes)", progress, bytes_transferred, header.filesize);
        }
        printf("\n");

        CloseHandle(file_handle);
        printf("File received successfully\n");
        send(client_socket, "OK", 2, 0);
    }
    else if(strcmp(header.command, "DOWNLOAD") == 0)
    {
        printf("Downloading file %s (Size %lld bytes)\n", header.filename, header.filesize);

        file_handle = CreateFileA(header.filename, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

        if(file_handle == INVALID_HANDLE_VALUE)
        {
            printf("Faild to download file.\n");
            send(client_socket, "FAIL", 4, 0);
            closesocket(client_socket); //close the client socket
            return;
        }

        // Get actual file size
        LARGE_INTEGER file_size;
        GetFileSizeEx(file_handle, &file_size);
        header.filesize = file_size.QuadPart;

        
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
    closesocket(client_socket); //close the client socket
}

int main()
{
    return 0;
}