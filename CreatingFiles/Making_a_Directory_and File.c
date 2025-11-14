#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>


//checks if the code is being compiled on windows
//if the code is compiled on windowsThis includes the Windows-specific header <direct.h>, which contains functions related to directories such as mkdir() and chdir()
#ifdef _WIN32
#include <direct.h>
#define MKDIR(dir) _mkdir(dir)   // Windows uses _mkdir()
#else
#define MKDIR(dir) mkdir(dir, 0777)
#endif


void create_dir(const char* name)
{
    if(MKDIR(name) == -1)
    {
        if(errno != EEXIST)
        {
            fprintf(stderr, "Error creating dir");
            exit(1);
        }
        else
        {
            printf("Directory %s already exist\n", name);
        }

    }
    else
    {
        printf("Directory %s created successfily");
    }
}


void create_file_in_dir(const char *dir_name,  const char* file_name)
{
    char full_path[256];
    // Use the correct path separator based on the OS (though '/' often works on Windows too)
    #ifdef _WIN32
        sprintf(full_path, "%s\\%s", dir_name, file_name);
    #else
        sprintf(full_path, "%s/%s", dir_name, file_name);
    #endif

    FILE *fptr = fopen(full_path, "w");
    if (fptr == NULL) {
        fprintf(stderr, "Error creating file %s\n", full_path);
    } else {
        fprintf(fptr, "Hello, this is content in the new file.\n");
        printf("File %s created and written to successfully\n", full_path);
        fclose(fptr);
    }

}

int main() {
    const char* folder_name = "MyNewFolder";
    const char* file_name = "data.txt";

    create_directory(folder_name);
    create_file_in_directory(folder_name, file_name);

    return 0;
}