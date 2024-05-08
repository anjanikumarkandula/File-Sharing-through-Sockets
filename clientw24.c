#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h> // Added for inet_pton
#include <unistd.h>
#include<fcntl.h>
#define MAX_MESSAGE_SIZE 255
int quit=0;
//function for w24fn size1 size 2
void fileext(int soc,char message[255]){
    int count=0;
    char copy[255];
    strcpy(copy,message);
    //printf("M:%s\n",message);
    int len=strlen(message);

    //printf("Hel\n");
    char *tokenarr[len];
    //printf("Hel\n");
    char *token=strtok(copy," ");
     while(token!=NULL){
        tokenarr[count++]=token;
        token = strtok(NULL," ");
    }
    if(count<2 && count>4){
        printf("No more than three extensions\n");
    }
    else{send(soc,message,MAX_MESSAGE_SIZE,0);
       long int bytes_to_recv = 0;
    int recstat = recv(soc, &bytes_to_recv, sizeof(long), 0);
    printf("\nbytes_to_recv: %ld\n", bytes_to_recv);
    fflush(stdout);
    if (bytes_to_recv < 1)
    {
        printf("\nNo files found or error processing tar\n");
        return;
    }
    int n;
    FILE *fp;
    char *filename = "recv_file.tar.gz";
    char buffer[512];
 
    fp = fopen(filename, "wb");
    if (fp == NULL)
    {
        perror(" - Error in opening file. Exiting . . .\n");
        exit(1);
    }
 
    int bytes_received = 0;
    // Loop while recieving the file from server
    while ((n = recv(soc, buffer, 512, 0)) > 0)
    {
        if (fwrite(buffer, sizeof(char), n, fp) != n)
        {
            perror(" - Error in writing file. Exiting . . .\n");
            exit(1);
        }
        bzero(buffer, 512);
        bytes_received += n;
        if (bytes_received >= bytes_to_recv)
        {
            printf("\nbytes recieved: %d\n", bytes_received);
            break;
        }
    }
    // close file
    fclose(fp);
    }
}
//function for w24fn size1 size 2
void filesize(int soc,char message[255]){
    int count=0;
    char copy[255];
    strcpy(copy,message);
    printf("M:%s\n",message);
    int len=strlen(message);

    printf("Hel\n");
    char *tokenarr[len];
    printf("Hel\n");
    char *token=strtok(copy," ");
     while(token!=NULL){
        tokenarr[count++]=token;
        token = strtok(NULL," ");
    }
    if(count!=3){
        printf("Invalid Arguments\n");
    }
    else{
        send(soc,message,MAX_MESSAGE_SIZE,0);
       long int bytes_to_recv = 0;
    int recstat = recv(soc, &bytes_to_recv, sizeof(long), 0);
    printf("\nbytes_to_recv: %ld\n", bytes_to_recv);
    fflush(stdout);
    if (bytes_to_recv < 1)
    {
        printf("\nNo files found or error processing tar\n");
        return;
    }
    int n;
    FILE *fp;
    char *filename = "recv_file.tar.gz";
    char buffer[512];
 
    fp = fopen(filename, "wb");
    if (fp == NULL)
    {
        perror(" - Error in opening file. Exiting . . .\n");
        exit(1);
    }
 
    int bytes_received = 0;
    // Loop while recieving the file from server
    while ((n = recv(soc, buffer, 512, 0)) > 0)
    {
        if (fwrite(buffer, sizeof(char), n, fp) != n)
        {
            perror(" - Error in writing file. Exiting . . .\n");
            exit(1);
        }
        bzero(buffer, 512);
        bytes_received += n;
        if (bytes_received >= bytes_to_recv)
        {
            printf("\nbytes recieved: %d\n", bytes_received);
            break;
        }
    }
    // close file
    fclose(fp);
    }
}

