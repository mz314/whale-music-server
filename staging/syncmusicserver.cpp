#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using namespace std;


int main()
{
 
    boost::asio::io_service io_service;

    tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 6543));
     tcp::socket socket(io_service);
      acceptor.accept(socket);
    for (;;)
    {
     
      
      char msg[]={"DUPA56789"};
      char buff[128];
      cout << "MSG: " << msg << endl;
      boost::system::error_code ignored_error;
      int bs=boost::asio::write(socket, boost::asio::buffer(msg));
      socket.read_some(boost::asio::buffer(buff),ignored_error);
      cout << "WROTE: " << bs << endl;
      cout << buff << endl;
      cout.flush();
      sleep(1);
      
    }
  
 

  return 0;
}