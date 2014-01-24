#ifndef THREAD_H
#define	THREAD_H

#include <thread>
#include <condition_variable>
#include <atomic>
#include "../logxx/logxx.h"

class Thread {
public:
        Thread(int id);
        virtual ~Thread();
        
        virtual bool Start();
        virtual void Join();
        virtual void Interrupt();
        
        const int id;
protected:
        virtual void Run();
        std::atomic_bool interrupted;
        std::unique_ptr<std::thread> thread;
        logxx::Log cLog;
        
private:
        void JoinWOCheck();
        void MakeThread();
        void WaitForStart();
        
        std::mutex threadExecuteMutex;
        std::condition_variable threadCV;
        bool threadReadyToStart;
        bool threadStarted;

};

#endif	/* THREAD_H */

