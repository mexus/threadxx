#include "threadxx.h"

namespace threadxx {

	Thread::Thread(int id) : id(id), interrupted(false), cLog("Thread #" + std::to_string(id)) {
	}
	
	Thread::~Thread() {
	        D_LOG("~Thread");
	        log(logxx::debug) << "Destructing class" << logxx::endl;
	        if (thread){
	                if (!interrupted){
	                        log(logxx::debug) << "Interrupting a thread via variable" << logxx::endl;
	                        interrupted.store(true);
	                }
	                log(logxx::debug) << "Joining a thread" << logxx::endl;
	                JoinWOCheck();
	        }
	}
	
	void Thread::MakeThread() {
	        D_LOG("MakeThread");
	        thread = std::unique_ptr<std::thread>(new std::thread([this, &log](){
	                {
	                        log(logxx::debug, "std::thread") << "Waiting for ready flag" << logxx::endl;
	                        std::unique_lock<std::mutex> lk(threadExecuteMutex);
	                        threadCV.wait(lk, [this]{return threadReadyToStart;});
	                        threadStarted = true;
	                        lk.unlock();
	                }
	                this->Run();
	        }));
	}
	
	void Thread::WaitForStart() {
	        D_LOG("WaitForStart");
	        {
	                std::unique_lock<std::mutex> lk(threadExecuteMutex);
	                threadReadyToStart = true;
	                log(logxx::debug) << "Main thread ready for processing, notifying thread" << logxx::endl;
	                threadCV.notify_one();
	        }
	        
	        {
	                std::unique_lock<std::mutex> lk(threadExecuteMutex);
	                log(logxx::debug) << "Waiting for a thread to start" << logxx::endl;
	                threadCV.wait(lk, [this]{return threadStarted;});
	        }
	}
	
	bool Thread::Start() {
	        D_LOG("Start");
	        if (thread){
	                auto &s = log(logxx::debug) << "thread already exists and is ";
	                if (!thread->joinable())
	                        s << "not ";
	                s << "joinable" << logxx::endl;
	                return false;
	        } else {
	                interrupted = false;
	                threadReadyToStart = false;
	                threadStarted = false;
	                log(logxx::debug) << "Creating a thread" << logxx::endl;
	                try {
	                        MakeThread();
	                        WaitForStart();
	                        log(logxx::debug) << "Resuming main thread" << logxx::endl;
	                        return true;
	                } catch (const std::system_error &e){
	                        log(logxx::error) << "Can't create thread, an exception caught #" <<
	                                e.code() << ": " << e.what() << logxx::endl;
	                        return false;
	                }
	               
	        }
	}
	
	void Thread::Join() {
	        D_LOG("Join");
	        if (thread)
	                JoinWOCheck();
	        else
	                log(logxx::warning) << "Thread is nullptr" << logxx::endl;
	}
	
	void Thread::JoinWOCheck() {
	        D_LOG("JoinWithOutCheck");
	        log(logxx::debug) << "Joining a thread" << logxx::endl;
	        if (thread->joinable())
	                thread->join();
	        else
	                log(logxx::debug) << "Thread is not joinable" << logxx::endl;
	        thread.reset();
	}
	
	void Thread::Interrupt() {
	        D_LOG("Interrupt");
	        if (thread) {
	                log(logxx::debug) << "Interrupting thread" << logxx::endl;
	                interrupted.store(true);
	        } else
	                log(logxx::debug) << "Thread is nullptr" << logxx::endl;
	}
	
	void Thread::Run() {
	        D_LOG("Run");
	        log(logxx::debug) << "Thread launched, notifying main thread" << logxx::endl;
	        threadCV.notify_one();
	}
} // namespace threadxx

