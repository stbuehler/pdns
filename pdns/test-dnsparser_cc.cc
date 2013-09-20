#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_NO_MAIN
#include <boost/test/unit_test.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/foreach.hpp>
#include <boost/tuple/tuple.hpp>
#include "dnsparser.hh"

BOOST_AUTO_TEST_SUITE(test_dnsparser_cc)

BOOST_AUTO_TEST_CASE(test_record_types) {
  string ret;

  static const char label_bytes[] =
    "\x01\x61\xc0\x0c" /* looping label. offset includes a dnsheader (12 bytes), points to first byte of label again */
    ;

  const vector<uint8_t> label_vector(label_bytes, label_bytes + sizeof(label_bytes) - 1);
  uint16_t frompos = 0;
  try {
    PacketReader::getLabelFromContent(label_vector, frompos, ret, 0);
    throw runtime_error(string("getLabelFromContent should have failed, got label: ") + ret);
  } catch (const MOADNSException &e) {
    /* FIXME: add some other check to prevent loops */
    BOOST_CHECK_EQUAL(string("Loop"), string(e.what()));
  }
}

BOOST_AUTO_TEST_SUITE_END()
