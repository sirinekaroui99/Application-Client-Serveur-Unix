#ifndef handlers_serv
#define handlers_serv

 # include <stdio.h>
 # include <stdlib.h>
 # include <unistd.h>
 # include <sys/types.h>
 # include <sys/stat.h>
 # include <sys/fcntl.h>
 # include <signal.h>

void hand_reveil ( int sig )
 {
 printf("SIGNAL DE REVEIL \n");
 return ;
 }

  void fin_serveur ( int sig )
{
 unlink ( QUESTION );
 unlink ( REPONSE );

 exit (2);
 }

 # endif
