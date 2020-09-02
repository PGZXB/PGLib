#ifndef __CONFIGURE_H__
#define __CONFIGURE_H__

#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>

#include <cstdio>
#include <vector>

#include <HttpFileResponseApplication.h>
#include <ObjectManager.h>
#include <PGDef.h>
#include <utils.h>

namespace pg {
    class Configure {
        using HttpFileResponseApplicationManager = ObjectManager<HttpFileResponseApplication>;
    private:
        Configure();

        Configure(const Configure &) = delete;
        Configure(Configure &&) = delete;

        Configure & operator = (const Configure &) = delete;
        Configure & operator = (Configure &&) = delete;

    public:
        ~Configure();

        type::Group<HttpApplication*> getFileReponseApplications();

    public:
        static Configure * getInstance();

    private:
        rapidjson::Document dom;
    };
} // namespace pg



#endif