#ifndef IP_HPP
#define IP_HPP

#include <iostream>
#include <vector>

using namespace std;

enum class AddressFamily {IPv4, IPv6};

class IPAddress {
public:
    IPAddress(const string ip, AddressFamily addressFamily);

    string toString();
    AddressFamily getFamliy();

    bool isIPv4() const;
    bool isIPv6() const;

    bool operator==(const IPAddress& other) const;
    bool operator!=(const IPAddress& other) const;
    bool operator<(const IPAddress& other) const;
    bool operator>(const IPAddress& other) const;

    bool isLoopback() const;
    bool isPrivate() const;
    bool isLinkLocal() const;

protected:
    bool isValidIPv4(const string ip);
    bool isValidIPv6(const string& ip);
    bool isValidIPv4Segment(const string segment);
    bool isValidIPv6Segment(const string& segment);

private:
    AddressFamily _family;
    string _ip;
};

#endif      //  IP_HPP