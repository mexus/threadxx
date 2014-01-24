#ifndef THREAD_TESTING_H
#define	THREAD_TESTING_H

#include "../main/logxx/logxx.h"
#include <fstream>

namespace thread_test {
        
        struct LogFile {
                LogFile(const std::string &fileName);
                ~LogFile();
        private:
                std::ofstream fStream;
        };

        class Testing {
        public:
                Testing();
                virtual ~Testing();
                
                bool RunTest() const;
        private:
                static logxx::Log cLog;
                
                bool TestStartJoin() const;
                bool TestDestruction() const;

        };
        
} //namespace thread_test

#endif	/* THREAD_TESTING_H */

