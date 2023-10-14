#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <signal.h>
#include <sys/select.h>
# define NMAX 20

int client_number = 0;
int sockfd, newsockfd;
char *socket_path = "\0hidden";
char tampon [100];
pid_t pid;
int reponse [ NMAX ];
char rep[NMAX];
int ind,i;
char port[5];



//Fermer puis spprimer la socket créee, et indiquer l'arrêt du programme
void quit(){
  printf("\n SERVER ->  Signal intercepté ...\n");
  close(newsockfd);
  remove(socket_path);
  printf("SERVER ->  Arret du serveur ...\n");
  exit(0);
}

//Lire le message reçu par un client, simuler le traitement de sa demande et lui renvoyer un message
int gererClient(struct sockaddr_un cli_addr, socklen_t clilen){

   bzero ((char *) tampon, 100);
   //lire les données provient du client
   read (newsockfd, tampon, 100);
if(tampon[0] != 0){


     printf ("SERVER ->  Client n° %i a envoyé le nombre aléatoire: %d\n", client_number, tampon[0]);
   fprintf (fp, "Question :%d\n", tampon[0]);
   printf("SERVER ->  Traitement des données ...\n");

  sleep(1); //simuler une action bloquante du serveur. Les autres clients ne devraient pas
              //être bloqués grâce au fork() et les processus lourds créés.

    for ( ind =0; ind < tampon[0] ; ind ++)
        { reponse [ ind ]= rand ()%10;
        }
   printf("SERVER ->  Fin du traitement pour le client %i\n",client_number);
   //envoi du resultat au client
    printf("VEUILLEZ PATIENTEZ SVP \n");
   write (newsockfd, reponse, 100);

   sleep(2);//simuler une action bloquante du serveur pour l'ouverture de 
		//l'interface conçu à l'affichage
//appel d ela commande system pour l'ouverture de l'executable de l'interface 
//graphique
system("./MyApp 2");

}

}

int main (int argc, char** argv){

 signal(SIGINT,quit);

 socklen_t clilen, servlen;
 //creation des adresses client et serveur
 struct sockaddr_un cli_addr;
 struct sockaddr_un serv_addr;

 fd_set active_fd_set, read_fd_set;

//creation et test sur le socket
 if ( (sockfd = socket(AF_LOCAL, SOCK_STREAM, 0)) < 0)
 {
   printf ("SERVER ->  Erreur de creation de socket\n"); exit (1);
 }

 bzero((char *)&serv_addr, sizeof(serv_addr));
 serv_addr.sun_family = AF_LOCAL;
 //on associe l'adresse du serveur à un port
 strcpy(serv_addr.sun_path, argv[0]);

 servlen = strlen(serv_addr.sun_path) + sizeof(serv_addr.sun_family);

//connexion au serveur
 if ( bind (sockfd, (struct sockaddr *) &serv_addr, servlen) < 0)
 {
   printf ("SERVER ->  Erreur de bind\n");
    exit (1);
 }

 listen(sockfd, 5);
 FD_ZERO(&active_fd_set);
 FD_SET(sockfd,&active_fd_set);

 int select_status;


 clilen = sizeof(cli_addr);
 read_fd_set = active_fd_set;

 while(1)
 {

   printf ("SERVER ->  serveur: En attente sur %s\n" ,argv[0]);
   newsockfd = accept (sockfd, (struct sockaddr *) &cli_addr, &clilen);

   pid = fork();
   client_number ++;
   switch (pid)
      {
          case -1 : printf ("SERVER ->  Erreur dans la creation du processus fils.\n");
          perror ("Erreur : ");
          break;
          case 0 : printf("SERVER ->  Arrivée d'un nouveau client (client n° %i) \n",client_number);

          gererClient(cli_addr,clilen);
          break;
          default:
          break;

      }
    }
    return 0;
}
