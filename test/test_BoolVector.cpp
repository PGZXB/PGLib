#include <cstdio>
#include <ctime>
#include <cassert>
#include <cstdlib>

#include <base/BoolVector.h>


int main () {
    pg::base::BoolVector bv;

    bool bs[31234] = { 0 };
    std::srand(std::time(NULL));
    for (int i = 0; i < 10; ++i) {
        bs[i] = std::rand() > RAND_MAX / 2;
    }

    for (bool e : bs) {
        bv.push_back(e);
    }

    for (std::size_t i = 0; i < bv.size(); ++i) {
        assert(bs[i] == bv[i]);
    }

    // printf(", \b\b]");

    return 0;
}