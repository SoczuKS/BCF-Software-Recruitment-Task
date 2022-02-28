#pragma once

#include <condition_variable>
#include <functional>
#include <queue>
#include <thread>
#include <vector>

class ThreadPool {
public:
    ThreadPool(unsigned int = 64);
    ~ThreadPool();

    void addJob(std::function<void()>);
    void terminate();

private:
    bool terminatePool{false};
    bool stopped{false};
    unsigned int maxNumberOfThreads{};

    std::queue<std::function<void()>> jobsQueue{};
    std::vector<std::thread> threads{};
    std::condition_variable condition{};
    std::mutex queueMutex{};

    void worker();
};
