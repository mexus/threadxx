#include "testing.h"

int main() {
        logxx::SetLogLevel(logxx::debug);
        bool res(true);
        thread_test::Testing testing;
        res &= testing.RunTest();
        return res ? 0 : 1;
}

