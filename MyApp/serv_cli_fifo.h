#ifndef serv_cli_fifo
#define serv_cli_fifo

 # include <stdio.h>
 # include <stdlib.h>
 # include <unistd.h>
 # include <sys/types.h>
 # include <sys/stat.h>
 # include <sys/fcntl.h>
 # include <signal.h>

 # define NMAX 20
 # define QUESTION " fifo1 "
 # define REPONSE " fifo2 "

 struct question {
 int pid_client ;
 int question ;
 };
 struct reponse {
 int pid_serveur ;
 int reponse [ NMAX ];
 };
 # endif
