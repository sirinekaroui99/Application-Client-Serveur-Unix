# include "serv_cli_fifo.h"
#include "handlers_serv.h"


 int main ( void )
 {
  /* Declarations */
 int d_question , d_reponse ; /* Descripteurs sur les tubes*/
 int ind , sig ;
 struct question question ;
 struct reponse reponse ;
 FILE * fp;
 fp = fopen ("fifo.txt", "w+");
 mode_t mode = S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR | S_IWGRP | S_IWOTH;

printf("SERVER -> je suis le serveur %d\n",getpid());
 /* Creation des tubes nommées */

 if( mkfifo ( QUESTION , mode ) == -1 || mkfifo ( REPONSE , mode ) == -1)
{
 perror(" Creation des tubes impossible \n ");
 exit (2);
 };

/*initialisation du générateur de nombres aléatoires */

 srand ( getpid ());
 reponse . pid_serveur = getpid ();

 /* ouverture des tubes nommées */
    printf("SERVER -> Ouverture des tubes nomées \n");
 d_question = open ( QUESTION , O_RDONLY );
 d_reponse = open ( REPONSE , O_WRONLY );

  /* installation des handlers */

 for ( sig =1; sig < NSIG ; sig ++)
 signal (sig , fin_serveur );
 //le serveur est reveillé par le signal SIGUSR1
signal(SIGUSR1,hand_reveil);

 while (1){
 /* lecture d'une question */
printf("SERVER -> lecture de la question : le client %d envoi le nombre %d\n",question.pid_client,question.question);
 if( read ( d_question ,& question , sizeof ( struct question )) <= 0 )
 {
 close ( d_question );
 d_question = open ( QUESTION , O_RDONLY );
 continue ;
 }
 /* construction de la reponse */
fprintf (fp, "Le nombre demandé par le client est :%d\nLe serveur envoi la reponse suivante :\n",question.question);
 for ( ind =0; ind < question . question ; ind ++)
 { reponse . reponse [ ind ]= rand ()%10;
  printf ("%d ", reponse . reponse [ ind ]);
  fprintf (fp, "Le nombre n° %d est: %d\n",ind+1,reponse . reponse [ ind ]);

 }
/*envoi de la reponse */
printf("SERVER -> envoi de la reponse vers client %d\n", question.pid_client);
 if( write ( d_reponse ,& reponse , sizeof ( struct reponse )) == -1)
 {
 perror ("SERVER -> erreur d'ecriture de reponse ");
 fin_serveur ( SIGUSR2 );
 }
 /* envoi du signal SIGUSR1 au client concerné */
 kill ( question . pid_client , SIGUSR1 );
 //attente de signal

 exit(0);

 }
 }
