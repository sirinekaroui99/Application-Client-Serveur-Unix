#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "myapp.h"
# define NMAX 20

//char *socket_path = "./socket";
char *socket_path = "\0hidden";
FILE * fp;
int c;


int nombre()
{
	int nb;
	srand(time(NULL));
	nb=1 + rand()% NMAX;
	printf("CLIENT -> Voici le nombre:%d\n",nb);
	return nb;
}

int main(int argc, char *argv[]) {

  struct sockaddr_un addr;
  char buf[100], server_reply[100];
  int fd,rc,ind;
    int res[NMAX];
    int client_actif = true;
    char ok[5];
   fp = fopen ("client.txt", "w+");
  if (argc > 1){

    socket_path='\0' + argv[1];
  } else {
    printf("CLIENT -> Veuillez spécifier un nom de socket valide en argument.\n");
    exit(1);
  }

  if ( (fd = socket(AF_LOCAL, SOCK_STREAM, 0)) == -1) {
    perror("CLIENT -> socket error");
    exit(-1);
  }
  memset(&addr, 0, sizeof(addr));
  addr.sun_family = AF_LOCAL;
  if (*socket_path == '\0') {
    *addr.sun_path = '\0';
    strncpy(addr.sun_path+1, socket_path+1, sizeof(addr.sun_path)-2);
  } else {
    strncpy(addr.sun_path, socket_path, sizeof(addr.sun_path));
  }

  if (connect(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
    perror("CLIENT -> connect error");
    exit(-1);
   bzero ((char *) buf, 100);
  		int question = nombre();
  		buf[0] = question;
  		printf("CLIENT -> Le nombre aléatoire demandé est %d, \n",question);
       
      printf("CLIENT -> Patientez pendant que le serveur traite votre message ... \n");
  		if( write(fd , buf , strlen(buf)) < 0)
  		{
  			puts("CLIENT -> Send failed");
  			exit(-1);
  		}

      if( read(fd , res , 100 ) < 0)
        {
          puts("CLIENT -> recv failed");

        }
       printf("CLIENT -> Le serveur repond par %d nombre aléatoires : \n",question);
         fprintf (fp, "Le nombre demandé par le client est :%d\nLe serveur envoi la reponse suivante :\n",question);
      for( ind = 0; ind < question ; ind ++)
      {
      printf(" CLIENT -> Nombre aléatoire n°%d : %d \n",ind+1, res[ind]);
    fprintf (fp, "Le nombre n° %d est: %d\n",ind+1,res[ind]);
      }
  close(fd);
  printf("Fin\n");
  return 0;
}
