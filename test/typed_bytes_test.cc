#include "gtest/gtest.h"
#include "typed_bytes.h"

#include <sstream>

namespace {

class TypedBytesTest : public ::testing::Test {
 protected:
  TypedBytesTest() {}
  virtual ~TypedBytesTest() {}
};


TEST(TypedBytesTest, ReadWriteSymmetry) {
  int testint = 123;
  long testlong = 1234567890;
  float testfloat = 1.23;
  double testdouble = 12345.789;
  std::string teststring = "123";
  char testbytes[] = {'1', '2', '3', '4'};
  size_t testbytes_len = 4;

  strmio::TypedBytes tb;
  std::ostringstream oss;

  tb.set_int_val(testint);
  tb.write(oss);
  tb.set_long_val(testlong);
  tb.write(oss);
  // tb.set_float_val(testfloat);
  // tb.write(oss);
  // tb.set_double_val(testdouble);
  // tb.write(oss);
  tb.set_string_val(teststring);
  tb.write(oss);
  tb.set_bytes_val(testbytes, testbytes_len);
  tb.write(oss);
  oss.flush();

  strmio::TypedBytes ntb;
  std::istringstream iss(oss.str());

  ntb.read(iss);
  ASSERT_EQ(strmio::TypedBytes::kTypeInt, ntb.type());
  ASSERT_EQ(testint, ntb.int_val());
  ntb.read(iss);
  ASSERT_EQ(strmio::TypedBytes::kTypeLong, ntb.type());
  ASSERT_EQ(testlong, ntb.long_val());
  ntb.read(iss);
  // ASSERT_EQ(strmio::TypedBytes::kTypeFloat, ntb.type());
  // ASSERT_FLOAT_EQ(testfloat, ntb.float_val());
  // ntb.read(iss);
  // ASSERT_EQ(strmio::TypedBytes::kTypeDouble, ntb.type());
  // ASSERT_DOUBLE_EQ(testdouble, ntb.double_val());
  // ntb.read(iss);
  ASSERT_EQ(strmio::TypedBytes::kTypeString, ntb.type());
  ASSERT_EQ(teststring, ntb.string_val());
  ntb.read(iss);
  ASSERT_EQ(strmio::TypedBytes::kTypeBytes, ntb.type());
  ASSERT_EQ(testbytes_len, ntb.bytes_val_len());
  ASSERT_TRUE(memcmp(testbytes, ntb.bytes_val(), ntb.bytes_val_len()) == 0);
}

TEST(TypedBytesTest, SetReadBytes) {
  char bytes1[] = {'1', '2', '3', '4'};
  size_t bytes1_len = 4;
  char bytes2[] = {'a', 'b', 'c'};
  size_t bytes2_len = 3;
  char bytes3[] = {'h', 'e', 'l', 'l', 'o', 'w', 'o', 'r', 'l', 'd'};
  size_t bytes3_len = 10;

  // make a istream with bytes1 and bytes3
  strmio::TypedBytes tb;
  std::ostringstream oss;
  tb.set_bytes_val(bytes1, bytes1_len);
  tb.write(oss);
  tb.set_bytes_val(bytes3, bytes3_len);
  tb.write(oss);
  oss.flush();
  std::istringstream iss(oss.str());

  strmio::TypedBytes ntb;
  ntb.set_bytes_val(bytes2, bytes2_len);
  ASSERT_EQ(bytes2_len, ntb.bytes_val_len());
  ASSERT_TRUE(memcmp(bytes2, ntb.bytes_val(), bytes2_len) == 0);

  // read bytes1 from iss
  ntb.read(iss);
  ASSERT_EQ(bytes1_len, ntb.bytes_val_len());
  ASSERT_TRUE(memcmp(bytes1, ntb.bytes_val(), bytes1_len) == 0);

  // read bytes3 from iss
  ntb.read(iss);
  ASSERT_EQ(bytes3_len, ntb.bytes_val_len());
  ASSERT_TRUE(memcmp(bytes3, ntb.bytes_val(), bytes3_len) == 0);
}

} // end of namespace


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
