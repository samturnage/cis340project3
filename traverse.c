
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdint.h>

/* define a directory entry in the Root directory */
struct direntry {
  char name[8];
  char ext[3];
  char attribute;
  char resv[10];	
  uint8_t timeUpdated[2];  /* updated time */
  uint8_t dateUpdated[2];  /* updated date */
  char startCluster[2];
  uint8_t size[4];
};


/* the properties of a root directory entry */
#define	SLOT_EMPTY	    0x00
#define	SLOT_DELETED	0xe5
#define	ATTR_VOLUME  	0x08		
#define	ATTR_DIRECTORY	0x10
#define	ATTR_READONLY	0x01		
#define	ATTR_HIDDEN	    0x02		
#define	ATTR_SYSTEM	    0x04		
#define	ATTR_ARCHIVE	0x20

/* a helper function to display the root directory entry */
static void displayEntry(struct direntry *de, int flag) {
  /* construct the full name for the file or directory */
  char fullName[14];
  int i, k;

  memset(fullName, 0, sizeof(fullName));

  fullName[0] = '/';
  k = 1;
  for (i = 0; i < 8; i++) {
    if (de->name[i] != ' ') {
      fullName[k++] = de->name[i];
    } else {
      break;
    }
  }
  for (i = 0; i < 3; i++) {
    if (de->ext[i] != ' ') {
      if (i == 0) {
        fullName[k++] = '.';
      }
      fullName[k++] = de->ext[i];
    } else {
      break;
    }
  }

  if (flag) { /* detailed format */
    
    char attr[5];
    int hour, minute, second;
    int year, month, day;
    uint16_t temp;
    uint32_t size;

    /* construct the attribute column */
    attr[0] = (de->attribute & ATTR_READONLY) ? 'R' : '-';
    attr[1] = (de->attribute & ATTR_ARCHIVE)  ? 'A' : '-';
    attr[2] = (de->attribute & ATTR_SYSTEM)   ? 'S' : '-';
    attr[3] = (de->attribute & ATTR_HIDDEN)   ? 'H' : '-';
    attr[4] = '\0';

    /* construct the time part */
    temp = (de->timeUpdated[1] << 8) | de->timeUpdated[0];
    second = ((temp) & 0x1f) * 2;
    minute = (temp >> 5) & 0x3f;
    hour = (temp >> 11) & 0x1f;

    /* construct the date part */
    temp = (de->dateUpdated[1] << 8) | de->dateUpdated[0];
    day = (temp) & 0x1f;
    month = (temp >> 5) & 0xf;
    year = ((temp >> 9) & 0x7f) + 1980;

    /* construct the file size */
    size = (de->size[3] << 24) | (de->size[2] << 16) |
           (de->size[1] << 8)  | (de->size[0]);

    if ((de->attribute & ATTR_DIRECTORY) != 0) {
      printf("%s\t%02d/%02d/%04d %02d:%02d:%02d\t<DIR>\t\t%s\n", 
        attr, month, day, year, hour, minute, second, fullName);
    } else {
      printf("%s\t%02d/%02d/%04d %02d:%02d:%02d\t%10d\t%s\n", 
        attr, month, day, year, hour, minute, second, size, fullName);
    }
  } else { /* short format */
    printf("%-15s", fullName);
    if ((de->attribute & ATTR_DIRECTORY) != 0) { 
      /* this is a directory */
      printf("\t\t\t<DIR>");
    }
    printf("\n");
  }

}

void traverse(int flag) {
  char num_fat;
  uint16_t size_fat;
  uint16_t num_root_dir;
  int i;
  struct direntry de;

  if (flag) { /* detailed format */
    /* print the table header */
    printf("\t*****************************\n");
    printf("\t** FILE ATTRIBUTE NOTATION **\n");
    printf("\t**                         **\n");
    printf("\t** R ------ READ ONLY FILE **\n");
    printf("\t** S ------ SYSTEM FILE    **\n");
    printf("\t** H ------ HIDDEN FILE    **\n");
    printf("\t** A ------ ARCHIVE FILE   **\n");
    printf("\t*****************************\n");
  }

  /* read the number of FATs and number of directory entries,
   * and the number of blocks for each FAT */
  lseek(3, 16, SEEK_SET);
  read(3, &num_fat, 1);
  read(3, &num_root_dir, 2);
  lseek(3, 22, SEEK_SET);
  read(3, &size_fat, 2);

  /* seek to the beginning of root directory */
  lseek(3, (1 + num_fat * size_fat) * 512, SEEK_SET);

  /* now start to read the directory entries */
  for (i = 0; i < num_root_dir; i++) {
    memset(&de, 0, sizeof(de));
    read(3, &de, sizeof(de));
    if (de.name[0] == SLOT_EMPTY) {
      /* this slot has not been used, means the end of the directory */
      break;
    }
    if ((uint8_t)de.name[0] == SLOT_DELETED) {
      /* this is a deleted slot */
      continue;
    }
    if ((de.attribute & ATTR_VOLUME) != 0) {
      continue;
    } else { /* otherwise print the entry */
      displayEntry(&de, flag);
    }
  }
}

int main(int argc, char *argv[])
{
	if(argc < 2)
	{
		traverse(0);	
	}
	else if(strcmp(argv[1],"-l")==0)
	{
		traverse(1);
	}
	else
	{
		traverse(0);
	}
	
	return 1;
}
