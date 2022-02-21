#include"httpd.h"
#include<iostream>
#include<sstream>
#include<fstream>
#include <netinet/in.h>
#include<string.h>

using namespace std;
//string type="";
string http_downloader::CreateHTTPRequest(int Persistent,string hostname,string url)
{
    stringstream ss;
    string connectiontype="keep-alive";
    if(Persistent==0)
        connectiontype="close";

    string formatted_string;
    formatted_string="GET ";
    formatted_string+=url;
    formatted_string+=" HTTP/1.1\r\nHost:";
    formatted_string+=hostname;
    formatted_string+="\r\nConnection:"+ connectiontype +"\r\n\r\n";
    return formatted_string;

}
void http_downloader::setRequestUrl(string url)
{
    requestUrl=url;
}

int http_downloader::ParseHeader(int sock){
    char c;
    char buff[1024]="",*ptr=buff+4;
    int bytes_received, status;
    printf("Reading Content length from header ..\n");
    while(bytes_received = recv(sock, ptr, 1, 0)){
        if(bytes_received==-1){
            perror("Parse Header");
            exit(1);
        }

        if(
            (ptr[-3]=='\r')  && (ptr[-2]=='\n' ) &&
            (ptr[-1]=='\r')  && (*ptr=='\n' )
        ) break;
        ptr++;
    }

    *ptr=0;
    ptr=buff+4;

    if(bytes_received){
        ptr=strstr(ptr,"Content-Length:");
        if(ptr)
        {
            sscanf(ptr,"%*s %d",&bytes_received);

        }
        else
            bytes_received=-1; //unknown size

       printf("Content-Length: %d\n",bytes_received);
    }
    //*ptr=0;
    ptr=buff+4;
    //string type="";

    if(bytes_received){
        ptr=strstr(ptr,"Content-Type:");
        if(ptr)
        {
            //sscanf(ptr,"%*s %d",type);
            char* ptr1=ptr+14;
            ptr1=strstr(ptr1,"\r");
            int length=ptr1-ptr-14;
            for(int i=0;i<length;i++)
               type=type + *(ptr+14+i);

        }
        /*else
            type=; //unknown size*/

       cout<<type;
    }
    printf("Completed ..\n");
    return  bytes_received ;
}
