/*
    PowerDNS Versatile Database Driven Nameserver
    Copyright (C) 2002 - 2014  PowerDNS.COM BV

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 2
    as published by the Free Software Foundation

    Additionally, the license of this program contains a special
    exception which allows to distribute the program in binary form when
    it is linked against OpenSSL.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#ifndef PDNS_IPUTILSHH
#define PDNS_IPUTILSHH

#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <stdio.h>
#include <functional>
#include <bitset>
#include "pdnsexception.hh"
#include "misc.hh"
#include "radix_tree.hh"
#include <sys/socket.h>
#include <netdb.h>
#include <sstream>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>

#include "namespaces.hh"

#ifdef __APPLE__
#include <libkern/OSByteOrder.h>

#define htobe16(x) OSSwapHostToBigInt16(x)
#define htole16(x) OSSwapHostToLittleInt16(x)
#define be16toh(x) OSSwapBigToHostInt16(x)
#define le16toh(x) OSSwapLittleToHostInt16(x)

#define htobe32(x) OSSwapHostToBigInt32(x)
#define htole32(x) OSSwapHostToLittleInt32(x)
#define be32toh(x) OSSwapBigToHostInt32(x)
#define le32toh(x) OSSwapLittleToHostInt32(x)

#define htobe64(x) OSSwapHostToBigInt64(x)
#define htole64(x) OSSwapHostToLittleInt64(x)
#define be64toh(x) OSSwapBigToHostInt64(x)
#define le64toh(x) OSSwapLittleToHostInt64(x)
#endif

union ComboAddress {
  struct sockaddr_in sin4;
  struct sockaddr_in6 sin6;

  bool operator==(const ComboAddress& rhs) const
  {
    if(boost::tie(sin4.sin_family, sin4.sin_port) != boost::tie(rhs.sin4.sin_family, rhs.sin4.sin_port))
      return false;
    if(sin4.sin_family == AF_INET)
      return sin4.sin_addr.s_addr == rhs.sin4.sin_addr.s_addr;
    else
      return memcmp(&sin6.sin6_addr.s6_addr, &rhs.sin6.sin6_addr.s6_addr, 16)==0;
  }

  bool operator<(const ComboAddress& rhs) const
  {
    if(boost::tie(sin4.sin_family, sin4.sin_port) < boost::tie(rhs.sin4.sin_family, rhs.sin4.sin_port))
      return true;
    if(boost::tie(sin4.sin_family, sin4.sin_port) > boost::tie(rhs.sin4.sin_family, rhs.sin4.sin_port))
      return false;
    
    if(sin4.sin_family == AF_INET)
      return sin4.sin_addr.s_addr < rhs.sin4.sin_addr.s_addr;
    else
      return memcmp(&sin6.sin6_addr.s6_addr, &rhs.sin6.sin6_addr.s6_addr, 16) < 0;
  }

  bool operator>(const ComboAddress& rhs) const
  {
    if(boost::tie(sin4.sin_family, sin4.sin_port) > boost::tie(rhs.sin4.sin_family, rhs.sin4.sin_port))
      return true;
    if(boost::tie(sin4.sin_family, sin4.sin_port) < boost::tie(rhs.sin4.sin_family, rhs.sin4.sin_port))
      return false;
    
    if(sin4.sin_family == AF_INET)
      return sin4.sin_addr.s_addr > rhs.sin4.sin_addr.s_addr;
    else
      return memcmp(&sin6.sin6_addr.s6_addr, &rhs.sin6.sin6_addr.s6_addr, 16) > 0;
  }

  struct addressOnlyLessThan: public std::binary_function<ComboAddress, ComboAddress, bool>
  {
    bool operator()(const ComboAddress& a, const ComboAddress& b) const
    {
      if(a.sin4.sin_family < b.sin4.sin_family)
        return true;
      if(a.sin4.sin_family > b.sin4.sin_family)
        return false;
      if(a.sin4.sin_family == AF_INET)
        return a.sin4.sin_addr.s_addr < b.sin4.sin_addr.s_addr;
      else
        return memcmp(&a.sin6.sin6_addr.s6_addr, &b.sin6.sin6_addr.s6_addr, 16) < 0;
    }
  };

  struct addressOnlyEqual: public std::binary_function<ComboAddress, ComboAddress, bool>
  {
    bool operator()(const ComboAddress& a, const ComboAddress& b) const
    {
      if(a.sin4.sin_family != b.sin4.sin_family)
        return false;
      if(a.sin4.sin_family == AF_INET)
        return a.sin4.sin_addr.s_addr == b.sin4.sin_addr.s_addr;
      else
        return !memcmp(&a.sin6.sin6_addr.s6_addr, &b.sin6.sin6_addr.s6_addr, 16);
    }
  };


  socklen_t getSocklen() const
  {
    if(sin4.sin_family == AF_INET)
      return sizeof(sin4);
    else
      return sizeof(sin6);
  }
  
  ComboAddress() 
  {
    sin4.sin_family=AF_INET;
    sin4.sin_addr.s_addr=0;
    sin4.sin_port=0;
  }

  ComboAddress(const struct sockaddr *sa, socklen_t salen) {
    setSockaddr(sa, salen);
  };

  ComboAddress(const struct sockaddr_in6 *sa) {
    setSockaddr((const struct sockaddr*)sa, sizeof(struct sockaddr_in6));
  };

  ComboAddress(const struct sockaddr_in *sa) {
    setSockaddr((const struct sockaddr*)sa, sizeof(struct sockaddr_in));
  };

  void setSockaddr(const struct sockaddr *sa, socklen_t salen) {
    if (salen > sizeof(struct sockaddr_in6)) throw PDNSException("ComboAddress can't handle other than sockaddr_in or sockaddr_in6");
    memcpy(this, sa, salen);
  }

  // 'port' sets a default value in case 'str' does not set a port
  explicit ComboAddress(const string& str, uint16_t port=0)
  {
    memset(&sin6, 0, sizeof(sin6));
    sin4.sin_family = AF_INET;
    sin4.sin_port = 0;
    if(makeIPv4sockaddr(str, &sin4)) {
      sin6.sin6_family = AF_INET6;
      if(makeIPv6sockaddr(str, &sin6) < 0)
        throw PDNSException("Unable to convert presentation address '"+ str +"'"); 
      
    }
    if(!sin4.sin_port) // 'str' overrides port!
      sin4.sin_port=htons(port);
  }

  bool isMappedIPv4()  const
  {
    if(sin4.sin_family!=AF_INET6)
      return false;
    
    int n=0;
    const unsigned char*ptr = (unsigned char*) &sin6.sin6_addr.s6_addr;
    for(n=0; n < 10; ++n)
      if(ptr[n])
        return false;
    
    for(; n < 12; ++n)
      if(ptr[n]!=0xff)
        return false;
    
    return true;
  }
  
  ComboAddress mapToIPv4() const
  {
    if(!isMappedIPv4())
      throw PDNSException("ComboAddress can't map non-mapped IPv6 address back to IPv4");
    ComboAddress ret;
    ret.sin4.sin_family=AF_INET;
    ret.sin4.sin_port=sin4.sin_port;
    
    const unsigned char*ptr = (unsigned char*) &sin6.sin6_addr.s6_addr;
    ptr+=12;
    memcpy(&ret.sin4.sin_addr.s_addr, ptr, 4);
    return ret;
  }

  string toString() const
  {
    char host[1024];
    getnameinfo((struct sockaddr*) this, getSocklen(), host, sizeof(host),0, 0, NI_NUMERICHOST);
      
    return host;
  }

  string toStringWithPort() const
  {
    if(sin4.sin_family==AF_INET)
      return toString() + ":" + std::to_string(ntohs(sin4.sin_port));
    else
      return "["+toString() + "]:" + std::to_string(ntohs(sin4.sin_port));
  }

  void truncate(unsigned int bits);
};

/** This exception is thrown by the Netmask class and by extension by the NetmaskGroup class */
class NetmaskException: public PDNSException 
{
public:
  NetmaskException(const string &a) : PDNSException(a) {}
};

