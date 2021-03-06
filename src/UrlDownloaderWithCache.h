//
//   File name      : UrlDownloaderWithCache.h
//
//   Author         : Yonghang Jiang(seedjyh@gmail.com)
//
//   Project name   : IFComicDownloader
//
//   Create datetime: 2015-12-30 15:47:36
//

#ifndef _URLDOWNLOADERWITHCACHE_H_
#define _URLDOWNLOADERWITHCACHE_H_ 1

// Inherite header
#include "IFCurlAdaptor/UrlDownloaderSimple.h"

// C system headers
// ...

// C++ system headers
// ...

// Headers from other projects
// ...

// Headers of current project
// ...

class CacheManager;

class UrlDownloaderWithCache : public UrlDownloaderSimple
{
    CacheManager &cache_manager_;
public:
    UrlDownloaderWithCache(
        CurlEasyInit    my_curl_easy_init,
        CurlEasySetOpt  my_curl_easy_setopt,
        CurlEasyPerform my_curl_easy_perform,
        CurlEasyCleanUp my_curl_easy_cleanup,
        CacheManager &cache_manager
    );
    virtual ~UrlDownloaderWithCache(){}

    // If URL is cached, return cached file.
    // If not cached, download it and add data into cache.
    virtual DATAHOLDER_PTR Download(const std::string &kURL, const std::string &kRefererURL, const std::string &kCookie);
protected:
private:
};

#endif
