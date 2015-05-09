Project 3 Redo

This is the project 3 redo for extra points. Thanks for the great semester.
-Samuel Turnage 2579621

Description: 
///////////////////////////////////////////////////////////
A floppy reading program that, using a shell, is able to read a local floppy file or image
and give information on its structure, files, FAT tables, and sectors.

Shell and commands work for the most part, allowing you to examine a floppy image using commands and navigating a shell

Member Contributions:
///////////////////////////////////////////////////////////
	Turnage, Samuel		s.turnage@vikes.csuohio.edu	100%
	I worked on the project 3 redo alone to try and better my personal grade
	
Compilation:
///////////////////////////////////////////////////////////
	To clean up
	$make clean
	
	To compile
	$make
	
	To run
	./fshell
	

Bugs:
///////////////////////////////////////////////////////////
	pipeline code is written in pipeline.c, but not implemented
	
Sample Run:(More than shown works, this is just a sample)
///////////////////////////////////////////////////////////	

samturnage4: ~/cis340project3 $ ./fshell
 
flop$pwd
/home/samturnage4/cis340project3
 
flop$path
 
Current Paths(seperated by a :): /bin
 
flop$path + /test
 
flop$path
 
Current Paths(seperated by a :): /bin:/test
 
flop$path - /test
 
flop$path
 
Current Paths(seperated by a :): /bin
 
flop$help
 
Commands: 
 
 help - Displays useable commands 
 cd [directory] - changes the directory
 path - edits the path
 traverse [-l] - Display the root directory contents (with the option to show more info) 
 showfat - Display content of the FAT tables 
 showsector [sector #] - Show content of the sector 
 exit - Quit out of the floppy shell 
 
 
flop$ls
README.txt  fshell  fshell.c  fshell.o  help  help.c  help.o  imagefile.img  makefile  pipeline.c  showfat  showfat.c  showfat.o  showsector  showsector.c  showsector.o  traverse  traverse.c  traverse.o
 
flop$cd ..
 
Current working directory is now ..
 
flop$ls
Applications  Backup  CIS-340-Project1  CISproject2  Documents  README.md  SystemsProgrammingProject3  Uploads  Web  cis340project3  cis340project4
 
flop$cd ./cis340project3
 
Current working directory is now ./cis340project3
 
flop$help
 
Commands: 
 
 help - Displays useable commands 
 cd [directory] - changes the directory
 path - edits the path
 traverse [-l] - Display the root directory contents (with the option to show more info) 
 showfat - Display content of the FAT tables 
 showsector [sector #] - Show content of the sector 
 exit - Quit out of the floppy shell 
 
 
flop$traverse -l
        *****************************
        ** FILE ATTRIBUTE NOTATION **
        **                         **
        ** R ------ READ ONLY FILE **
        ** S ------ SYSTEM FILE    **
        ** H ------ HIDDEN FILE    **
        ** A ------ ARCHIVE FILE   **
        *****************************
-A--    10/27/2014 13:13:10            670      /A.CLA
-A--    10/27/2014 13:13:10            763      /ALOOP1.CLA
-A--    10/27/2014 13:13:10            333      /ALOOP1.JAV
-A--    10/27/2014 13:13:10            786      /ALOOP2.CLA
-A--    10/27/2014 13:13:10            404      /ALOOP2.JAV
-A--    10/27/2014 13:13:10            786      /ALOOP3.CLA
-A--    10/27/2014 13:13:10            408      /ALOOP3.JAV
-A--    10/27/2014 13:13:10            358      /B.CLA
-A--    10/27/2014 13:13:10           1067      /CONDIT.CLA
-A--    10/27/2014 13:13:10            444      /CONDIT.JAV
-A--    10/27/2014 13:13:10            508      /D.CLA
-A--    10/27/2014 13:13:10            967      /DEMO.CLA
-A--    10/27/2014 13:13:10            648      /DEMO.JAV
----    10/27/2014 13:13:10     <DIR>           /DIR1
-A--    10/27/2014 13:13:10            630      /POLYTEST.CLA
-A--    10/27/2014 13:13:10           1063      /POLYTEST.JAV
-A--    10/27/2014 13:13:10            226      /SOME.CLA
 
flop$showsector 10
 
Sector : 10
 
     0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
 000 F0 FF FF 00 40 00 FF 6F 00 FF FF FF 09 F0 FF FF 
 010 CF 00 FF FF FF FF 0F 01 11 F0 FF FF FF FF 15 F0 
 020 FF 17 F0 FF FF FF FF FF FF FF 1D F0 FF 1F 00 02 
 030 FF FF FF 00 00 00 00 00 00 00 00 00 00 00 00 00 
 040 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
 050 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
 060 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
 070 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
 080 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
 090 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
 0A0 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
 0B0 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
 0C0 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
 0D0 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
 0E0 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
 0F0 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
 100 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
 110 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
 120 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
 130 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
 140 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
 150 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
 160 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
 170 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
 180 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
 190 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
 1A0 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
 1B0 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
 1C0 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
 1D0 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
 1E0 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
 1F0 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
 
flop$exit
samturnage4: ~/cis340project3 $  

 
