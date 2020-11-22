#define private public // To Test
#define protected public // To Test

#include <HttpAppServer.h>
#include <HttpRequest.h>
#include <HttpResponse.h>
#include <HttpApplication.h>
#include <HttpFileResponseApplication.h>
#include <ObjectManager.h>
#include <Configure.h>
#include <AutoHttpApplication.h>
#include <base/DynamicArrayWrapper.h>
#include <PGDef.h>
#include <utils.h>
#include <fmt_util.h>
#include <tostring_util.h>
#include <Page.h>

#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>

#include <cstdio>
#include <iostream>
#include <map>


int main() {
    pg::HttpAppServer s(8080);

    auto apps = pg::Configure::getInstance()->getFileReponseApplications();
    s.addApplicationBatch(apps);

    for (auto & e : apps) {
        auto ee = dynamic_cast<pg::HttpFileResponseApplication* >(e);
        printf("%s, %s, %s\n", ee->url.c_str(), ee->filename.c_str(), ee->contentType.c_str());
    }
    
    // /test/index/home.html
    pg::HttpApplication * app = pg::Configure::getInstance()->getFileReponseApplications().front();
    pg::AutoHttpApplication autoApp2(
        [app] (const pg::HttpRequest & request, pg::HttpResponse & response)
            { app->exec(request, response); }, "/test");
    pg::AutoHttpApplication autoApp("/index");
    autoApp.pushChildApplication(&autoApp2);
    autoApp2.pushChildApplication(
        pg::Configure::getInstance()->getFileReponseApplications().front()
    );
    s.addApplication(&autoApp);

    s.run();

    pg::Page page("/home/pgzxb/Pictures/index.html");

    printf("\n---\n%s\n---\n", page.formatAll(std::string("First"), 128, 1024).c_str());

    return 0;
}
