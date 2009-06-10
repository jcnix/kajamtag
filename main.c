#include <stdio.h>
#include <stdlib.h>

#define TAG_TO_INT(tag) ((tag) &0x7f) | (((tag) &0x7f00) >> 1) | (((tag)&0x7f0000)>>2) | (((tag)&0x7f000000)>>3)

int findHeader(FILE*);

int main()
{    
    FILE *musicFile;
    musicFile = fopen("test.mp3", "rb");
    
    findHeader(musicFile);
    
    char* titleHeader = malloc(4);
    fread(titleHeader, 1, 4, musicFile);

    int titleSize = 0;
    fread(&titleSize, 4, 1, musicFile);

    int titleFlags;
    fread(&titleFlags, 2, 1, musicFile);

    char* title1 = malloc(10);
    fread(title1, 1, 10, musicFile);

    char* title = malloc(10);
    fread(title, 1, 10, musicFile);
    
    printf("%s\n", titleHeader);
}

int findHeader(FILE *musicFile)
{
    char* identifier = malloc(3);
    fread(identifier, 1, 3, musicFile);
    
    int majorVer = 0;
    fread(&majorVer, 1, 1, musicFile);
    
    int minorVer = 0;
    fread(&minorVer, 1, 1, musicFile);

    char flags = 0;
    fread(&flags, 1, 1, musicFile);

    int size = 0;
    fread(&size, 4, 1, musicFile);
    size = TAG_TO_INT(htonl(size));
    
    printf("%s\n", identifier);
    printf("%d ", majorVer);
    printf("%d\n", minorVer);
    printf("%d\n", flags);
    printf("%d\n", size);
    
    return 1;
}
