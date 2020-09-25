#include "../include/base/Buffer.h"

#include <cstdio>

int main () {
    pg::base::Buffer buffer;

    struct String { char str[BUFSIZ] = "aiaiaiaiaaiaiaiaiaiaiaiaiaiaiia"; };

    String str;
    int val = 100;

    buffer.push_back(val);
    buffer.push_back(str);


    int val2 = -1;
    std::memcpy(&val2, (void *)(buffer.get()), sizeof(int));

    std::printf("%s\n", buffer.get());
    std::printf("%d\n", *(int *)buffer.get());
    std::printf("%s\n", buffer.get() + sizeof(int));

    return 0;
}