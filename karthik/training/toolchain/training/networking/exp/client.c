#include <stdio.h>                                                              
#include <sys/types.h>                                                          
#include <sys/socket.h>                                                         
#include <stdlib.h>                                                             
#include <netinet/in.h>                                                                                
int main(void)                                                                  
{                                                                               
    int sockfd; 
 	struct sockaddr_in addr;
	socklen_t length;     
                      
    void *buf = NULL;                                                           
    int len = 30;    

	if(NULL == (buf = (char *)malloc(sizeof(char)*1024))) {
		perror("malloc failed");
		exit(1);
	}

	if(-1 == (sockfd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP))) { /*create an endpoint  
                                                    for communication*/         
                                                                                
        perror("socket() failed");                                              
        exit(1);                                                                
    }   

   	addr.sin_family = PF_INET;                                               
    addr.sin_port = 3014;  
	addr.sin_addr.s_addr = inet_addr("172.16.5.56"); 

	while(1) {
		printf("Enter the message:");
		fgets(buf, 1024, stdin);

 		if(-1 == sendto(sockfd, buf, 1024, 0, (struct sockaddr *)&addr, sizeof(addr))) { /*send   
                                                        a message on a socket*/ 
        	perror("sendto() failed");                                              
        	exit(1);                                                                
    	}

		length = sizeof(addr);
 		if(-1 == recvfrom(sockfd, buf, 1024, 0 , (struct sockaddr *)&addr, &length)) {   

        	perror("recvfrom() failed");                                            
        	exit(1);                                                                
   	 	}
        printf("Message is %s",buf);

	}
	close(sockfd);

	return 0;
}                                                                           
                                                                                  
        
