# include "serv_cli_fifo.h"
#include "handlers_serv.h"

 int main ( void ){
 /* Declarations */
 int d_question , d_reponse ;
 int ind ,sig;
 struct question question ;
 struct reponse reponse ;
printf("CLIENT -> Je suis le client %d\n",getpid());
/* ouverture des tubes nommées */
printf("CLIENT -> Ouverture des tubes par le client \n ");
 d_question = open ( QUESTION , O_WRONLY );
 d_reponse = open ( REPONSE , O_RDONLY );
 if( d_reponse == -1 || d_question == -1)
 {
 perror ("CLIENT -> Ouverture des tubes impossible \n ");
 exit (2);
 };

 /* installation des handlers */
for ( sig =1; sig < NSIG ; sig ++)
 signal (sig , fin_serveur );

/*construction et envoi d'une question */
 srand ( getpid ());
 question . pid_client = getpid ();
 question . question = 1 + rand ()% NMAX ;
printf("CLIENT -> ecriture de la question : le client %d envoi le nombre %d\n",question.pid_client,question.question);
 if( write ( d_question ,& question , sizeof ( struct question )) == -1){
 perror ("CLIENT -> erreur d'ecriture de la question ");
 exit (2);
 }
printf("CLIENT -> question envoyé\n");
 /*attente de la reponse */

 signal(SIGUSR1,hand_reveil);
close(d_question);
close(d_reponse);
system("./MyApp 2 2");
 /*lecture de la reponse */

 if( read ( d_reponse ,& reponse , sizeof ( struct reponse ) ) <= 0 )
 {
  //perror (" Probleme de lecture \n ");
  printf("CLIENT -> lecture du reponse par le client %d\n", getpid());
 exit (2);
 };
 /* envoi du signal SIGUSR1 au serveur */

 kill ( reponse . pid_serveur , SIGUSR1 );
 printf("CLIENT -> envoi signal vers le serveur %d\n",reponse.pid_serveur);

/* traitement locale de la reponse */
 printf ("CLIENT -> Reponse reçu de %d nombres aléatoires  :\n", question . question );
 for ( ind =0; ind < question . question ; ind ++)
 printf ("%d ", reponse . reponse [ ind ]);
 printf ("\n ");

 exit (0);
 }
