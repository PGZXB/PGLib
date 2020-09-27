#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <cstdio>

#include <base/Buffer.h>
#include <base/FILEWrapper.h>

int main () {

    std::FILE * file;
    pg::base::FILEWrapper FILEW(file = std::fopen("test_BoolVector.cpp", "r+t"));
    pg::base::FILEWrapper FILEW2(std::fopen("test.txt", "w"));


    // std::printf("%s\n", FILEW.readAllAsString().c_str());
    // std::printf("%s\n", FILEW.readAsString(10).c_str());

    pg::base::Buffer buf;
    FILEW.readAll(buf);
    std::printf("%s\n", buf.get());

    FILEW2.write(buf, 100);

    return 0;
}