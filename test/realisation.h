#ifndef THREAD_REALISATION_H
#define	THREAD_REALISATION_H

#include "../main/threadxx/threadxx.h"
#include <chrono>

namespace thread_test {

        class Realisation : public Thread {
        public:
                Realisation(int id, int sleepDuration);
                virtual ~Realisation();
                
                unsigned int Executed() const;
                
        protected:
                virtual void Run();
                const std::chrono::seconds sleepDuration;
                unsigned int executed = 0;
                
                logxx::Log cLog;
        };
        
} //namespace thread_test
#endif	/* THREAD_REALISATION_H */

