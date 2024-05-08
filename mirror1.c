#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include<ftw.h>
#include<unistd.h>
#include<time.h>
#include <fcntl.h>
char *path="/home/kandula/Desktop";
#define MAX_MESSAGE_SIZE 255

int num_directories = 0; // Number of directories found
int max_directories = 0; 
int num_directories_t = 0; // Number of directories found
int max_directories_t = 0;
int file_found=0;
char *targetfile=NULL;
char **directories = NULL;
char **directories_time=NULL;
char file_details[10240];
time_t *creation_times = NULL;
long int size1=0;
long int size2=0;
int sock=0;
int no_file=0;
char *extension=NULL;
//for zippinng file 
void zipper(const char *file_path){
    printf("Zipper\n");
    printf("path at zipper is %s\n",file_path);
    char *f_path = malloc(200);

    strcpy(f_path, file_path);

    strcpy(f_path, file_path);
    char *args[] = {"tar", "-rf", "temp.tar.gz", (char *)file_path, NULL};
    printf("tar\n");
    printf("mall\n");
    int pid=fork();
  if(pid==0){
    if (execvp("tar", args) == -1) {
        perror("execvp");
        exit(EXIT_FAILURE);
    }
  }
  else{
    wait(NULL);
  }

}
//for zippinng file based on date before
void zipbydb(int soc,char message[255]){
     int len=strlen(message);
    char *tokenarr[len];
    //printf("Hel\n");
    char copy[255];
    strcpy(copy,message);
    //printf("Hel\n");
    int count=0;
    char *token=strtok(message," ");
     while(token!=NULL){
        printf("token:%s\n",token);
        tokenarr[count++]=token;
        token = strtok(NULL," ");
    }
    for(int i=1;i<count;i++){
         int flag = FTW_PHYS;
     printf("Before tracer\n");
     extension=tokenarr[i];
     printf("Extension:%s\n",extension);
    int traverse=nftw(path,ext_finder,64,flag);
    }
    // for (int i = 0; i < count; i++) {
    //     free(tokenarr[i]);
    // }
    FILE *fp;
    // char *filename = "/home/gideon/file.tar.gz";
    char buffer[512];
    int n=0;
    fp = fopen("temp.tar.gz", "rb");
    struct stat filestat;
    stat("temp.tar.gz", &filestat);
    if (send(soc, &filestat.st_size, sizeof(long), 0) <= 0)
    {
        printf("\nError sending byte length to client");
        fflush(stdout);
        return -1;
    }
    int bytes_sent = 0;
    while ((n = fread(buffer, sizeof(char), 512, fp)) > 0)
    {
        if (send(soc, buffer, n, 0) == -1)
        {
            printf("\nError sending the file");
            return -1;
        }
        bzero(buffer, 512);
        bytes_sent += n;
        if (bytes_sent >= filestat.st_size)
        {
            printf("\nbytes sent: %d", bytes_sent);
            break;
        }
    }
    // close file
    fclose(fp);

    
}
//for zippinng file based on date after
void zipbyda(int soc,char message[255]){
     int len=strlen(message);
    char *tokenarr[len];
    //printf("Hel\n");
    char copy[255];
    strcpy(copy,message);
    //printf("Hel\n");
    int count=0;
    char *token=strtok(message," ");
     while(token!=NULL){
        printf("token:%s\n",token);
        tokenarr[count++]=token;
        token = strtok(NULL," ");
    }
    for(int i=1;i<count;i++){
         int flag = FTW_PHYS;
     printf("Before tracer\n");
     extension=tokenarr[i];
     printf("Extension:%s\n",extension);
    int traverse=nftw(path,ext_finder,64,flag);
    }
    // for (int i = 0; i < count; i++) {
    //     free(tokenarr[i]);
    // }
    FILE *fp;
    // char *filename = "/home/gideon/file.tar.gz";
    char buffer[512];
    int n=0;
    fp = fopen("temp.tar.gz", "rb");
    struct stat filestat;
    stat("temp.tar.gz", &filestat);
    if (send(soc, &filestat.st_size, sizeof(long), 0) <= 0)
    {
        printf("\nError sending byte length to client");
        fflush(stdout);
        return -1;
    }
    int bytes_sent = 0;
    while ((n = fread(buffer, sizeof(char), 512, fp)) > 0)
    {
        if (send(soc, buffer, n, 0) == -1)
        {
            printf("\nError sending the file");
            return -1;
        }
        bzero(buffer, 512);
        bytes_sent += n;
        if (bytes_sent >= filestat.st_size)
        {
            printf("\nbytes sent: %d", bytes_sent);
            break;
        }
    }
    // close file
    fclose(fp);

    
}

