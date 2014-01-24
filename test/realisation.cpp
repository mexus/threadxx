#include "realisation.h"
#include <chrono>

namespace thread_test {

        Realisation::Realisation(int id, int sleepDuration) : Thread(id), sleepDuration(sleepDuration),
                cLog(this->Thread::cLog, "Realisation")
        {
                D_LOG("Realisation");
                log(logxx::debug) << "Created a class" << logxx::endl;
        }

        Realisation::~Realisation() {
                D_LOG("~Realisation");
                log(logxx::info) << "Execution count: " << executed << logxx::endl;
        }
        
        void Realisation::Run() {
                Thread::Run();
                D_LOG("Run");
                log(logxx::info) << "Running thread" << logxx::endl;
                executed = 0;
                while (!interrupted){
                        ++executed;
                        log(logxx::info) << "Sleeping for " << sleepDuration.count() << " seconds" << logxx::endl;
                        std::this_thread::sleep_for(sleepDuration);
                }
        }
        
        unsigned int Realisation::Executed() const {
                return executed;
        }


} // namespace thread_test
