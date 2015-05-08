Description: 

A floppy reading program that, using a shell, is able to read a local floppy file or image
and give information on its structure, files, FAT tables, and sectors.

Shell and commands work for the most part, allowing you to examine a floppy image using commands and navigating a shell

Member Contributions:

	Turnage, Samuel		s.turnage@vikes.csuohio.edu	33%
	Lu, Tian		T.LU25@vikes.csuohio.edu	33%
	Sesek, Sarah		S.SESEK@vikes.csuohio.edu	34%

Compilation:
	$make clean
	$make
	./fshell

Bugs:

	fshell:
		Cannot delete the first path "/bin" without deleting the entire pathname
		cannot find binaries for ls and other commands even when they are on the path
	small formatting bugs in showfat and showsector
	traverse reading an extra file
	output redirection is very close, but files don't show the output?
	pipeline code is written in pipeline.c, but not implemented
	
Sample Run:(More than shown works, this is just a sample)
	

samturnage4: ~/SystemsProgrammingProject3 $ ./fshell
 
floppy: traverse -l
*****************************
** FILE ATTRIBUTE NOTATION **
** **
** R ------ READ ONLY FILE **
** S ------ SYSTEM FILE **
** H ------ HIDDEN FILE **
** A ------ ARCHIVE FILE **
*****************************
ATTRIB  DATE            TIME            SIZE    SECTOR  NAME
/-A--- 10/29/2002       13:13:05        670     3       A.CLA
/-A--- 10/29/2002       13:13:05        763     5       ALOOP1.CLA
/-A--- 10/29/2002       13:13:05        333     7       ALOOP1.JAV
/-A--- 10/29/2002       13:13:05        786     8       ALOOP2.CLA
/-A--- 10/29/2002       13:13:05        404     10      ALOOP2.JAV
/-A--- 10/29/2002       13:13:05        786     11      ALOOP3.CLA
/-A--- 10/29/2002       13:13:05        408     13      ALOOP3.JAV
/-A--- 10/29/2002       13:13:05        358     14      B.CLA
/-A--- 10/29/2002       13:13:05        1067    15      CONDIT.CLA
/-A--- 10/29/2002       13:13:05        444     18      CONDIT.JAV
/-A--- 10/29/2002       13:13:05        508     19      D.CLA
/-A--- 10/29/2002       13:13:05        967     20      DEMO.CLA
/-A--- 10/29/2002       13:13:05        648     22      DEMO.JAV
/D---- 10/29/2002       13:13:05        0       24      DIR1            <DIR>
/-A--- 10/29/2002       13:13:05        630     28      POLYTEST.CLA
/-A--- 10/29/2002       13:13:05        1063    30      POLYTEST.JAV
/-A--- 10/29/2002       13:13:05        226     33      SOME.CLA
/-A--- 10/29/2002       13:13:05        278     34      OME~1.JAV
 
floppy: showsector 10
 
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
 
floppy: help
 
Commands: 
 
 help - Displays useable commands 
 traverse [-l] - Display the root directory contents (with the option to show more info) 
 showfat - Display content of the FAT tables 
 showsector [sector #] - Show content of the sector 
 exit - Quit out of the floppy shell 
 
 
floppy: cd
 
Current working directory is now (null)
 
floppy: exit