#ifndef HTTPD_H_INCLUDED
#define HTTPD_H_INCLUDED

#include <string>
using namespace std;
class http_downloader
{
    public:
    string requestUrl;
    string hosname;
    string type="";
    string CreateHTTPRequest(int Persistent,string hostname,string url);
    void setRequestUrl(string url);
    int ParseHeader(int sock);
    void DownloadObjectInPersistentMode(string filename,int sckt);
    void DownloadObjectInNonPersistentMode(string filename,int sckt);
    void sethostname(string hname)
    {
      hosname=hname;
    }
};
#endif // HTTPD_H_INCLUDED
