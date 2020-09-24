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
#include <AutoHttpApplication.h>
#include <utils.h>
#include <fmt_util.h>
#include <tostring_util.h>
#include <tools/DynamicArrayWrapper.h>

#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>

#include <cstdio>
#include <iostream>
#include <map>


int main() {
    // pg::HttpAppServer s(8080);

    // auto apps = pg::Configure::getInstance()->getFileReponseApplications();
    // s.addApplicationBatch(apps);

    // for (auto & e : apps) {
    //     auto ee = dynamic_cast<pg::HttpFileResponseApplication* >(e);
    //     printf("%s, %s, %s\n", ee->url.c_str(), ee->filename.c_str(), ee->contentType.c_str());
    // }
    
    // pg::HttpApplication * app = pg::Configure::getInstance()->getFileReponseApplications().front();
    // pg::AutoHttpApplication autoApp2(
    //     [app] (const pg::HttpRequest & request, pg::HttpResponse & response)
    //         { app->exec(request, response); }, "/test");
    // pg::AutoHttpApplication autoApp("/index");
    // autoApp.pushChildApplication(&autoApp2);
    // autoApp2.pushChildApplication(
    //     pg::Configure::getInstance()->getFileReponseApplications().front()
    // );
    // s.addApplication(&autoApp);

    // s.run();

    // for (auto & e : pg::util::stringUtil::__IN_fmtUtil::parseArgs(std::vector<std::string>{"1", "2", "3", ""}, 1, 1, 1)) {
    //     printf("%s, ", e.c_str());
    // } printf("\n");
    // puts(pg::util::stringUtil::format(
        // "{0}\n{0}", std::map<int, std::list<int>>{{1, {1}}, {2, {1, 2}}, {3, {1, 2, 3}}}).c_str());
    
    pg::tools::DynamicArrayWrapper<std::vector<std::vector<int>>> V2D(new std::vector<std::vector<int>>[10]);
    for (int i = 0; i < 10; ++i) { 
        V2D[i].push_back({i, i + 1, i * i});
        V2D[i].push_back({i + 2, i + 3, i * i * i});
        V2D[i].push_back({i + 3, i + 4, i * i * i * i});
    }
    for (int i = 0; i < 10; ++i) {
        puts(pg::util::stringUtil::__IN_fmtUtil::transToString(V2D[i], {}).c_str());
    }

    return 0;
}
