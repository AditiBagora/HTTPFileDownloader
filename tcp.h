#ifndef TCP_H_INCLUDED
#define TCP_H_INCLUDED
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include<fstream>
//namespace udp;
using namespace std;
class TCP
{
  public:
   string ip;
   int port;
   int downloadCount=0;
   int socketFd;
   char* buf_tcp;
   struct sockaddr_in destination;
   void SetIp(string ip);
   void SetPort(int port);
   int SendPkt(const char* buf,int size_pkt);
   void RecevePkt(string type="");
    TCP()
    {
        SetIp("199.232.22.208");
        SetPort(80);
    }
    void CreateSocket()
    {
      socketFd = socket(AF_INET, SOCK_STREAM, 0);
      if(!socketFd)
      {
        cout<<"Error creating socket"<<endl;
        exit(1);
      }
      else
        connect_server();
    }
    void connect_server()
    {

     destination.sin_family = AF_INET;
     destination.sin_port = htons(80);
     inet_pton(AF_INET, ip.c_str(), &(destination.sin_addr));
     memset(&(destination.sin_zero), '\0', 8);

     int ret = connect(socketFd, (struct sockaddr *)&destination, sizeof(struct sockaddr));
     if (ret<0)
     {
       cout<<"Error with server connection "<<endl;
       close(socketFd);
       exit(1);
      }
    }
   };
#endif // TCP_H_INCLUDED
