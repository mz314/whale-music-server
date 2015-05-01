#include "httptest.hpp"
#include "sockets_http.hpp"
#include "logs.h";

using boost::asio::ip::tcp;

int main() {
    logs *log=logs::get_instance();
    cout << "Http test\n";
    sockets_http http(6666,log);
    return 0;
}
