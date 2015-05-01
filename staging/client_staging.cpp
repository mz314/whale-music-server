#include <iostream>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <cstring>
// #include <asio.hpp>


#include "../protocol.h"

using boost::asio::ip::tcp;
using namespace std;



int main(int argc, char* argv[])
{

    boost::asio::io_service io_service;

    tcp::resolver resolver(io_service);
    tcp::resolver::query query("localhost", "6543");
    tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

    tcp::socket socket(io_service);
    socket.connect(*endpoint_iterator); ///!!!!! TAK MA BYC !!!!!!
request req;
    
      //boost::array<char, 128> buf;
      char buf[5];
      char feedback[]={"12345"};
      boost::system::error_code error;
      boost::asio::mutable_buffers_1 buff((void *)buf,5);
      size_t siz;
      size_t len = socket.read_some(buff,error);
      
      /* if (error == boost::asio::error::eof)
       {  cout << "BYE!\n";   } // Connection closed cleanly by peer.
      else if (error)
      {
       cout << "ERROR\n";
       exit(0);
      }*/
      cout.flush();
      cout << feedback << endl;
      socket.write_some(boost::asio::buffer(HANDSHAKE_A),error);
      req.type=LOG;
      req.incoming_string=1;
      string_data user="m";
      string_data password="xxx";
      siz=sizeof(req);
      socket.write_some(boost::asio::buffer((void *)&siz,sizeof(size_t)));
      socket.write_some(boost::asio::buffer((void *)&req,siz));
      socket.write_some(boost::asio::buffer(user,128));
      socket.write_some(boost::asio::buffer(password,128));
      
      char loc[128]={"/home/maciek/mp3/"};
      
      req.type=LIST_DIR;
      
 
      siz=sizeof(req);
      socket.write_some(boost::asio::buffer((void *)&siz,sizeof(size_t)));
      socket.write_some(boost::asio::buffer((void *)&req,siz));
      socket.write_some(boost::asio::buffer(loc,128));
      //if (error || error!=boost::asio::error::eof)
      //	cout << "ERR";
      
    dir_data d;
    socket.read_some(boost::asio::buffer((void *)&siz,sizeof(size_t)));
    socket.read_some(boost::asio::buffer((void *)&siz,siz));
    cout << "S: " << siz << endl;
    cout.flush();
    for(int i=0; i<siz; i++)
    {
      size_t len;
      unsigned char id;
      socket.read_some(boost::asio::buffer((void *)&len,sizeof(size_t)));
      char *str=new char[len];
      socket.read_some(boost::asio::buffer((void *)str,len));
      cout << str << ":";
      socket.read_some(boost::asio::buffer((void *)&len,sizeof(size_t)));
      socket.read_some(boost::asio::buffer((void *)&id,len));
      cout << (id+48) << endl;
      cout.flush();
      delete str;
    }
    
  
   req.type=LOGOUT;
   socket.write_some(boost::asio::buffer((void *)&siz,sizeof(size_t)));
   socket.write_some(boost::asio::buffer((void *)&req,siz));

  return 0;
}