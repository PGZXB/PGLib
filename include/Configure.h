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
        Configure() {
            FILE * configFile = std::fopen(util::CONFIG_FILE_NAME, "r");
            char buf[BUFSIZ] = { 0 };

            rapidjson::FileReadStream fistream(configFile, buf, sizeof(buf));
            dom.ParseStream(fistream);

            std::fclose(configFile);
        }

        Configure(const Configure &) = delete;
        Configure(Configure &&) = delete;

        Configure & operator = (const Configure &) = delete;
        Configure & operator = (Configure &&) = delete;

    public:
        ~Configure() = default;

        type::Group<HttpApplication*> getFileReponseApplications() {
            type::Group<HttpApplication*> res;
            HttpFileResponseApplicationManager * manager = HttpFileResponseApplicationManager::getInstance();

            auto fileResponseArray = dom["file-response"].GetArray();

            std::string path;

            {
                auto end = fileResponseArray.End();
                for (auto iter = fileResponseArray.Begin(); iter != end; ++iter) {

                    path = (*iter)["path"].GetString();

                    
                    if ( iter->HasMember("urls") ) {
                        auto us = (*iter)["urls"].GetArray();

                        if (us.Empty())
                            res.push_back( manager->createObject(path.c_str()) );

                        for (auto & e : us)
                            res.push_back( manager->createObject(e.GetString(), path.c_str()) );
                    } else
                        res.push_back( manager->createObject(path.c_str()) );
                }
            }

            return res;            
        }

    public:
        static Configure * getInstance() {
            static Configure instance;

            return &instance;
        }

    private:
        rapidjson::Document dom;
    };
} // namespace pg



#endif