#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#pragma commment(lib, "Ws2_32.lib")

#define PORT 5555
#define BUFFER_SIZE 65536
#define MAX_FILENAME 256

typedef struct
{
    char command[10];
    char filename[MAX_FILENAME];
    long long filesize;

}FileTransferHeader;


//GET the file size

long long get_file_size(const char* filename)
{

}