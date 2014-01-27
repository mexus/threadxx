#include "testing.h"

int main() {
        logxx::GlobalLogLevel(logxx::debug);
        bool res(true);
        thread_test::Testing testing;
        res &= testing.RunTest();
        return res ? 0 : 1;
}

