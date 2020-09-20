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

#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>

#include <cstdio>
#include <iostream>


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
    
    // bool	布尔型	-
    // char	字符型	8 bit
    // wchar_t	宽字符型	16 bit
    // short	短整型	16 bit
    // int	整形	16 bit
    // long	长整型	32 bit
    // long long	长整型	64 bit
    // float	单精度浮点型	6位有效数字
    // double	双精度浮点型	10位有效数字
    // long double	扩展精度浮点型	10位有效数字
    printf("\"%s\"\n", pg::util::stringUtil::format(
        "bool:{0}\n char:{1}\n short:{2}\n int:{3}\n"
        " long:{4}\n long long:{5}\n float:{6:.2}\n "
        "double:{7:.3}\n long double:{8}",
        false, 'T', (short)100, (int)100000, (long)1000000000, (long long)1000000000000000, (float)10.235, (double)19.898787222222, (long double)20.333724693444701470
        ).c_str());

    printf("\"%s\"\n", pg::util::stringUtil::format("{0}", std::vector<bool>{0, 1, 1, 0}).c_str());
    printf("%d\n", pg::util::stringUtil::__IN_fmtUtil::has_iterator<std::vector<int>>::value);
    return 0;
}
