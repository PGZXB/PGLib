#include <base/File.h>
#include <base/FDWrapper.h>
#include <base/FILEWrapper.h>

int main () {
    pg::base::File<pg::base::FDWrapper> file("tt.txt", pg::base::FileOpenMode::Read);

    printf("****<><><><><><>***\n");
    printf("[[%s]]\n", file.readAllAsString().c_str());


    printf("***<><><><><><>****\n");

    return 0;
}