#include <HttpApplication.h>
#include <HttpAppServer.h>
#include <HttpRequest.h>
#include <HttpResponse.h>

class HA_Home : public pg::HttpApplication {
public:
    HA_Home() { this->url = "/home"; }

    void exec(const pg::HttpRequest &, pg::HttpResponse & response) override {
        response.setContentType(pg::util::HTTP_CT_HTML);
        response.setStatusCode(pg::util::HTTP_SUCCESS_STATUS_CODE);
        response.pushFile_back("/home/pgzxb/Pictures/home.html");
    }

    static HA_Home * getInstance() {
        static HA_Home instance;

        return &instance;
    }
};


class HA_Movie : public pg::HttpApplication {
public:
    HA_Movie() { this->url = "/movie"; }

    void exec(const pg::HttpRequest &, pg::HttpResponse & response) override {
        response.setContentType(pg::util::HTTP_CT_HTML);
        response.setStatusCode(pg::util::HTTP_SUCCESS_STATUS_CODE);
        response.pushFile_back("/home/pgzxb/Pictures/test.html");
    }

    static HA_Movie * getInstance() {
        static HA_Movie instance;

        return &instance;
    }
};

class HA_MP4 : public pg::HttpApplication {
public:
    HA_MP4() { this->url = "/movie.mp4"; }

    void exec(const pg::HttpRequest &, pg::HttpResponse & response) override {
        response.setContentType(pg::util::HTTP_CT_MP4);
        response.setStatusCode(pg::util::HTTP_SUCCESS_STATUS_CODE);
        response.pushFile_back("/home/pgzxb/Pictures/test.mp4");
    }

    static HA_MP4 * getInstance() {
        static HA_MP4 instance;

        return &instance;
    }
};

class HA_Icon : public pg::HttpApplication {
public:
    HA_Icon() { this->url = "/favicon.ico"; }

    void exec(const pg::HttpRequest &, pg::HttpResponse & response) override {
        response.setContentType(pg::util::HTTP_CT_JPG);
        response.setStatusCode(pg::util::HTTP_SUCCESS_STATUS_CODE);
        response.pushFile_back("/home/pgzxb/Pictures/test.jpg");
    }

    static HA_Icon * getInstance() {
        static HA_Icon instance;

        return &instance;
    }
};

int main() {
    pg::HttpAppServer s(8080);

    s
    .addApplication(HA_Home::getInstance())
    .addApplication(HA_Movie::getInstance())
    .addApplication(HA_MP4::getInstance())
    .addApplication(HA_Icon::getInstance());

    s.run();

    return 0;
}
