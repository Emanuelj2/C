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


//retrun the size of a file in bytes
long long get_file_size(const char* filename)
{
    /*
    HANDLE file_handle = CreateFileA(
    filename,          // file name
    GENERIC_READ,      // desired access (read-only)
    0,                 // share mode (no sharing)
    NULL,              // default security attributes
    OPEN_EXISTING,     // open only if the file exists
    FILE_ATTRIBUTE_NORMAL, // normal file attributes
    NULL               // no template
);
    */
    HANDLE file_handle = CreateFileA(filename, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if(file_handle == INVALID_HANDLE_VALUE)
    {
        return -1;
    }

    LARGE_INTEGER file_size;
    GetFileSizeEX(file_handle, &file_size);
    CloseHandle(file_handle);
    return file_size.QuadPart;
}

//Upload the file
void upload_file(SOCKET socket, const char* filename)
{
    FileTransferHeader header;
    char buffer[BUFFER_SIZE];
    HANDLE file_handle;
    long long bytes_sent = 0;
    DWORD bytes_read; //DWORD is an unsigned 32-bit integer

    long long filesize = get_file_size(filename);
    if(filesize == -1)
    {
        printf("File not found %s\n", filename);
        return;
    }

    send(socket, (char*)&header, sizeof(header), 0);

    char response[10];
    recv(socket, response, 10, 0);
    if(strcmp(response, "READY") != 0)
    {
        printf("Server not ready\n");
        return;
    }

    printf("Uploading: %s (Size: %lld bytes)\n", filename, filesize);

    file_handle = CreateFileA(filename, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if(file_handle == INVALID_HANDLE_VALUE)
    {
        printf("Fail to open file\n");
        return;
    }

    //send the file data
    //while there i 
    while (ReadFile(file_handle, buffer, BUFFER_SIZE, &bytes_read, NULL) && bytes_read > 0)
    {
        send(socket, buffer, bytes_read, 0);
        bytes_sent += bytes_read;

        double progress = (double)bytes_sent / filesize * 100;
        printf("\rProgress: %.2f%% (%lld/%lld bytes)", progress, bytes_sent, filesize);
    }
    printf("\n");

    CloseHandle(file_handle);

    //wait for conformation
    memset(response, 0, sizeof(response));
    recv(socket, response, 10, 0);
    if(strcmp(response, "OK") == 0)
    {
        printf("Upload successful\n");
    }
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