inline ComboAddress makeComboAddress(const string& str)
{
  ComboAddress address;
  address.sin4.sin_family=AF_INET;
  if(inet_pton(AF_INET, str.c_str(), &address.sin4.sin_addr) <= 0) {
    address.sin4.sin_family=AF_INET6;
    if(makeIPv6sockaddr(str, &address.sin6) < 0)
      throw NetmaskException("Unable to convert '"+str+"' to a netmask");        
  }
  return address;
}

/** This class represents a netmask and can be queried to see if a certain
    IP address is matched by this mask */
class Netmask
{
public:
  Netmask()
  {
	d_network.sin4.sin_family=0; // disable this doing anything useful
	d_mask=0;
	d_bits=0;
  }
  
  Netmask(const ComboAddress& network, uint8_t bits=0xff)
  {
    d_network = network;
    
    if(bits == 0xff)
      bits = (network.sin4.sin_family == AF_INET) ? 32 : 128;
    
    d_bits = bits;
    if(d_bits<32)
      d_mask=~(0xFFFFFFFF>>d_bits);
    else
      d_mask=0xFFFFFFFF; // not actually used for IPv6
  }
  
  //! Constructor supplies the mask, which cannot be changed 
  Netmask(const string &mask) 
  {
    pair<string,string> split=splitField(mask,'/');
    d_network=makeComboAddress(split.first);
    
    if(!split.second.empty()) {
      d_bits = pdns_stou(split.second);
      if(d_bits<32)
        d_mask=~(0xFFFFFFFF>>d_bits);
      else
        d_mask=0xFFFFFFFF;
    }
    else if(d_network.sin4.sin_family==AF_INET) {
      d_bits = 32;
      d_mask = 0xFFFFFFFF;
    }
    else {
      d_bits=128;
      d_mask=0;  // silence silly warning - d_mask is unused for IPv6
    }
  }

