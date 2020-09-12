#ifndef __AUTOHTTPAPPLICATIONMANAGER_H__
#define __AUTOHTTPAPPLICATIONMANAGER_H__

#include <HttpApplication.h>
#include <ObjectManager.h>
#include <AutoHttpApplication.h>
#include <PGDef.h>

#include <vector>
#include <string>


namespace pg {
    class AutoHttpApplicationManager {
        using ManagerType = ObjectManager<AutoHttpApplication>;
    public:
        AutoHttpApplicationManager() { }
        ~AutoHttpApplicationManager() { }

        void putApplication(std::string fullUrl, HttpApplication* app) {
            std::vector<std::string> urls = util::stringUtil::split(fullUrl, '/');
            std::vector<std::string>::iterator urlIter = urls.begin();
            std::map<std::string, AutoHttpApplication*>::iterator iter = appOfUrl.find(*urlIter);
            if (iter == appOfUrl.end()) {
                appOfUrl[*urlIter] = manager->createObject();
            }
        }
    private:
        std::map<std::string, AutoHttpApplication*> appOfUrl;
        ManagerType * manager = ManagerType::getInstance();
    };    
} // namespace pg


#endif