int ext_finder(const char *file_path, struct stat *found_file_status, int flag, struct FTW *found_file_details) {
    printf("In to finder\n");
    char *samp=file_path+found_file_details->base; 
    char *ext=strchr(samp,'.');
     printf("ext:%s\n",ext);
     printf("extension:%s\n",extension);
    //printf("size1=%d,size2=%d\n",size1,size2);
    if(flag==FTW_F && ext!=NULL && strcmp(ext+1,extension)==0){
        // printf("found path:%s\n",file_path);
        // printf("found file is %s\n",file_path+found_file_details->base);
        //  printf("found file size is %d\n",found_file_status->st_size);
        // printf("Second condition\n");

        zipper(file_path);
    }
    else{
        no_file=1;
        printf("No file\n");
    }
    return 0;
}

void zipbyext(int soc,char message[255]){
     int len=strlen(message);
    char *tokenarr[len];
    //printf("Hel\n");
    char copy[255];
    strcpy(copy,message);
    //printf("Hel\n");
    int count=0;
    char *token=strtok(message," ");
     while(token!=NULL){
        printf("token:%s\n",token);
        tokenarr[count++]=token;
        token = strtok(NULL," ");
    }
    for(int i=1;i<count;i++){
         int flag = FTW_PHYS;
     printf("Before tracer\n");
     extension=tokenarr[i];
     printf("Extension:%s\n",extension);
    int traverse=nftw(path,ext_finder,64,flag);
    }
    // for (int i = 0; i < count; i++) {
    //     free(tokenarr[i]);
    // }
    FILE *fp;
    // char *filename = "/home/gideon/file.tar.gz";
    char buffer[512];
    int n=0;
    fp = fopen("temp.tar.gz", "rb");
    struct stat filestat;
    stat("temp.tar.gz", &filestat);
    if (send(soc, &filestat.st_size, sizeof(long), 0) <= 0)
    {
        printf("\nError sending byte length to client");
        fflush(stdout);
        return -1;
    }
    int bytes_sent = 0;
    while ((n = fread(buffer, sizeof(char), 512, fp)) > 0)
    {
        if (send(soc, buffer, n, 0) == -1)
        {
            printf("\nError sending the file");
            return -1;
        }
        bzero(buffer, 512);
        bytes_sent += n;
        if (bytes_sent >= filestat.st_size)
        {
            printf("\nbytes sent: %d", bytes_sent);
            break;
        }
    }
    // close file
    fclose(fp);

    
}


int file_finder(const char *file_path, struct stat *found_file_status, int flag, struct FTW *found_file_details) {
   
    printf("size1=%d,size2=%d\n",size1,size2);
    if(flag==FTW_F && found_file_status->st_size>=size1 && found_file_status->st_size<=size2){
        printf("found path:%s\n",file_path);
        printf("found file is %s\n",file_path+found_file_details->base);
         printf("found file size is %d\n",found_file_status->st_size);
        printf("Second condition\n");

        zipper(file_path);
    }
    else{
        no_file=1;
        printf("No file\n");
    }
    return 0;
}


int file_tracer(const char *file_path, struct stat *found_file_status, int flag, struct FTW *found_file_details) {
    printf("tracer\n");
    
    if(flag==FTW_F){
        printf("%s\n",file_path);
        char*  filename=file_path+found_file_details->base;
        targetfile[strlen(targetfile)-1]='\0';
         char *com=(char *)malloc(strlen(file_path+found_file_details->base)+1);
         strcpy(com,file_path+found_file_details->base);
        if(strcmp(filename,targetfile)==0){
        printf("%s\n",file_path+found_file_details->base);
        file_found=1;
            printf("Hello\n");
            snprintf(file_details, 1024, "File: %s\n"
                                   "Size: %lld bytes\n"
                                   "Last modified: %s"
                                   "Permissions: %o\n",
             filename,
             (long long)found_file_status->st_size,
             ctime(&found_file_status->st_mtime),
             found_file_status->st_mode);
            // Do something with file_details
            
            free(com);
      //return 1;
    }
}
}

