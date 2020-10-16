#include <base/File.h>
#include <base/Buffer.h>


#define DEBUG_PRINT(fmt, msg) std::printf("In %s at %-3d MSG( %-30s ) : " fmt "\n", __FILE__, __LINE__, #msg, msg)

int main () {

    pg::base::File file("tt_renamed.txt");

    DEBUG_PRINT("%s", file.getAbsolutePath().c_str());
    DEBUG_PRINT("%s", file.getName().c_str());
    DEBUG_PRINT("%s", file.getParent().c_str());
    DEBUG_PRINT("%d", file.exists());
    DEBUG_PRINT("%d", file.isAbsolute());
    DEBUG_PRINT("%d", file.isDir());
    DEBUG_PRINT("%d", file.isFile());
    DEBUG_PRINT("%d", file.writable());
    DEBUG_PRINT("%d", file.readable());

    file.rename("tt.txt");

    // auto pFILEWper = file.getFILEWrapper();
    // DEBUG_PRINT("\n%s\n", pFILEWper->readAllAsString().c_str());

    auto pFdWper = file.getFDWrapper();
    // DEBUG_PRINT("\n%s\n", pFdWper->readAllAsString().c_str());

    pg::base::Buffer buf;
    buf.push_back("Hello pg::base::File!");
    pFdWper->write(buf, buf.size());

    return 0;
}