void filename(int soc,char ms[MAX_MESSAGE_SIZE]){
char buf[1024];
send(soc, ms, MAX_MESSAGE_SIZE, 0);
recv(soc,buf,sizeof(buf),0);
printf("%s\n",buf);
}
//function for dirlist -a
void dirlist_a(int soc,char ms[MAX_MESSAGE_SIZE]){
printf("Into the dirlist\n");
printf("%s\n",ms);
//int num_directories;
int num_directories;
send(soc, ms, strlen(ms), 0);
read(soc, &num_directories, sizeof(int));
printf("Number of directories: %d\n", num_directories);
for (int i = 0; i < num_directories; i++) {
        int path_len;
        char *path;

        if (read(soc, &path_len, sizeof(int)) == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }
        //printf("path length:%d\n",path_len);
        path = (char *)malloc(path_len + 1);
        if (path == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }

        if (read(soc, path, path_len) == -1) {
            perror("read");
            free(path);
            exit(EXIT_FAILURE);
        }
        path[path_len] = '\0'; // Null-terminate the string
        printf("%s\n", path);

        free(path);
    }
}
//function for dirlist -t
void dirlist_t(int soc,char ms[MAX_MESSAGE_SIZE]){
printf("Into the dirlist\n");
printf("%s\n",ms);
//int num_directories;
int num_directories;
send(soc, ms, strlen(ms), 0);
read(soc, &num_directories, sizeof(int));
printf("Number of directories: %d\n", num_directories);
for (int i = 0; i < num_directories; i++) {
        int path_len;
        char *path;

        if (read(soc, &path_len, sizeof(int)) == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }
        //printf("path length:%d\n",path_len);
        path = (char *)malloc(path_len + 1);
        if (path == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }

        if (read(soc, path, path_len) == -1) {
            perror("read");
            free(path);
            exit(EXIT_FAILURE);
        }
        path[path_len] = '\0'; // Null-terminate the string
        printf("%s\n", path);

        free(path);
    }
}

//Input validation
void check(char message[MAX_MESSAGE_SIZE],int soc){
 printf("%s\n",message);
 if(strcmp(message,"dirlist -a\n")==0){
    dirlist_a(soc,message);
   }
   else if(strcmp(message,"dirlist -t\n")==0){
    dirlist_t(soc,message);
   }
   else if(strstr(message,"w24fn")!=NULL){
    filename(soc,message);
    
   }
   else if(strstr(message,"w24fz")!=NULL){
    filesize(soc,message);
   }
   else if(strstr(message,"w24ft")!=NULL){
    fileext(soc,message);
   }
   else if(strcmp(message,"quitc\n")==0){
    quit=1;
   }
 else{
    
    printf("Invalid Input\n");
 }
   
}

void check_input(int soc) {
    char message[MAX_MESSAGE_SIZE];
    char strData[MAX_MESSAGE_SIZE];
    char serMsg[255] = "Message from the client to the server'Hello ser' ";
    send(soc, serMsg, sizeof(serMsg), 0);
    // recv(soc, strData, sizeof(strData), 0);
    // printf("Server response: %s\n", strData);
    while (1) {
        printf("Enter message to send: ");
        fgets(message, MAX_MESSAGE_SIZE, stdin);
        check(message,soc);
        // Send the message
        if(quit)
        break;
        // Receive response
        // recv(soc, strData, sizeof(strData), 0);
        // printf("Server response: %s\n", strData);
    }
    //free(serMsg);
}

int main() {
    int sockD = socket(AF_INET, SOCK_STREAM, 0);
    if (sockD == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in servAddr;
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(9697);
    inet_pton(AF_INET, "127.0.0.1", &servAddr.sin_addr);

    if (connect(sockD, (struct sockaddr*)&servAddr, sizeof(servAddr)) == -1) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    printf("Connected to the server\n");

    // Call the function to send and receive messages
    //while(1)
    char dat[255];
    send(sockD,"Hi Server",sizeof("Hi Server"),0);
     recv(sockD,dat,sizeof(dat),0);
     printf("Received from server:%s\n",dat);
     if(strcmp(dat,"9695")==0){
        close(sockD);
        printf("Connecting to mirror1\n");
        struct sockaddr_in servAddr;
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(9697);
    inet_pton(AF_INET, "127.0.0.1", &servAddr.sin_addr);

    if (connect(sockD, (struct sockaddr*)&servAddr, sizeof(servAddr)) == -1) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }
    check_input(sockD);
     }
    else if(strcmp(dat,"9693")==0){
        close(sockD);
        printf("Connecting to mirror2\n");
        struct sockaddr_in servAddr;
        servAddr.sin_family = AF_INET;
        servAddr.sin_port = htons(9697);
        inet_pton(AF_INET, "127.0.0.1", &servAddr.sin_addr);

        if (connect(sockD, (struct sockaddr*)&servAddr, sizeof(servAddr)) == -1) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
         
    }
   check_input(sockD);
     }
    else{
        check_input(sockD);
    }
    close(sockD);
    return 0;
}