void zipbysize(int soc,char message[255]){
    
    int len=strlen(message);
    char *tokenarr[len];
    //printf("Hel\n");
    char copy[255];
    strcpy(copy,message);
    //printf("Hel\n");
    int count=0;
    char *token=strtok(message," ");
     while(token!=NULL){
        printf("token:%s\n",token);
        tokenarr[count++]=token;
        token = strtok(NULL," ");
    }
    printf("Hel\n");
    printf("%s",tokenarr[count-1]);
    printf("Token count: %d\n", count);
    printf("Token before size2 conversion: %s\n", tokenarr[count - 1]);
    printf("Token before size1 conversion: %s\n", tokenarr[count - 2]);

    size1=atoi(tokenarr[count-2]);
    size2=atoi(tokenarr[count-1]);

    printf("size1: %d\n", size1);
    printf("size2: %d\n", size2); 
     int flag = FTW_PHYS;
     printf("Before tracer\n");
    int traverse=nftw(path,file_finder,64,flag);
    FILE *fp;
    // char *filename = "/home/gideon/file.tar.gz";
    char buffer[512];
    int n=0;
    fp = fopen("temp.tar.gz", "rb");
    struct stat filestat;
    stat("temp.tar.gz", &filestat);
    if (send(soc, &filestat.st_size, sizeof(long), 0) <= 0)
    {
        printf("\nError sending byte length to client");
        fflush(stdout);
        return -1;
    }
    int bytes_sent = 0;
    while ((n = fread(buffer, sizeof(char), 512, fp)) > 0)
    {
        if (send(soc, buffer, n, 0) == -1)
        {
            printf("\nError sending the file");
            return -1;
        }
        bzero(buffer, 512);
        bytes_sent += n;
        if (bytes_sent >= filestat.st_size)
        {
            printf("\nbytes sent: %d", bytes_sent);
            break;
        }
    }
    // close file
    fclose(fp);
}
//for traversing directory
void searchfile(int soc,char *request){
    int flag = FTW_PHYS;
    printf("token1\n");
    printf("token\n");
    printf("%s:request\n",request);
    int len=strlen(request);
    int i=0;
    char *tokenarr[len];
    char *token=strtok(request," ");
    while(token!=NULL && i<len){
        tokenarr[i++]=token;
        token = strtok(NULL," ");
    }
    printf("token2\n");
    targetfile=(char *)malloc(strlen(tokenarr[1]));
    strcpy(targetfile,tokenarr[1]);
    printf("target:%s\n",targetfile);
    int traverse=nftw(path,file_tracer,64,flag);
    char ms[255]="file found";
    if(file_found){
       printf("file found\n");
       send(soc, file_details, 1024, 0);
       file_found=0;
    }
    else{
      printf("file not found\n");
      send(soc, "File not Found", sizeof("File not Found"), 0);
    }
}

//for sorting directories based on time of creation
void insertion_sort() {
    for (int i = 1; i < num_directories_t; ++i) {
        char *temp_dir = directories_time[i];
        time_t temp_time = creation_times[i];
        int j = i - 1;
        while (j >= 0 && creation_times[j] > temp_time) {
            directories_time[j + 1] = directories_time[j];
            creation_times[j + 1] = creation_times[j];
            --j;
        }
        directories_time[j + 1] = temp_dir;
        creation_times[j + 1] = temp_time;
    }
}

void heapify(char **arr, int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n && strcmp(arr[l], arr[largest]) > 0)
        largest = l;
    if (r < n && strcmp(arr[r], arr[largest]) > 0)
        largest = r;
    if (largest != i) {
        char *temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}
//for sorting directories based on alphabets
void heap_sort(char **arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        char *temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}

int directory_finder_with_time(const char *file_path, const struct stat *found_file_status, int flag, struct FTW *found_file_details) {
    if (flag == FTW_D) {
        // Increase capacity by 10
        if (num_directories_t >= max_directories_t) {
            max_directories_t += 10;
            directories_time = realloc(directories_time, max_directories_t * sizeof(char *));
            creation_times = realloc(creation_times, max_directories_t * sizeof(time_t));
            if (directories_time == NULL || creation_times == NULL) {
                perror("realloc");
                exit(EXIT_FAILURE);
            }
        }

        // Store directory path and creation time
        directories_time[num_directories_t] = strdup(file_path);
        if (directories_time[num_directories_t] == NULL) {
            perror("strdup");
            exit(EXIT_FAILURE);
        }
        creation_times[num_directories_t] = found_file_status->st_ctime;
        num_directories_t++; // Increment number of directories
    }
    return 0; // Continue
}