  bool match(const ComboAddress& ip) const
  {
    return match(&ip);
  }

  //! If this IP address in socket address matches
  bool match(const ComboAddress *ip) const
  {
    if(d_network.sin4.sin_family != ip->sin4.sin_family) {
      return false;
    }
    if(d_network.sin4.sin_family == AF_INET) {
      return match4(htonl((unsigned int)ip->sin4.sin_addr.s_addr));
    }
    if(d_network.sin6.sin6_family == AF_INET6) {
      uint8_t bytes=d_bits/8, n;
      const uint8_t *us=(const uint8_t*) &d_network.sin6.sin6_addr.s6_addr;
      const uint8_t *them=(const uint8_t*) &ip->sin6.sin6_addr.s6_addr;
      
      for(n=0; n < bytes; ++n) {
        if(us[n]!=them[n]) {
          return false;
        }
      }
      // still here, now match remaining bits
      uint8_t bits= d_bits % 8;
      uint8_t mask= ~(0xFF>>bits);

      return((us[n] & mask) == (them[n] & mask));
    }
    return false;
  }

  //! If this ASCII IP address matches
  bool match(const string &ip) const
  {
    ComboAddress address=makeComboAddress(ip);
    return match(&address);
  }

  //! If this IP address in native format matches
  bool match4(uint32_t ip) const
  {
    return (ip & d_mask) == (ntohl(d_network.sin4.sin_addr.s_addr) & d_mask);
  }

  string toString() const
  {
    if (empty()) return "any";
    return d_network.toString()+"/"+std::to_string((unsigned int)d_bits);
  }

  string toStringNoMask() const
  {
    return d_network.toString();
  }
  const ComboAddress& getNetwork() const
  {
    return d_network;
  }
  int getBits() const
  {
    return d_bits;
  }
  bool isIpv6() const 
  {
    return d_network.sin6.sin6_family == AF_INET6;
  }
  bool isIpv4() const
  {
    return d_network.sin4.sin_family == AF_INET;
  }

  bool operator<(const Netmask& rhs) const 
  {
    return tie(d_network, d_bits) < tie(rhs.d_network, rhs.d_bits);
  }

  bool operator==(const Netmask& rhs) const 
  {
    return tie(d_network, d_bits) == tie(rhs.d_network, rhs.d_bits);
  }

