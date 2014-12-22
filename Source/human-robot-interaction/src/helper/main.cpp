#include <boost/thread.hpp>
#include <iostream>

using namespace std;

void ThreadFunction2()
{
//    int counter = 0;
    
    for(;;)
    {
        cout << "thread2 iteration " << endl;

        
        try
        {
            // Sleep and check for interrupt.
            // To check for interrupt without sleep,
            // use boost::this_thread::interruption_point()
            // which also throws boost::thread_interrupted
            boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
        }
        catch(boost::thread_interrupted&)
        {
            cout << "Thread is stopped" << endl;
            return;
        }
    }
}


void ThreadFunction1()
{
//    int counter = 0;
    
    for(;;)
    {
        cout << "thread1 iteration " << endl;
        
        try
        {
            // Sleep and check for interrupt.
            // To check for interrupt without sleep,
            // use boost::this_thread::interruption_point()
            // which also throws boost::thread_interrupted
            boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
        }
        catch(boost::thread_interrupted&)
        {
            cout << "Thread is stopped" << endl;
            return;
        }
    }
}

int main()
{
    // Start thread
    boost::thread t1(&ThreadFunction1);
    boost::thread t2(&ThreadFunction2);
    
    // Wait for Enter
    char ch;
    cin.get(ch);
    
    // Ask thread to stop
    t1.interrupt();
    t2.interrupt();
    
    // Join - wait when thread actually exits
    t1.join();
    t2.join();
    cout << "main: thread ended" << endl;
    
    return 0;
}