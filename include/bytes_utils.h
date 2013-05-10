#ifndef STRMIO_BYTES_UTILS
#define STRMIO_BYTES_UTILS

#include <iostream>


namespace strmio
{

// BytesUtils provide tools to manipulate bytes.
class BytesUtils 
{
 public:
  // Read bytes from is.
  static char *ReadBytes(std::istream &is, 
                         char buf[], 
                         int offset, 
                         int len);

  // Write bytes to os.
  static void WriteBytes(std::ostream &os,
                         const char bytes[],
                         int offset,
                         int len);

  // Read a byte from is.
  static char ReadByte(std::istream &is);

  // Write a byte to os.
  static void WriteByte(std::ostream &os, char aByte);

  // Read a bool value from is.
  static bool ReadBool(std::istream &is);

  // Write a bool value to os.
  static void WriteBool(std::ostream &os, bool aBool);

  // Read an int from is.
  static int ReadInt(std::istream &is);

  // Write an int to os.
  static void WriteInt(std::ostream &os, int i);

  // Read a long from is.
  static long ReadLong(std::istream &is);

  // Write a long to os.
  static void WriteLong(std::ostream &os, long l);

  // Read a float from is.
  static float ReadFloat(std::istream &is);

  // Write a float to os.
  static void WriteFloat(std::ostream &os, float f);

  // Read a double from is.
  static double ReadDouble(std::istream &is);

  // Write a double to os.
  static void WriteDouble(std::ostream &os, double d);

  // Read a string of length len.
  static std::string ReadString(std::istream &is, int len);

  // Write a string.
  static void WriteString(std::ostream &os, std::string s);


 protected:
  BytesUtils();
  virtual ~BytesUtils();
};

}

#endif  // STRMIO_BYTES_UTILS