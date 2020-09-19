# Basic-Linux-Shell
Implemented some basic commands in Linux like 'cd', 'ls', 'echo', etc.
HOW TO RUN THE PROGRAM:-
*make sonu
*./sonu

COMMANDS SUPPORTED:-
*ls,ls -a,ls -l,ls -(al) 
cd
echo
pwd
pinfo
fg, bg
setenv, unsetenv
jobs, kjob
overkill, quit
CtrlC, CtrlZ

FOR EXITING TERMINAL:-
*quit

FILES DESCRIPTION:-
*file.h: Contains all the required headers and function prototypes 
*commandParse.c: Command parser
*display.c: Manages shell display
*lineParser.c: Handles line input
*ls.c: various function implementation for ls
*pinfo.c: various function implementation for pinfo
*execCmd.c: Combines everything and lists and manages all commands possible.
*main.c: combines all the files
*makefile:  compiles all the code
*argumentize.c: breaks the input string 
*pipe.c: handles piping cases
*redirection.c: handles redirection cases