  bool empty() const 
  {
    return d_network.sin4.sin_family==0;
  }

protected:
  ComboAddress d_network;
  uint32_t d_mask;
  uint8_t d_bits;
};

class NetmaskBitstring : public Netmask {
public:
  NetmaskBitstring() = default;
  explicit NetmaskBitstring(Netmask const& other);
  explicit NetmaskBitstring(const ComboAddress& network, uint8_t bits);

  /* bitstring concept methods */

  /** length of bitstring including address-family indicator */
  size_t length() const {
    if (empty()) return 0;
    return 1 + d_bits;
  }

  /** return truncated Netmask: the truncated length includes the address-family indicator */
  NetmaskBitstring truncate(size_t bits) const;

  /** returned indexed bit in bitstring (starting with the address-family indicator) */
  bool operator[](size_t ndx) const;
};

bool operator==(NetmaskBitstring const& a, NetmaskBitstring const& b);
bool operator!=(NetmaskBitstring const& a, NetmaskBitstring const& b);
bool is_prefix(NetmaskBitstring const& prefix, NetmaskBitstring const& str);
NetmaskBitstring longest_common_prefix(NetmaskBitstring const& a, NetmaskBitstring const& b);

/* identity mapping */
struct Netmask_radix_tree_traits {
  typedef NetmaskBitstring bitstring;
  typedef Netmask value_type;

  bitstring value_to_bitstring(value_type const& val) {
    return bitstring(val);
  }

  value_type bitstring_to_value(bitstring const& bs) {
    return bs;
  }
};

/** Per-bit binary tree map implementation with <Netmask,T> pair.
 *
 * This is an binary tree implementation for storing attributes for IPv4 and IPv6 prefixes.
 * The most simple use case is simple NetmaskTree<bool> used by NetmaskGroup, which only
 * wants to know if given IP address is matched in the prefixes stored.
 *
 * This element is useful for anything that needs to *STORE* prefixes, and *MATCH* IP addresses
 * to a *LIST* of *PREFIXES*. Not the other way round.
 *
 * You can store IPv4 and IPv6 addresses to same tree, separate payload storage is kept per AFI.
 *
 * To erase something copy values to new tree sans the value you want to erase.
 *
 * Use swap if you need to move the tree to another NetmaskTree instance, it is WAY faster
 * than using copy ctor or assigment operator, since it moves the nodes and tree root to
 * new home instead of actually recreating the tree.
 *
 * Please see NetmaskGroup for example of simple use case. Other usecases can be found
 * from GeoIPBackend and Sortlist, and from dnsdist.
 */
template <typename T>
class NetmaskTree {
private:
  typedef radix_tree<Netmask, T, Netmask_radix_tree_traits> tree;

public:
  typedef typename tree::iterator iterator;
  typedef typename tree::const_iterator const_iterator;

  typedef Netmask key_type;
  typedef T value_type;
  typedef std::pair<key_type,value_type> node_type;
  typedef size_t size_type;

public:
  const_iterator begin() const { return m_tree.begin(); }
  const_iterator end() const { return m_tree.end(); }
  iterator begin() { return m_tree.begin(); }
  iterator end() { return m_tree.end(); }

  // Creates entry with default-constructed value if not already present; returns iterator for key
  iterator insert(const string &mask) {
    return insert(key_type(mask));
  }

  iterator insert(const key_type& key) {
    return m_tree.insert(key, value_type()).first;
  }

  //<! Creates, but does NOT update, value
  std::pair<iterator, bool> insert(const key_type& mask, const value_type& value) {
    return m_tree.insert(mask, value);
  }

  std::pair<iterator, bool> insert(const string& mask, const value_type& value) {
    return m_tree.insert(key_type(mask), value);
  }

  //<! Creates or updates value
  std::pair<iterator, bool> insert_or_assign(const key_type& mask, const value_type& value) {
    return m_tree.insert_or_assign(mask, value);
  }

  std::pair<iterator, bool> insert_or_assign(const string& mask, const value_type& value) {
    return insert_or_assign(key_type(mask), value);
  }

  //<! check if given key is present in TreeMap
  bool has_key(const key_type& key) const {
    return bool(m_tree.find_exact(key));
  }

