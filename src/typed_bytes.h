#ifndef STRMIO_TYPED_BYTES
#define STRMIO_TYPED_BYTES

#include <iostream>


namespace strmio
{

// Read from and Write to Hadoop streaming TypedBytes InputWriter/OutputReader.
class TypedBytes
{
 public:
  // Constructor.
  TypedBytes();

  // Deconstructor.
  virtual ~TypedBytes();

  // Populate this TypedBytes from is.
  bool read(std::istream &is);

  // Dump this TypedBytes to os.
  bool write(std::ostream &os);

  // type codes

  static const int kTypeBytes;
  static const int kTypeByte;
  static const int kTypeBool;
  static const int kTypeInt;
  static const int kTypeLong;
  static const int kTypeFloat;
  static const int kTypeDouble;
  static const int kTypeString;
  static const int kTypeVector;  // not support yet
  static const int kTypeList;  // not support yet
  static const int kTypeMap;  // not support yet

  // access type code
  int type() const {
    return type_;
  }

  // bytes accessor
  int bytes_val_len() const {
    return bytes_val_len_;
  }

  const char * bytes_val() const {
    return (bytes_val_via_ == kViaRead ? read_bytes_val_ : set_bytes_val_);
  }

  // bytes mutator
  void set_bytes_val(const char bytes[], int len) {
    type_ = kTypeBytes;
    set_bytes_val_ = bytes;
    bytes_val_len_ = len;
    bytes_val_via_ = kViaSet;
  }

  // byte accessor
  char byte_val() const {
    return byte_val_;
  }

  // byte mutator
  void set_byte_val(char byte) {
    type_ = kTypeByte;
    byte_val_ = byte;
  }

  // bool accessor
  bool bool_val() const {
    return bool_val_;
  }

  // bool mutator
  void set_bool_val(bool bool_val) {
    type_ = kTypeBool;
    bool_val_ = bool_val;
  }

  // int accessor
  int int_val() const {
    return int_val_;
  }

  // int mutator
  void set_int_val(int int_val) {
    type_ = kTypeInt;
    int_val_ = int_val;
  }

  // long accessor
  long long_val() const {
    return long_val_;
  }

  // long mutator
  void set_long_val(long long_val) {
    type_ = kTypeLong;
    long_val_ = long_val;
  }

  // float accessor
  float float_val() const {
    return float_val_;
  }

  // float mutator
  void set_float_val(float float_val) {
    type_ = kTypeFloat;
    float_val_ = float_val;
  }

  // double accessor
  double double_val() const {
    return double_val_;
  }

  // double mutator
  void set_double_val(double double_val) {
    type_ = kTypeDouble;
    double_val_ = double_val;
  }

  // string accessor
  std::string string_val() const {
    return string_val_;
  }

  // string mutator
  void set_string_val(const std::string &str_val) {
    type_ = kTypeString;
    string_val_ = str_val;
  }


private:
  // type of value
  int type_;

  // values, one of them will be set according to type_

  static const int kViaNull;
  static const int kViaSet;
  static const int kViaRead;

  // via set_bytes_val() or Read()
  int bytes_val_via_;
  // length of bytes_val
  int bytes_val_len_;
  // set via set_bytes_val()
  const char *set_bytes_val_;
  // set via Read()
  char *read_bytes_val_;
  
  char byte_val_;
  bool bool_val_;
  int int_val_;
  long long_val_;
  float float_val_;
  double double_val_;
  std::string string_val_;
};

}


#endif  // STRMIO_TYPED_BYTES