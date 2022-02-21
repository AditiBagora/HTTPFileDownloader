#ifndef TCP_H_INCLUDED
#define TCP_H_INCLUDED

#include <string>
#include "tcp.h"
using namespace std;
class http_downloader
{
    public:
    string requestUrl;
    //char * GetHTTPRequest();
    string CreateHTTPRequest(int Persistent);
    void setRequestUrl(string url);
    //void DownloadObjectInPersistentMode(string filename,TCP sckt);
    //void DownloadObjectInNonPersistentMode(string filename,TCP sckt);
};
#endif // HTTP_H_INCLUDED
