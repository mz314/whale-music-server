#include "sockabstract.h"

sock_type sock_make()
{
 sock_type socketi;
 socketi=socket(AF_INET,SOCK_STREAM,0);
 if (socketi < 0 )
   return WHALE_ERROR_SOCKET;
}

sock_type sock_connect(sock_type sock,char *host,int port)
{
 struct hostent *server;
 struct sockaddr_in serv_addr;
 server=gethostbyname(host);
 if (!server)
   return WHALE_ERROR_NOHOST;
 serv_addr.sin_family = AF_INET;
 serv_addr.sin_addr.s_addr = INADDR_ANY;
 serv_addr.sin_port=htons((unsigned short)port);
 bzero((char *) &serv_addr, sizeof(serv_addr));
 serv_addr.sin_family = AF_INET;
 bcopy((char *)server->h_addr,
      (char *)&serv_addr.sin_addr.s_addr,
      server->h_length);
 serv_addr.sin_port = htons(port);
 if (connect(sock,&serv_addr,sizeof(serv_addr)) < 0)
  return WHALE_ERROR_NOCONNECT;
 return sock;
}

sock_type sock_disconnect(sock_type sock)
{
 close(sock);
}

size_type sock_read(sock_type sock,buff_type buff,size_data size)
{
 size_data bytes_read=0;
 size_data total=0;
 while (total<size)  
 {
   bytes_read=read(sock,buff+total,size-total);
   total+=bytes_read;
   
}
 
   
 
 return bytes_read;
}

size_type sock_write(sock_type sock,buff_type buff,size_data size)
{
 size_type w=0;
 size_type total=0;
 while(total<size)  
 {
   w=write(sock,buff+total,size-total);
   total+=w;
   
}
 
 return w;
}