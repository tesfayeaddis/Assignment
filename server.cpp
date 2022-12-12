#include<sys/type>
#include<unistd> 
#include<stdio>  
#include<string>
#include<stdlib>
#include<signal>
#include<sys/socket>
#include<sys/un>
#include <iostream>

using namespace std;
#define PORT 1897
#define SIM_LENGTH 10

int main (){
  
 int sock; 
 int connect_sock;
 struct sockaddr_in serv_name;
  size_t len; //It is the type of the result returned by sizeof operator.
  int count;
  
    sock = socket(AF_INET, SOCK_STREAM, 0); 
  
  if (sock < 0) {
         perror ("Error opening channel");
          clean_up(1, &sock); //invoke function clean up in the agrgumentd form of connect_sock and sock
    }
  
  
  bzero(&serv_name, sizeof(serv_name)); 
  serv_name.sin_family = AF_INET;
  serv_name.sin_port = htons(PORT);
  
   if (bind(sock, (struct sockaddr *)&serv_name, sizeof(serv_name)) < 0)
    { perror ("Error naming channel");
      clean_up(1, &sock);
    }
  
  
   cout<<"Server is a live and waiting for socket connection from client";
    listen(sock, 1);
  
   len = sizeof(serv_name);
  connect_sock = accept(sock, (struct sockaddr *)&serv_name, &len);
  
  for (count = 1; count <= SIM_LENGTH; count++)
    { write(connect_sock, &count, 4);
      cout<<"Server has written %d to socket." + count;
  
  
  close(connect_sock);  
  clean_up(0, &sock);
  
  return 0;
}
  
//funciton to remove connction
void clean_up(int cond, int *sock){ 
  cout<<"Exiting";
   close(*sock); 
    exit(cond);
}
