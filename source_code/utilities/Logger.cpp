#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <exception>
#include <cstdlib>

#include "Logger.hpp"

std::queue<std::string> messageQueue;
std::mutex messageQueueMutex;

std::thread * printLoopThread;
std::mutex printLoopMutex;
std::condition_variable printLoopConditionVariable;

LoggerLevels loggerConsoleLoggingLevel = LoggerLevels::Finest;
LoggerLevels loggerFileLoggingLevel = LoggerLevels::Finest;

bool shouldIncludeTimestamp = true;
bool shouldIncludeFile = true;
bool shouldIncludeLine = true;

bool intialize() __attribute__ ((constructor));
void printLoop();

bool intialize()
{
    using namespace std;

    try
    {
        printLoopThread = new thread(printLoop);
    }
    catch(const system_error & system_exception)
    {
        cerr << "Logger has failed intialization!" << endl;
        cerr << system_exception.what();
        exit(EXIT_FAILURE);
        return false;
    }

    return true;
}

void printLoop()
{
    using namespace std;

    unique_lock<mutex> printLoopLock(printLoopMutex);

    while(true)
    {
        messageQueueMutex.lock();

        /*
          Prints out the messages until the message queue is empty.
         */
        while(!messageQueue.empty())
        {
            string message = messageQueue.front();
            messageQueue.pop();

            /*
              Logger is meant to be low priority.
              So the message queue is unlocked incase something is trying to log a message.
             */
            messageQueueMutex.unlock();
            cout << message;

            messageQueueMutex.lock();
        }

        messageQueueMutex.unlock();

        /*
          Waits until log() is called and notifies that there are messages available.
         */
        printLoopConditionVariable.wait(printLoopLock);
    }
}

bool log(std::string message, LoggerLevels level, const char * file, int lineNumber)
{
    if(level >= loggerConsoleLoggingLevel)
    {
        using namespace std::chrono;

        /*
          Gets the current time.
         */
        time_point<system_clock> nowTimePoint = system_clock::now();
        time_t nowTime = system_clock::to_time_t(nowTimePoint);

        using namespace std;
        stringstream  stringStream;

        if(shouldIncludeTimestamp)
        {
            stringStream << put_time(localtime(& nowTime), "[%Y-%m-%d] [%X] ");
        }

        if(shouldIncludeFile)
        {
            stringStream << "[" << file << "] ";
        }

        if(shouldIncludeLine)
        {
            stringStream << "[" << lineNumber << "] ";
        }

        stringStream << "[" << LoggerLevelNames[level] << "] ";
        stringStream << message << "\n";

        /*
          Pushes the message to the message queue.
         */
        messageQueueMutex.lock();
        messageQueue.push(stringStream.str());
        messageQueueMutex.unlock();

        /*
          Notifies the printLoopThread that there are messages available to be printed to console.
         */
        printLoopConditionVariable.notify_one();

        return true;
    }

    return false;
}
