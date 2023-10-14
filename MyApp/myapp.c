//My application
// gcc -o MyApp myapp.c -Wall `pkg-config --cflags --libs gtk+-3.0` -export-dynamic
//Libraries
#include <gtk/gtk.h> // GTK Library
#include <stdio.h> // c io library
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "myapp.h"

//variables
GtkWidget *window, *window_socket,*window_res_socket,*window_res_fifo;

GtkLabel *socket_res,*tube_res;
FILE *fp;
int i =0;
//main function
int main(int argc, char *argv[])
{	
	GtkBuilder *builder;
	gtk_init(&argc,&argv);
	builder = gtk_builder_new();
	gtk_builder_add_from_file(builder, "Linux_App.glade",NULL);

	window = GTK_WIDGET(gtk_builder_get_object(builder,"MyWindow"));
	window_socket = GTK_WIDGET(gtk_builder_get_object(builder,"window_socket"));
	window_res_socket = GTK_WIDGET(gtk_builder_get_object(builder,"window_res_socket"));
	window_res_fifo = GTK_WIDGET(gtk_builder_get_object(builder,"window_res_fifo"));
	socket_res = GTK_LABEL(gtk_builder_get_object(builder,"socket_res"));
	tube_res = GTK_LABEL(gtk_builder_get_object(builder,"tube_res"));
	

	gtk_builder_connect_signals(builder,NULL);
	g_object_unref(builder);
	
	if(argc == 1) {
	
	gtk_widget_show_all(window);
	}else if(argc == 2){
	gtk_widget_show_all(window_res_socket);
	}else{
	gtk_widget_show_all(window_res_fifo);
	}
	
	gtk_main();
	
	return 0;
	
}
void retour_menu(){
	gtk_widget_destroy(window_res_socket);
	gtk_widget_destroy(window_res_fifo);
	gtk_widget_show_all(window);
}
void exit_app()
{
	printf("Exit app \n");
	gtk_main_quit();
}


void afficher_socket(){
char string[100];
char s[500];

    FILE *fp;
    fp=fopen("client.txt","r");
    
	while(fgets(string,100,fp) != NULL){
    printf(" %s",string);
strcat(s,string);
}
gtk_label_set_text(socket_res,s);
//creation de bouton

 fclose(fp);
}




void button_socket_clicked()
{	char* argv[50];
	char cmd[]="gnome-terminal";
	
	pid_t pid;
	 pid = fork();
	
	argv[0]="1208";
strcat(cmd," -- ");
strcat(cmd,"./client ");
strcat(cmd,argv[0]);
strcat(cmd," &");
printf("execution du serveur \n");
	if (pid == 0) {
        printf("printed from child process - %d\n", getpid());
	
	printf("execution du client \n");
	system(cmd);


        exit(EXIT_SUCCESS);
    } else {
        printf("printed from parent process - %d\n", getpid());
	execv("./server",argv);
	
    }
}

void afficher_tube(){
char string[100];
char s[500];
 
FILE *fp;
fp=fopen("fifo.txt","r");
    
while(fgets(string,100,fp) != NULL){
  printf(" %s",string);
strcat(s,string);
}

gtk_label_set_text(tube_res,s);

printf("exit declanché");

 fclose(fp);

}

void button_tube_clicked()
{
	char* argv[50];
	
	pid_t pid;
	 pid = fork();
	gtk_widget_destroy(window);
	printf("execution du serveur \n");
	if (pid == 0) {
        printf("printed from child process - %d\n", getpid());
	
	printf("execution du client \n");
	
	system("gnome-terminal -- bash -c \"./client_fifo; exec bash\" &");
        exit(EXIT_SUCCESS);
    } else {
        printf("printed from parent process - %d\n", getpid());
	
	execv("./server_fifo",argv);
    }}













