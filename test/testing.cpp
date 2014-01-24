#include "testing.h"
#include "realisation.h"
#include "config.h"

namespace thread_test {
        
        LogFile::LogFile(const std::string& fileName) : fStream(fileName) {
                if (!fStream.good())
                        throw std::logic_error("Can't open file {" + fileName + "}");
                else {
                       logxx::SetStream(fStream);
                }
        }

        LogFile::~LogFile() {
                logxx::SetStream(std::cout);
        }
        
        
        logxx::Log Testing::cLog("Testing");

        Testing::Testing() {
        }

        Testing::~Testing() {
        }
        
        bool Testing::RunTest() const {
                S_LOG("RunTest");
//                logxx::SetLogLevel(logxx::warning);
                logxx::SetLogLevel(logxx::debug);
                log(logxx::info) << "Starting tests" << logxx::endl;
                bool res(true);
                res = TestStartJoin() && TestDestruction();
//                res = TestDestruction();
                
                if (res)
                        log(logxx::info) << "OK" << logxx::endl;
                else
                        log(logxx::info) << "FAILED" << logxx::endl;
                
                return res;
        }

        bool Testing::TestStartJoin() const {
                S_LOG("TestStartJoin");
                log(logxx::info) << "Testing start, interrupt and join" << logxx::endl;
                LogFile lf(DATA_DIR "TestStartJoin.output");
                try {
                        Realisation r1(0, 10);
                        Realisation r2(1, 2);
                        Realisation r3(2, 5);
                        
                        bool res = r1.Start() && r2.Start() && r3.Start();
                        if (res){
                                std::this_thread::sleep_for(std::chrono::milliseconds(16500));
                                r1.Interrupt(); r2.Interrupt(); r3.Interrupt();
                                
                                log(logxx::info) << "Waiting for threads" << logxx::endl;
                                r1.Join();
                                r2.Join();
                                r3.Join();
#define cmp(a, b)  \
        if (a != b) {\
                res = false;\
                log(logxx::warning) << #a " != " #b << ": " << a << " != " << b << logxx::endl; \
        }
                                cmp(r1.Executed(), 2);
                                cmp(r2.Executed(), 9);
                                cmp(r3.Executed(), 4);
#undef cmp
                        } else
                                log(logxx::error) << "Can't start threads" << logxx::endl;
                        return res;
                        
                } catch (const std::exception& e){
                        log(logxx::error) << "Caught an exception: " << e.what() << logxx::endl;
                        return false;
                }
        }

        bool Testing::TestDestruction() const {
                S_LOG("TestDestruction");
                log(logxx::info) << "Testing auto destruction" << logxx::endl;
                LogFile lf(DATA_DIR "TestDestruction.output");
                try {
                        Realisation r1(3, 2);
                        Realisation r2(4, 4);
                        Realisation r3(5, 5);
                        
                        bool res = r1.Start() && r2.Start() && r3.Start();
//                        bool res = r1.Start();
                        if (!res)
                                log(logxx::error) << "Can't start threads" << logxx::endl;
                        return res;
                        
                } catch (const std::exception& e){
                        log(logxx::error) << "Caught an exception: " << e.what() << logxx::endl;
                        return false;
                }
        }




} //namespace thread_test
