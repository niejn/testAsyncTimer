#include <iostream>
#include "asynctimerqueue.h"
auto start = std::chrono::system_clock::now();

int handler1() {
    std::cout << "handler1 ";
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>( \
    std::chrono::system_clock::now() - start).count() << std::endl;
    return 0;
}

int handler2() {
    std::cout << "handler2 ";
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>( \
    std::chrono::system_clock::now() - start).count() << std::endl;

    return 0;
}

class foo {
public:
    void handler3() {
        std::cout << "handler3 ";
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>( \
        std::chrono::system_clock::now() - start).count() << std::endl;
    }
};

#define asyncTimerObj Timer::AsyncTimerQueue::Instance()

int main()
{
    // Start timer loop
    std::thread asyncthread(&Timer::AsyncTimerQueue::timerLoop,
                            &asyncTimerObj);

    foo f;

    int eventId1 = asyncTimerObj.create(5000, true, &handler1);
    int eventId2 = asyncTimerObj.create(3000, true, &handler2);
    int eventId3 = asyncTimerObj.create(6000, false, &foo::handler3, &f);

    std::this_thread::sleep_for(std::chrono::seconds(10));

    if (asyncTimerObj.cancel(eventId1) == -1) {
        std::cout << "Failed to cancel id" << std::endl;
    }

    if (asyncTimerObj.cancel(eventId2, 3000) == -1) {
        std::cout << "Failed to cancel id" << std::endl;
    }

    if (asyncTimerObj.cancel(eventId3) == -1) {
        std::cout << "Failed to cancel id" << std::endl;
    }

    asyncTimerObj.shutdown();

    asyncthread.join();


    std::cout << "Main Thread Shut down!" << std::endl;
    return 0;
}