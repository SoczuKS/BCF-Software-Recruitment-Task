#include <ThreadPool.hpp>

#include <algorithm>
#include <mutex>
#include <thread>

ThreadPool::ThreadPool(unsigned int maxNumberOfThreads_) : maxNumberOfThreads(std::min(maxNumberOfThreads_, std::thread::hardware_concurrency())) {
    for (unsigned int i = 0; i < maxNumberOfThreads; ++i) {
        threads.push_back(std::thread(&ThreadPool::worker, this));
    }
}

ThreadPool::~ThreadPool() {
    if (!stopped) {
        terminate();
    }
}

void ThreadPool::addJob(std::function<void()> job) {
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        jobsQueue.push(job);
    }

    condition.notify_one();
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
void ThreadPool::worker() {
    while (true) {
        std::function<void()> job;

        {
            std::unique_lock<std::mutex> lock(queueMutex);

            condition.wait(lock, [this](){
                return !jobsQueue.empty() || terminatePool;
            });

            if (jobsQueue.empty()) {
                break;
            }

            job = jobsQueue.front();
            jobsQueue.pop();
        }

        job();
    }
}
#pragma clang diagnostic pop

void ThreadPool::terminate() {
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        terminatePool = true;
    }

    condition.notify_all();

    for (auto& thread : threads) {
        thread.join();
    }

    threads.clear();
    stopped = true;
}
