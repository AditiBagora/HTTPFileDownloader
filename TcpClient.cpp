#include "tcp.h"
#include "httpd.h"
#include <netinet/in.h>
#include <iostream>
using namespace std;
void TCP:: SetIp(string ip1)
{
      ip=ip1;
}
void TCP:: SetPort(int port)
{
       port=htons(port);
}

int TCP:: SendPkt(const char* buf,int size_pkt)
{
       int bytesend=send(socketFd,buf,size_pkt,0);
       if(bytesend<0)
       {
         cout<<"send failed";
       }
       else
       cout<<"Send successful"<<bytesend<<endl;
    return bytesend;
}
void TCP::RecevePkt(string type)
{
       char rcvDataBuf[65536];
       socklen_t sinSize = sizeof(struct sockaddr_in);
       cout<<"Receiving response...";
       memset(&rcvDataBuf, 0, 65536);
       downloadCount=downloadCount + 1;
       string filename=type+"Obj";
       filename+=to_string(downloadCount);



       http_downloader httpclient;
       int contentlength=httpclient.ParseHeader(socketFd);
       string type1=httpclient.type;
       size_t found2 = type1.find_first_of("/");
       string extension =type1.substr(found2);
       filename+="."+extension.erase(0,1);
       ofstream File_HTTP(filename);
       int datarecv=0;int bytes=0;
       cout<<"Downloading Object.....";
       while(datarecv = recv(socketFd, rcvDataBuf, 65535, 0))
          {
            if(datarecv==-1)
            {
                perror("recieve");
                exit(3);
            }
            File_HTTP.write(rcvDataBuf,datarecv);

            bytes+=datarecv;
            if(bytes==contentlength)
              break;
          }

       File_HTTP.close();
       cout<<"Download Complete"<<downloadCount;
}