  //<! Returns "best match" for key_type, might return end()
  const_iterator lookup(const key_type& key) const {
    return m_tree.find(key);
  }

  //<! Removes key from TreeMap.
  void erase(const key_type& key) {
    m_tree.erase(key);
  }

  void erase(const string& key) {
    erase(key_type(key));
  }

  //<! checks whether the container is empty.
  bool empty() const {
    return m_tree.empty();
  }

  //<! returns the number of elements
  size_type size() const {
    return m_tree.size();
  }

  //<! See if given ComboAddress matches any prefix
  bool match(const ComboAddress& value) const {
    return bool(lookup(key_type(value)));
  }

  bool match(const std::string& value) const {
    return match(ComboAddress(value));
  }

  //<! Clean out the tree
  void clear() {
    m_tree.clear();
  }

  //<! swaps the contents, rhs is left with nullptr.
  void swap(NetmaskTree& rhs) {
    using std::swap;
    swap(m_tree, rhs.m_tree);
  }

  friend void swap(NetmaskTree& a, NetmaskTree& b) {
    using std::swap;
    swap(a.m_tree, b.m_tree);
  }

private:
  tree m_tree;
};

/** This class represents a group of supplemental Netmask classes. An IP address matchs
    if it is matched by zero or more of the Netmask classes within.
*/
class NetmaskGroup
{
public:
  //! If this IP address is matched by any of the classes within

  bool match(const ComboAddress *ip) const
  {
    return tree.match(*ip);
  }

  bool match(const ComboAddress& ip) const
  {
    return match(&ip);
  }

  //! Add this string to the list of possible matches
  void addMask(const string &ip)
  {
    addMask(Netmask(ip));
  }

  //! Add this Netmask to the list of possible matches
  void addMask(const Netmask& nm)
  {
    tree.insert(nm, true);
  }

  void clear()
  {
    tree.clear();
  }

  bool empty() const
  {
    return tree.empty();
  }

  size_t size() const
  {
    return tree.size();
  }

  string toString() const
  {
    ostringstream str;
    bool first = true;
    for (auto const& entry: tree) {
      if (first) {
        str << ", ";
        first = false;
      }
      str << entry.key().toString();
    }
    return str.str();
  }

  void toStringVector(vector<string>* vec) const
  {
    for (auto const& entry: tree) {
      vec->push_back(entry.key().toString());
    }
  }

  void toMasks(const string &ips)
  {
    vector<string> parts;
    stringtok(parts, ips, ", \t");

    for (auto const& part: parts)
      addMask(part);
  }

private:
  NetmaskTree<bool> tree;
};


struct SComboAddress
{
  SComboAddress(const ComboAddress& orig) : ca(orig) {}
  ComboAddress ca;
  bool operator<(const SComboAddress& rhs) const
  {
    return ComboAddress::addressOnlyLessThan()(ca, rhs.ca);
  }
  operator const ComboAddress&()
  {
    return ca;
  }
};


int SSocket(int family, int type, int flags);
int SConnect(int sockfd, const ComboAddress& remote);
int SBind(int sockfd, const ComboAddress& local);
int SAccept(int sockfd, ComboAddress& remote);
int SListen(int sockfd, int limit);
int SSetsockopt(int sockfd, int level, int opname, int value);

#if defined(IP_PKTINFO)
  #define GEN_IP_PKTINFO IP_PKTINFO
#elif defined(IP_RECVDSTADDR)
  #define GEN_IP_PKTINFO IP_RECVDSTADDR 
#endif
bool IsAnyAddress(const ComboAddress& addr);
bool HarvestDestinationAddress(struct msghdr* msgh, ComboAddress* destination);
bool HarvestTimestamp(struct msghdr* msgh, struct timeval* tv);
void fillMSGHdr(struct msghdr* msgh, struct iovec* iov, char* cbuf, size_t cbufsize, char* data, size_t datalen, ComboAddress* addr);
int sendfromto(int sock, const char* data, int len, int flags, const ComboAddress& from, const ComboAddress& to);
#endif

extern template class NetmaskTree<bool>;
