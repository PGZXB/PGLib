#include "../include/base/Buffer.h"

#include <cstdio>

int main () {
    pg::base::Buffer buffer;

    struct String { char str[BUFSIZ] = "Test For String"; };

    String str;
    int val = 100;

    buffer.push_back(val);
    buffer.push_back(str);


    int val2 = -1;
    std::memcpy(&val2, (void *)(buffer.get()), sizeof(int));

    for (size_t i = 0; i < buffer.size(); ++i) {
        putc(*(buffer.get() + i), stdout);
    } putc('\n', stdout);
    std::printf("%d\n", *(int *)buffer.get());
    std::printf("%s\n", buffer.get() + sizeof(int));

    std::printf("----------------------------------------------------------------\n");

    pg::base::StaticBuffer<1024> buffer2;

    buffer2.push_back(val);
    buffer2.push_back(&str, sizeof(str));

    for (size_t i = 0; i < buffer.size(); ++i) {
        putc(*(buffer.get() + i), stdout);
    } putc('\n', stdout);
    std::printf("%d\n", *(int *)buffer.get());
    std::printf("%s\n", buffer.get() + sizeof(int));

    return 0;
}