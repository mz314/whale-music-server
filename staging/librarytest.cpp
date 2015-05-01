


#include <iostream>


extern "C" {

#include "../clientlib/whalelib.h"
};


using namespace std;

int main()
{
  cout << "Connectin\'" << endl;
  int sock;
  sock=whale_connect("localhost",6543);
  if (sock < 0 )
  { cout << sock << endl;
    return 11; }
  cout << "LOG: " <<  whale_log_user(sock,"m","xxx");
  dir_data *ddata;
  //ddata=whale_get_dir(sock,"/home/maciek/");
  //for (int i=0; i<ddata->n; i++)
   // cout << ddata->items[i].name << " - " << (ddata->items[i].is_file == 1 ? "F" : "D") << endl;
  //whale_dispose_dir_data(ddata);
  whale_play_file(sock,"/home/maciek/test.wav");
  whale_logout(sock);
  whale_disconnect(sock);
  return 0;
}