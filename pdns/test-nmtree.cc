#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <boost/test/unit_test.hpp>
#include <bitset>
#include "iputils.hh"

using namespace boost;

BOOST_AUTO_TEST_SUITE(nmtree)

BOOST_AUTO_TEST_CASE(test_basic) {
  NetmaskTree<int> nmt;
  nmt.insert_or_assign(Netmask("130.161.252.0/24"), 0);
  nmt.insert_or_assign(Netmask("130.161.0.0/16"), 1);
  nmt.insert_or_assign(Netmask("130.0.0.0/8"), 2);

  BOOST_CHECK(!nmt.lookup(ComboAddress("213.244.168.210")));
  auto found=nmt.lookup(ComboAddress("130.161.252.29"));
  BOOST_CHECK(found);
  BOOST_CHECK_EQUAL(found->value(), 0);
  found=nmt.lookup(ComboAddress("130.161.180.1"));
  BOOST_CHECK(found);
  BOOST_CHECK_EQUAL(found->value(), 1);

  BOOST_CHECK_EQUAL(nmt.lookup(ComboAddress("130.255.255.255"))->value(), 2);
  BOOST_CHECK_EQUAL(nmt.lookup(ComboAddress("130.161.252.255"))->value(), 0);
  BOOST_CHECK_EQUAL(nmt.lookup(ComboAddress("130.161.253.255"))->value(), 1);

  found=nmt.lookup(ComboAddress("130.145.180.1"));
  BOOST_CHECK(found);
  BOOST_CHECK_EQUAL(found->value(), 2);

  nmt.clear();
  BOOST_CHECK(!nmt.lookup(ComboAddress("130.161.180.1")));

  nmt.insert_or_assign(Netmask("::1"), 1);
  nmt.insert_or_assign(Netmask("::/0"), 0);
  nmt.insert_or_assign(Netmask("fe80::/16"), 2);
  BOOST_CHECK(!nmt.lookup(ComboAddress("130.161.253.255")));
  BOOST_CHECK_EQUAL(nmt.lookup(ComboAddress("::2"))->value(), 0);
  BOOST_CHECK_EQUAL(nmt.lookup(ComboAddress("::ffff"))->value(), 0);
  BOOST_CHECK_EQUAL(nmt.lookup(ComboAddress("::1"))->value(), 1);
  BOOST_CHECK_EQUAL(nmt.lookup(ComboAddress("fe80::1"))->value(), 2);
}

BOOST_AUTO_TEST_CASE(test_single) {
  NetmaskTree<bool> nmt;
  nmt.insert_or_assign(Netmask("127.0.0.0/8"), 1);
  BOOST_CHECK_EQUAL(nmt.lookup(ComboAddress("127.0.0.1"))->value(), 1);
}

BOOST_AUTO_TEST_CASE(test_scale) {
  string start="192.168.";
  NetmaskTree<int> works;
  for(int i=0; i < 256; ++i) {
    for(int j=0; j < 256; ++j) {
      works.insert_or_assign(Netmask(start+std::to_string(i)+"."+std::to_string(j)), i*j);
    }
  }

  for(int i=0; i < 256; ++i) {
    for(int j=0; j < 256; ++j) {
      BOOST_CHECK_EQUAL(works.lookup(ComboAddress(start+std::to_string(i)+"."+std::to_string(j)))->value(), i*j);
    }
  }

  start="130.161.";
  for(int i=0; i < 256; ++i) {
    for(int j=0; j < 256; ++j) {
      BOOST_CHECK(!works.lookup(ComboAddress(start+std::to_string(i)+"."+std::to_string(j))));
    }
  }

  start="2000:123:";
  for(int i=0; i < 256; ++i) {
    for(int j=0; j < 256; ++j) {
      works.insert_or_assign(Netmask(start+std::to_string(i)+":"+std::to_string(j)+"::/64"), i*j);
    }
  }

  for(int i=0; i < 256; ++i) {
    for(int j=0; j < 256; ++j) {
      BOOST_CHECK_EQUAL(works.lookup(ComboAddress(start+std::to_string(i)+":"+std::to_string(j)+"::"+std::to_string(i)+":"+std::to_string(j)))->value(), i*j);
    }
  }

  start="2001:123:";
  for(int i=0; i < 256; ++i) {
    for(int j=0; j < 256; ++j) {
      BOOST_CHECK(!works.lookup(ComboAddress(start+std::to_string(i)+":"+std::to_string(j)+"::"+std::to_string(i)+":"+std::to_string(j))));
    }
  }
}

BOOST_AUTO_TEST_SUITE_END()
