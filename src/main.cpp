#define private public
#define protected public

#include <HttpAppServer.h>
#include <HttpRequest.h>
#include <HttpResponse.h>
#include <HttpApplication.h>
#include <HttpFileResponseApplication.h>
#include <ObjectManager.h>
#include <PGDef.h>
#include <Configure.h>

#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>

#include <cstdio>


int main() {
    pg::HttpAppServer s(8080);

    // pg::type::Group<pg::HttpApplication*> files = {
    //     new pg::HttpFileResponseApplication("/home/pgzxb/Pictures/home.html"),
    //     new pg::HttpFileResponseApplication("/home/pgzxb/Pictures/movie.html"),
    //     new pg::HttpFileResponseApplication("/home/pgzxb/Pictures/test.jpg"),
    //     new pg::HttpFileResponseApplication("/home/pgzxb/Pictures/movie.mp4"),
    //     new pg::HttpFileResponseApplication("/home/pgzxb/Pictures/favicon.ico"),
    //     new pg::HttpFileResponseApplication("/home/pgzxb/Pictures/index.html"),
    //     new pg::HttpFileResponseApplication("/home/pgzxb/Pictures/1.html"),
    //     new pg::HttpFileResponseApplication("/home/pgzxb/Pictures/2.html"),
    //     new pg::HttpFileResponseApplication("/home/pgzxb/Pictures/3.html"),
    //     new pg::HttpFileResponseApplication("/home/pgzxb/Pictures/4.html"),
    //     new pg::HttpFileResponseApplication("/home/pgzxb/Pictures/5.html"),
    //     new pg::HttpFileResponseApplication("/home/pgzxb/Pictures/6.html"),
    //     new pg::HttpFileResponseApplication("/home/pgzxb/Pictures/7.html"),

    // };

    // s.addApplicationBatch(files);
    // printf("_____________________________________________________________________\n");
    
    // s.run();

    auto apps = pg::Configure::getInstance()->getFileReponseApplications();

    s.addApplicationBatch(apps);

    for (auto & e : apps) {
        auto ee = dynamic_cast<pg::HttpFileResponseApplication*>(e);
        printf("%s, %s, %s\n", ee->url.c_str(), ee->filename.c_str(), ee->contentType.c_str());
    }

    s.run();

    return 0;
}
