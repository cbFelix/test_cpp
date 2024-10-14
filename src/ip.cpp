#include "ip.hpp"

#include <iostream>

using namespace std;

IPAddress::IPAddress(const string ip, AddressFamily addressFamily) {
    if(addressFamily == AddressFamily::IPv4) {
        if(!isValidIPv4(ip)) {
            throw invalid_argument("Invalid IPv4 address");
        }
        _family = addressFamily;
    }
    else if (addressFamily == AddressFamily::IPv6) {
        if(!isValidIPv6(ip)) {
            throw invalid_argument("Invalid IPv6 address");
        }
        _family = addressFamily;
    }
    else {
        throw invalid_argument("Invalid address family");
    }
    _ip = ip;
}

string IPAddress::toString() {
    return _ip;
}

bool IPAddress::isValidIPv4(const string ip) {
    int numDots = 0;
    string segment;
    for (char ch : ip) {
        if (ch == '.') {
            if (!isValidIPv4Segment(segment)) return false;
            segment.clear();
            numDots++;
        } else if (!isdigit(ch)) {
            return false;
        } else {
            segment += ch;
        }
    }

    if (!isValidIPv4Segment(segment)) return false;
    return numDots == 3;
}

bool IPAddress::isValidIPv6(const string& ip) {
    if (ip.empty()) return false;
    
    int numColons = 0;  
    int numSegments = 0;   
    std::string segment;
    bool doubleColon = false;
    
    for (size_t i = 0; i < ip.length(); ++i) {
        char ch = ip[i];

        if (ch == ':') {
            if (i > 0 && ip[i-1] == ':') {  
                if (doubleColon) {
                    throw(invalid_argument("You can't use the 'double colon' twice"));
                    return false;
                }
                doubleColon = true;
            } else {
                if (!segment.empty()) {
                    if (!isValidIPv6Segment(segment)) return false;
                    segment.clear();
                    numSegments++;
                }
            }
            numColons++;
        } else if (std::isxdigit(ch)) {
            segment += ch;
        } else {
            throw(invalid_argument("Invalid character: " + string(1, ch)));
            return false;
        }
    }

    if (!segment.empty()) {
        if (!isValidIPv6Segment(segment)) return false;
        numSegments++;
    }

    if (numColons > 7 || (!doubleColon && numSegments != 8) || (doubleColon && numSegments >= 8)) {
        return false;
    }

    return true;
}

bool IPAddress::isValidIPv4Segment(const string segment) {
    if (segment.empty() || segment.length() > 3) return false;
    if (segment.length() > 1 && segment[0] == '0') return false;
    int value = stoi(segment);
    return value >= 0 && value <= 255;
}

bool IPAddress::isValidIPv6Segment(const string& segment) {
    if (segment.empty() || segment.length() > 4) {
        return false;
    }

    for (char ch : segment) {
        if (!std::isxdigit(ch)) {
            throw(invalid_argument("Invalid character"));
            return false; 
        }
    }

    return true;
}


AddressFamily IPAddress::getFamliy() {
    return _family;
}

bool IPAddress::isIPv4() const{
    return _family == AddressFamily::IPv4;
}

bool IPAddress::isIPv6() const {
    return _family == AddressFamily::IPv4;
}

bool IPAddress::operator==(const IPAddress& other) const {
    return this->_ip == other._ip && this->_family == other._family;
}

bool IPAddress::operator!=(const IPAddress& other) const {
    return !(*this == other);
}

bool IPAddress::operator<(const IPAddress& other) const {
    if (this->_family != other._family) {
        return this->_family < other._family; 
    }
    return this->_ip < other._ip; 
}

bool IPAddress::operator>(const IPAddress& other) const {
    return other < *this;
}

bool IPAddress::isLoopback() const {
    if (_family == AddressFamily::IPv4) {
        return _ip == "127.0.0.1";
    } else if (_family == AddressFamily::IPv6) {
        return _ip == "::1";
    }
    return false;
}

bool IPAddress::isPrivate() const {
    if (_family == AddressFamily::IPv4) {
        return _ip.find("10.") == 0 ||  // 10.0.0.0/8
               (_ip.find("172.") == 0 && // 172.16.0.0 - 172.31.255.255
                (stoi(_ip.substr(4, 2)) >= 16 && stoi(_ip.substr(4, 2)) <= 31)) ||
               _ip.find("192.168.") == 0; // 192.168.0.0/16
    } else if (_family == AddressFamily::IPv6) {
        return _ip.find("fc") == 0 || _ip.find("fd") == 0;
    }
    return false;
}

bool IPAddress::isLinkLocal() const {
    if (_family == AddressFamily::IPv4) {
        return _ip.find("169.254.") == 0;
    } else if (_family == AddressFamily::IPv6) {
        return _ip.find("fe80:") == 0; 
    }
    return false;
}

