
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

/*
show the specified FAT12 tables of the floppy
*/
int main(int argc, char *argv[])
{
    //cast to integer
    short a = -1;
    if(argc > 1)
	a = atoi(argv[1]);
    short i;
    short startSector, endSector = 0;
    char buffer[512] = {'\0'};
    //table 1 - sectors 1 to 9
    if(a == 1 || a == -1)
    {
        startSector = 1;
        endSector = 9;
        printf("\n\nFAT Table 1:\n");
    }
    //table 2 - sectors 10 to 18
    else if (a == 2)
    {
        startSector = 10;
        endSector = 18;
        printf("\n\nFAT Table 2:\n");
    }
    else
    {
	printf("\nNot a valid FAT table number");
	printf("\nPlease enter a number 1-2");
	startSector = 1;
	endSector = 0;
    }
    for(a = startSector; a <= endSector; ++a)
    {
        printf("\n\nSector : %d",a);
        printf("\n     0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F");
        lseek(3, 512*a, SEEK_SET);
        read(3, buffer, 512);
        for(i = 0; i < 512; ++i)
        {
            if(i % 16 == 0)
                printf("\n %03X ",i);
            if((unsigned char)buffer[i] == 0)
            {
                printf("FREE ");
            }
            else
            {
                printf("%03X  ", (unsigned char)buffer[i]);
            }
        }
    }
    printf("\n");
    return 0;
}