int directory_finder(const char *file_path, const struct stat *found_file_status, int flag, struct FTW *found_file_details){
    if(flag==FTW_D){
      max_directories += 10; // Increase capacity by 10
            directories = realloc(directories, max_directories * sizeof(char *));
            if (directories == NULL) {
                perror("realloc");
                exit(EXIT_FAILURE);
            }
        directories[num_directories] = strdup(file_path);
        if (directories[num_directories] == NULL) {
            perror("strdup");
            exit(EXIT_FAILURE);
        }
        num_directories++; // Increment number of directories
    }
    return 0; // Continue
}
//to send reply to client
void send_directory_list_based_on_time(int sockfd) {
    // Send the number of directories first
    insertion_sort();
    // for(int i=0;i<num_directories;i++){
    //     printf("order:%s\n",directories[i]);
    // }
    printf("count:%d\n",num_directories);
    if (write(sockfd, &num_directories_t, sizeof(int)) == -1) {
        perror("write");
        exit(EXIT_FAILURE);
    }

    // Send each directory path
    for (int i = 0; i < num_directories_t; i++) {
        int path_len = strlen(directories_time[i]);
        if (write(sockfd, &path_len, sizeof(int)) == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }
        if (write(sockfd, directories_time[i], path_len) == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }
    }

    // Free the array of directory paths
//     for (int i = 0; i < num_directories; i++) {
//         free(directories[i]);
//     }
//     free(directories);
 }

void send_directory_list(int sockfd) {
    // Send the number of directories first
    heap_sort(directories, num_directories);
    // for(int i=0;i<num_directories;i++){
    //     printf("order:%s\n",directories[i]);
    // }
     printf("count:%d\n",num_directories);
    if (write(sockfd, &num_directories, sizeof(int)) == -1) {
        perror("write");
        exit(EXIT_FAILURE);
    }

    // Send each directory path
    for (int i = 0; i < num_directories; i++) {
        int path_len = strlen(directories[i]);
        if (write(sockfd, &path_len, sizeof(int)) == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }
        if (write(sockfd, directories[i], path_len) == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }
    }

    // Free the array of directory paths
//     for (int i = 0; i < num_directories; i++) {
//         free(directories[i]);
//     }
//     free(directories);
 }

void getdirlisttime(){
    int flag = FTW_PHYS;
    int traverse=nftw(path,directory_finder_with_time,64,flag);
}

void getdirlistalpha(){
    int flag = FTW_PHYS;
    int traverse=nftw(path,directory_finder,64,flag);
}


int main() {
    int servSockD = socket(AF_INET, SOCK_STREAM, 0);
    if (servSockD == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in servAddr;
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(9697);
    servAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(servSockD, (struct sockaddr*)&servAddr, sizeof(servAddr)) == -1) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(servSockD, 1) == -1) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening for connections...\n");

    int clientSocket = accept(servSockD, NULL, NULL);
    if (clientSocket == -1) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    printf("Client connected\n");

    char message[MAX_MESSAGE_SIZE];
    char strData[MAX_MESSAGE_SIZE];
    recv(clientSocket, message, sizeof(message), 0);
        message[sizeof(message)-1]='\0';
         printf("Message from client: %s\n", message);
        //  send(clientSocket, strData, strlen(strData), 0);
        memset(message, '\0', sizeof(message));
        int connection_count=1;
        send(clientSocket,"proceed",sizeof("proceed"),0);
    while (1) {
        // Receive message from client
        recv(clientSocket, message, sizeof(message), 0);
        //printf("Message from client: %s\n", message);
        message[sizeof(message)-1]='\0';
        
        
       // printf("Message from client: %s\n", message);
    if(connection_count>=1 && connection_count<=3){
        if(strcmp(message,"dirlist -a\n")==0){//for dirlist -a
        printf("Message from client : %s\n",message);
        getdirlistalpha();
        send_directory_list(clientSocket);
    }
    else if(strcmp(message,"dirlist -t\n")==0){//for dirlist -a
        printf("Message from client : %s\n",message);
    getdirlisttime();
    send_directory_list_based_on_time(clientSocket);
    }
    else if(strstr(message,"w24fn")!=NULL){//for w24fn filename
    printf("Message from client : %s\n",message);
    searchfile(clientSocket,message);
    }
    else if(strstr(message,"w24fz")!=NULL){//for w24fn size1 size2
    printf("Message from client : %s\n",message);
    zipbysize(clientSocket,message);
    //searchfile(clientSocket,message);
    }
    else if(strstr(message,"w24ft")!=NULL){//for w24ft ext
    printf("Message from client : %s\n",message);
    zipbyext(clientSocket,message);
    }
     else if(strstr(message,"w24da")!=NULL){//for w24da date
    printf("Message from client : %s\n",message);
    zipbyda(clientSocket,message);
    }
    else if(strstr(message,"w24db")!=NULL){//for w24da date
    printf("Message from client : %s\n",message);
    zipbydb(clientSocket,message);
    }
        // Send response to client
        //printf("Enter response: ");
        
        //fgets(strData, MAX_MESSAGE_SIZE, stdin);
        //send(clientSocket, strData, strlen(strData), 0);
        memset(message, '\0', sizeof(message));
    }
   
    }
   
    close(servSockD);
    close(clientSocket);

    return 0;
}
