#include <iostream>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

int main()
{
    boost::asio::io_service io;
    
    for(;;) {
        boost::asio::deadline_timer timer(io, boost::posix_time::seconds(1));
        timer.wait();
        std::cout << "Blocking wait(): " << boost::posix_time::second_clock::local_time() << " second-wait\n";
    }
    
    return 0;
}