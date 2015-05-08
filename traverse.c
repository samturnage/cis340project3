#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>



unsigned int convertHexToDec(unsigned char fileInfo[], short highestIndex, short numBytes, unsigned int * newValue)
{
//2 hex digits make up 1 character
    short power = numBytes*2 - 1;
    *newValue = 0;
    unsigned int upperHex, lowerHex, decValue = 0;
//for loops
    short i,z;
//go backwards because we are using little endian
    for(z = highestIndex; z > (highestIndex - numBytes); --z)
    {
        decValue = (unsigned int)fileInfo[z];
        if (decValue == 0)
        {
            power = power - 2;
            continue;
        }
//upper bits
        upperHex = (decValue/16);
//lower bits
        if (decValue > 15)
            lowerHex = (decValue%16);
        else
            lowerHex = decValue;
        for (i = power; i > 0; --i)
        {
            upperHex = upperHex*16;
            if ((i - 1) > 0)
                lowerHex = lowerHex*16;
        }
        *newValue = *newValue + upperHex + lowerHex;
        power = power - 2;
    }
//return the value to the location specified
    return *newValue;
}


void PrintMoreSectorInfo(unsigned int fileInfoDec[],unsigned  char fileInfo[])
{
      //File type is displayed first
      char attributes[] = "-----";
      //get the attributes
      unsigned int attributeNum = fileInfoDec[11];
      //vars for looping
      //check for subdirectorys and archives
      if (attributeNum > 15)
      {
          if (attributeNum < 32)//Subdirectory
              attributes[0] = 'D';
          else if (attributeNum < 48)//Archive
              attributes[1] = 'A';
      }
      if ((attributeNum % 16) == 0)
      {
          attributeNum = (attributeNum % 16);
          //read only
          if ((attributeNum % 2) != 0)
              attributes[2] = 'R';
          //hidden
          if (attributeNum == 2 || attributeNum == 3 || attributeNum == 6 || attributeNum == 7 || 
                attributeNum == 10 || attributeNum == 11 || attributeNum >= 14) //if second-lowest bit is set
              attributes[3] = 'H';
          //sys file
          if ((attributeNum > 3 && attributeNum < 8) || attributeNum > 11)
              attributes[4] = 'S';
      }
      printf("%s ", attributes);
      //DATE
      unsigned int year = 1980,monthNum = 0,dayNum = 0,monthDay,yearOffset = 0;
      //YEAR
      yearOffset = (fileInfoDec[17]/2);
      yearOffset = ((yearOffset/16)*10 + yearOffset%16);
      year = year + yearOffset;
      //MONTH
      monthDay = fileInfoDec[16];
      monthDay = (monthDay - (monthDay%32));
      if (monthDay == 32 || monthDay == 96 || monthDay == 160 || monthDay == 224)monthNum++;
      if (monthDay == 64 || monthDay == 96 || monthDay == 192 || monthDay == 224)monthNum = monthNum + 2;
      if (monthDay > 128) monthNum = monthNum + 4;
      if(fileInfoDec[17] % 2 != 0) monthNum = monthNum + 8;
      //DAY
      monthDay = fileInfoDec[16];
      dayNum = (((monthDay/16)*10) + (monthDay%16));
      if (dayNum > 32)
          dayNum = dayNum % 32;
      printf("%d/%d/%d \t", monthNum, dayNum, year);
      //TIME
      unsigned int hourMin = fileInfoDec[15];
      unsigned int minSec = fileInfoDec[14];
      //HOUR
      hourMin = (hourMin/8);
      printf("%02d:", hourMin);
      //MINUTE
      hourMin = fileInfoDec[15];
      minSec = (hourMin%8)*8 + (minSec/32);
      printf("%02d:", minSec);
      //SECONDS
      minSec = fileInfoDec[14];
      minSec = (minSec%32);
      printf("%02d \t", minSec);
      //File Size
      unsigned int newDecValue = 0;
      newDecValue = convertHexToDec(fileInfo, 31, 4, &newDecValue);
      printf("%d\t", newDecValue);
      //First Sector
      newDecValue = convertHexToDec(fileInfo, 27, 2, &newDecValue);
      printf("%d\t", newDecValue);
}

int main(int argc, char *argv[])
{
      short flag = 0;
      if(argc > 1 && strcmp("-l",argv[1]) == 0)
	flag = 1;
      short sector,file,a;
      unsigned char fileInfo[32] = {'\0'};
      unsigned int fileInfoDec[32] = {'\0'};
      if (flag == 1)
      {
          printf("*****************************\n");
          printf("** FILE ATTRIBUTE NOTATION **\n");
          printf("** **\n");
          printf("** R ------ READ ONLY FILE **\n");
          printf("** S ------ SYSTEM FILE **\n");
          printf("** H ------ HIDDEN FILE **\n");
          printf("** A ------ ARCHIVE FILE **\n");
          printf("*****************************\n");
          printf("ATTRIB\tDATE\t\tTIME\t\tSIZE\tSECTOR\tNAME");
      }
      //read through root sectors
      for (sector = 19; sector < 33; ++sector)
      {
          lseek(3, 512*sector, SEEK_SET);
          
          //16 files per sector
          for (file = 0; file < 16; ++file)
          {
              lseek(3, (512*sector + file*32), SEEK_SET);
              //32 btyes for root sector
              read(3, fileInfo, 32);
              if (fileInfo[0] == '\0')
                  continue;
              //cast to integer
              for (a = 0; a < 32; ++a)
                  fileInfoDec[a] = (unsigned int)fileInfo[a];
              //ignore
              if (fileInfoDec[11] == 15)
                  continue;
              printf("\n/");
              
              //print more info if flag is checked
              if (flag == 1)
                  PrintMoreSectorInfo(fileInfoDec,fileInfo);
              //directory
              if (fileInfo[11] == 16)
              {
                  for (a = 0; a < 11; ++a)
                      printf("%c", fileInfo[a]);
                  printf("\t<DIR>");
              }
              //normal file
              else
              {
                  for (a = 0; a < 11; ++a)
                  {
                      if(fileInfo[a]!=' ')printf("%c", fileInfo[a]);
                      //print a dot for the file extension
                      if (a == 7)
                          printf(".");
                  }
              }
          }
      }
      printf("\n");
      return 0;
}
