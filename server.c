#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

int main(){
    char buffer[256];
    char buffer2[256];
    //server creates FIFO (WKP) + waits for connection
    mkfifo("WKP",0644);
    mkfifo("input",0666);
    mkfifo("output",0666);
    while(1){
        //server recieves client's message (private FIFO name) and removes WKP
        int fd = open("WKP",O_RDONLY);
        read(fd,buffer,sizeof(buffer));
        printf("communicating with client: %s\n",buffer);
        close(fd);
        //server connects to client's FIFO and sends acknowledgement message
        int fd2 = open(buffer,O_WRONLY);
        char str[256] = "acknowledged";
        write(fd2,str,strlen(str));
        close(fd2);
        
        int fdresponse = open("WKP",O_RDONLY);
        read(fdresponse,buffer,sizeof(buffer));
        printf("message from client: %s\n",buffer);
        close(fdresponse);
        
        //server and client exchange information
        int fd3 = open("input",O_RDONLY);
        read(fd3,buffer2,strlen(buffer2));
        close(fd3);
        
        int fd4 = open("output",O_WRONLY);
        int i = 0;
        while(buffer2[i]){
            buffer2[i]=toupper(buffer2[i]);
            i++;
        }
        write(fd4,buffer2,strlen(buffer2)+1);
        close(fd4);
    }
    
    //client exits; server recreates WKP
    
    return(0);
}