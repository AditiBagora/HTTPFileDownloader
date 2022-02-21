#include <iostream>
#include "tcp.h"
#include "httpd.h"
#include<netdb.h>
#include <string>

using namespace std;
string hostname;
string requesturl;
struct in_addr ip_addr;

void InitializeHostandUrl(http_downloader httpclient,TCP sckt,string url)
{
   size_t found = url.find_first_of(":");

   string url_new=url.substr(found+3); //url_new is the url excluding the http part
   size_t found1 =url_new.find_first_of("/");
   string host =url_new.substr(0,found1);

   size_t found2 = url_new.find_first_of("/");
   string path =url_new.substr(found2);

   httpclient.sethostname(url_new.substr(0,found1));
   hostent* ip=gethostbyname(httpclient.hosname.c_str());

   struct in_addr** addrlist=(struct in_addr**)ip->h_addr_list;
   sckt.SetIp(inet_ntoa(*(addrlist[0])));
   httpclient.setRequestUrl(path.erase(path.size() - 1));
   hostname=url_new.substr(0,found1);
   requesturl=path;
   ip_addr=*addrlist[0];
}
void DownloadObjectInPersistentMode(string filename,TCP sckt,http_downloader httpclient)
{
    fstream objFile;
    objFile.open(filename,ios_base::in);

    if(objFile.is_open())
    {
        string objurl;int objCount=10;
        while(getline(objFile,objurl))
        {
            if(objCount<0)
             break;
             InitializeHostandUrl(httpclient,sckt,objurl);
             if(objCount==10)
             {
                sckt.SetIp(inet_ntoa(ip_addr));
                sckt.CreateSocket();
             }
             string pkt= httpclient.CreateHTTPRequest(1,hostname,requesturl);
             char sendDataBuf[65536];
             memset(sendDataBuf,0,65536);
             strcpy(sendDataBuf,pkt.c_str());
             sckt.SendPkt(sendDataBuf,strlen(pkt.c_str()));
             sckt.RecevePkt("Persistent");
             objCount--;
         }
    }
}
void DownloadObjectInNonPersistentMode(string filename,TCP sckt,http_downloader httpclient)
{
    fstream objFile;
    objFile.open(filename,ios_base::in);

    if(objFile.is_open())
    {
        string objurl;int objCount=10;
        while(getline(objFile,objurl))
        {
            if(objCount==0)
             break;

             InitializeHostandUrl(httpclient,sckt,objurl);
             sckt.SetIp(inet_ntoa(ip_addr));
             sckt.CreateSocket();
             string pkt= httpclient.CreateHTTPRequest(0,hostname,requesturl);
             char sendDataBuf[65536];
             strcpy(sendDataBuf,pkt.c_str());
             cout<<sendDataBuf;

             sckt.SendPkt(sendDataBuf,strlen(pkt.c_str()));
             sckt.RecevePkt("nonP");
             objCount--;
         }
    }
}
void DownloadOneObj(http_downloader httpclient,TCP sckt)
{
    string url;
    cout<<"Enter url"<<endl;
    cin>> url;
    InitializeHostandUrl(httpclient,sckt,url);
    sckt.SetIp(inet_ntoa(ip_addr));
    sckt.CreateSocket();

    string pkt= httpclient.CreateHTTPRequest(1,hostname,requesturl);
    char sendDataBuf[65536];
    strcpy(sendDataBuf,pkt.c_str());
    cout<<sendDataBuf;

    sckt.SendPkt(sendDataBuf,strlen(pkt.c_str()));
    sckt.RecevePkt();
}

int main()
{
    TCP sckt;
    http_downloader httpclient;
    DownloadOneObj(httpclient,sckt);
    DownloadObjectInPersistentMode("New Text Document.txt",sckt,httpclient);
    DownloadObjectInNonPersistentMode("New Text Document.txt",sckt,httpclient);
    return 0;
}
