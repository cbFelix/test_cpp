#include <iostream>

#include "smartSocket.hpp"
#include "ip.hpp"

using namespace std;

int main() {
    try{
        IPAddress ip("192.132.127.1", AddressFamily::IPv4);

        cout << ip.toString() << " is IPv4: " << ip.isIPv4() << endl;

        IPAddress ipv6("2001:0db8:0000:0000:0000:ff00:0042:8329", AddressFamily::IPv6);

        cout << ipv6.toString() << " is IPv6: " << ip.isIPv6() << endl;


        return 0;
    }
    
    catch(exception& e) {
        cout << e.what() << endl;
        return -1;
    }
}
