#include "heavy_tasks.hpp"
#include <cstring>

void *fun(params_type params,size_t size,bool *abort)
{
 cout << "FUN\n";
 char *str=new char[10];
 strcpy(str,"BOO");
 bool ab=*abort;
 while (*abort==false)
 {
  bool ab=*abort;
   cout << (char *)params << ", " << size << endl;
  cout.flush();
 }
 return (void *)str;
}

int main()
{
  heavy_task task;
  char str[128]={"XXX"};
  int x;
  task.setup(fun,str,666);
  task.start();
  sleep(1);
  task.stop();
  cout << "FIN" << endl;
  
  cin >> x;
  cout << "I: " << (char *)task.returned();
  return 0;
}