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
#include <utils.h>
#include <AutoHttpApplication.h>

#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>

#include <cstdio>


int main() {
    pg::HttpAppServer s(8080);

    auto apps = pg::Configure::getInstance()->getFileReponseApplications();
    s.addApplicationBatch(apps);

    for (auto & e : apps) {
        auto ee = dynamic_cast<pg::HttpFileResponseApplication* >(e);
        printf("%s, %s, %s\n", ee->url.c_str(), ee->filename.c_str(), ee->contentType.c_str());
    }
    
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

    return 0;
}
