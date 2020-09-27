#include <base/FDWrapper.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <cstdio>

#include <base/Buffer.h>

int main () {

    pg::base::FDWrapper FD(::open("test_BoolVector.cpp", O_RDONLY));

    std::printf("%s\n", FD.readAllAsString().c_str());
    std::printf("%s\n", FD.readAsString(10).c_str());

    pg::base::Buffer buf;
    FD.readAll(buf);
    std::printf("%s\n", buf.get());

    return 0;
}