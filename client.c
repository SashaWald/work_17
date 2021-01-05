#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int main(){
    char buffer[256];
    char buffer2[256];
    //client creates "private" FIFO
    sprintf(buffer,"%d",getpid());
    mkfifo(buffer,0644);
    while(1){
        //client connects to server + sends private FIFO name
        int fd = open("WKP",O_WRONLY);
        write(fd,buffer,sizeof(buffer));
        close(fd);
        //client recieves server's acknowledgement message and removes FIFO
        int fd2 = open(buffer,O_RDONLY);
        read(fd2,buffer,sizeof(buffer));
        printf("message from server: %s\n",buffer);
        close(fd2);
        //client sends response to server
        int fdresponse = open("WKP",O_WRONLY);
        char str[256] = "recieved acknowledgment";
        write(fdresponse,str,strlen(str));
        close(fdresponse);
        //server and client exchange information
        if(strcmp(buffer,"acknowledged") == 0){
            int fd3=open("input",O_WRONLY);
            printf("please enter an input: ");
            fgets(buffer2,256,stdin);
            write(fd3,buffer2,strlen(buffer2));
            close(fd3);
            
            int fd4=open("output",O_RDONLY);
            read(fd4,buffer2,strlen(buffer2));
            printf("result: %s\n",buffer2);
            close(fd4);
            //printf("yes\n");
            sprintf(buffer,"%d",getpid());
        }
    }
    
    
    return(0);
}