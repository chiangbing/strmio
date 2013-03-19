#include "typed_bytes.h"
#include "bytes_utils.h"
#include <cstdlib>
#include <sstream>


namespace strmio {

static std::string itoa(int number) {
  std::stringstream ss;
  ss << number;
  return ss.str();
}


const int TypedBytes::kTypeBytes = 0;
const int TypedBytes::kTypeByte = 1;
const int TypedBytes::kTypeBool = 2;
const int TypedBytes::kTypeInt = 3;
const int TypedBytes::kTypeLong = 4;
const int TypedBytes::kTypeFloat = 5;
const int TypedBytes::kTypeDouble = 6;
const int TypedBytes::kTypeString = 7;
const int TypedBytes::kTypeVector = 8;  // not support yet
const int TypedBytes::kTypeList = 9;  // not support yet
const int TypedBytes::kTypeMap = 10;  // not support yet

const int TypedBytes::kViaNull = 0;
const int TypedBytes::kViaSet = 1;
const int TypedBytes::kViaRead = 2;

TypedBytes::TypedBytes() 
    : read_bytes_val_(NULL),
      bytes_val_via_(kViaNull) {}


TypedBytes::~TypedBytes() {
  if (read_bytes_val_ != NULL) {
    delete[] read_bytes_val_;
    read_bytes_val_ = NULL;
  }
}


bool TypedBytes::read(std::istream &is) {
  type_ = is.get();
  switch (type_) {
    case kTypeBytes: {
      bytes_val_len_ = BytesUtils::ReadInt(is);
      if (read_bytes_val_ != NULL) {
        int old_buf_len = sizeof(read_bytes_val_) / sizeof(char);
        if (bytes_val_len_ > old_buf_len) {
          // re-allocate new buffer for read_bytes_val_
          delete[] read_bytes_val_;
          read_bytes_val_ = new char[bytes_val_len_];
        }
      } else {
        read_bytes_val_ = new char[bytes_val_len_];
      }
      BytesUtils::ReadBytes(is, read_bytes_val_, 0, bytes_val_len_);
      bytes_val_via_ = kViaRead;
      break;
    }
    case kTypeByte: {
      byte_val_ = BytesUtils::ReadByte(is);
      break;
    }
    case kTypeBool: {
      bool_val_ = BytesUtils::ReadBool(is);
      break;
    }
    case kTypeInt: {
      int_val_ = BytesUtils::ReadInt(is);
      break;
    }
    case kTypeLong: {
      long_val_ = BytesUtils::ReadLong(is);
      break;
    }
    case kTypeFloat: {
      float_val_ = BytesUtils::ReadFloat(is);
      break;
    }
    case kTypeDouble: {
      double_val_ = BytesUtils::ReadLong(is);
      break;
    }
    case kTypeString: {
      int len = BytesUtils::ReadInt(is);
      if (len > 0) {
        string_val_ = BytesUtils::ReadString(is, len);
      } else {
        string_val_ = "";
      }
      break;
    }
    default: {
      std::cerr << "not supported type: " << (char)type_ << std::endl;
      return false;
    }
  }
  return true;
}


bool TypedBytes::write(std::ostream &os) {
  os.put(type_);
  switch (type_) {
    case kTypeBytes: {
      char *bytes_val = bytes_val_via_ == kViaRead ? read_bytes_val_
                                                   : set_bytes_val_;
      BytesUtils::WriteInt(os, bytes_val_len_);
      BytesUtils::WriteBytes(os, bytes_val, 0, bytes_val_len_);
      break;
    }
    case kTypeByte: {
      BytesUtils::WriteByte(os, byte_val_);
      break;
    }
    case kTypeBool: {
      BytesUtils::WriteBool(os, bool_val_);
      break;
    }
    case kTypeInt: {
      BytesUtils::WriteInt(os, int_val_);
      break;
    }
    case kTypeLong: {
      BytesUtils::WriteLong(os, long_val_);
      break;
    }
    case kTypeFloat: {
      BytesUtils::WriteFloat(os, float_val_);
      break;
    }
    case kTypeDouble: {
      BytesUtils::WriteDouble(os, double_val_);
      break;
    }
    case kTypeString: {
      if (string_val_.empty()) {
        BytesUtils::WriteInt(os, -1);
      } else {
        BytesUtils::WriteInt(os, string_val_.length());
        BytesUtils::WriteString(os, string_val_);
      }
      break;
    }
    default: {
      std::cerr << "not supported type: " << (char)type_ << std::endl;
      return false;
    }
  }
  return true;
}

} // end of namespace strmio