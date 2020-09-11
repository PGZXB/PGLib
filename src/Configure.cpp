#include <Configure.h>

// private-constructor
pg::Configure::Configure() {
    FILE * configFile = std::fopen(util::CONFIG_FILE_NAME, "r");
    char buf[BUFSIZ] = { 0 };

    rapidjson::FileReadStream fistream(configFile, buf, sizeof(buf));
    dom.ParseStream(fistream);

    std::fclose(configFile);
}

// public-funcitons
pg::Configure::~Configure() = default;

pg::type::Group<pg::HttpApplication*> pg::Configure::getFileReponseApplications() {
    static type::Group<HttpApplication*> res;
    if (!res.empty()) return res;
    
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

pg::HttpApplication* pg::Configure::get404Page() {
    return getFileReponseApplications().back();
}

// public-static-function(s)
pg::Configure * pg::Configure::getInstance() {
    static Configure instance;

    return &instance;
}