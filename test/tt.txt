#include <base/File.h>

#define DEBUG_PRINT(fmt, msg) std::printf(" In %s at %-3d MSG( %-30s ) : "#fmt"\n", __FILE__, __LINE__, #msg, msg);

int main () {

    pg::base::File file("/home/pgzxb/Documents/DevWorkspace/PGLib/test/tt.txt");

    DEBUG_PRINT("%s", file.getAbsolutePath().c_str());
    DEBUG_PRINT("%s", file.getName().c_str());
    DEBUG_PRINT("%s", file.getParent().c_str());
    DEBUG_PRINT("%d", file.isAbsolute());
    DEBUG_PRINT("%d", file.isDir());
    DEBUG_PRINT("%d", file.isFile());
    DEBUG_PRINT("%d", file.writable());
    DEBUG_PRINT("%d", file.readable());

    auto pFdWper =  file.getFILEWrapper();
    DEBUG_PRINT("\n%s\n", pFdWper->readAllAsString().c_str())

    return 0;
}