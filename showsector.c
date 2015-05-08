#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
//show a specified sector of the floppy

int main(int argc,const char **argv)
{
    int sectorNum = 1;
    if(argc > 1)
    	sectorNum = atoi(argv[1]);
    //checks for valid floppy sector
    if(sectorNum >= 0 && sectorNum < 2880)
    {
        printf("\nSector : %d\n", sectorNum);
        char buffer[512] = {'\0'};
        lseek(3, 512*sectorNum, SEEK_SET);
        read(3, buffer, 512);
        printf("\n     0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F");
        int i;
        for(i = 0; i < 512; ++i)
        {
            //print row
            if(i % 16 == 0)
            {
                printf("\n %03X ", i);
            }
            printf("%02X ", (unsigned char)buffer[i]);
        }
    }
    else
    {
        printf("\nSector must be between 0 and 2879\n");
    }
    printf("\n");
    return 0;
}


