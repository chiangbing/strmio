#include "bytes_utils.h"

using namespace strmio;


BytesUtils::BytesUtils() {}
BytesUtils::~BytesUtils() {}


char *BytesUtils::ReadBytes(std::istream &is, 
                            char bytes[],
                            int offset,
                            int len) {
  char *inBuf = bytes + offset;
  is.read(inBuf, len);
  return inBuf;
}


void BytesUtils::WriteBytes(std::ostream &os,
                            char bytes[],
                            int offset,
                            int len) {
  char *outBuf = bytes + offset;
  os.write(outBuf, len);
}


char BytesUtils::ReadByte(std::istream &is) {
  return (char) is.get();
}


void BytesUtils::WriteByte(std::ostream &os, char aByte) {
  os.put(aByte);
}


bool BytesUtils::ReadBool(std::istream &is) {
  int b = is.get();
  return (b == 1);
}


void BytesUtils::WriteBool(std::ostream &os, bool aBool) {
  char c = (aBool == true) ? 1 : 0;
  os.put(c);
}


int BytesUtils::ReadInt(std::istream &is) {
  int i = 0;
  char buf[4];

  is.read(buf, 4);
  i = 0xff & buf[0];
  i = (i << 8) | (0xff & buf[1]);
  i = (i << 8) | (0xff & buf[2]);
  i = (i << 8) | (0xff & buf[3]);
  return i;
}


void BytesUtils::WriteInt(std::ostream &os, int i) {
  char buf[4];

  buf[0] = (char) ((i >> 24) & 0xff);
  buf[1] = (char) ((i >> 16) & 0xff);
  buf[2] = (char) ((i >> 8) & 0xff);
  buf[3] = (char) (i & 0xff);
  os.write(buf, 4);
}


long BytesUtils::ReadLong(std::istream &is) {
  long l = 0;
  char buf[8];

  is.read(buf, 8);
  for (int i = 0; i < 8; i++) {
      l = (l << 8) | (0xff & buf[i]);
  }
  return l;
}


void BytesUtils::WriteLong(std::ostream &os, long l) {
  char buf[8];

  for (int i = 0; i < 8; ++i) {
      buf[i] = (char) ((l >> ((8 - 1 - i) * 8)) & 0xff);
  }
  os.write(buf, 8);
}


float BytesUtils::ReadFloat(std::istream &is) {
  // TODO(clay.chiang) not supported yet
  throw "not supported yet";
}


void BytesUtils::WriteFloat(std::ostream &os, float f) {
  // TODO(clay.chiang) not supported yet
  throw "not supported yet.";
}


double BytesUtils::ReadDouble(std::istream &is) {
  // TODO(clay.chiang) not supported yet
  throw "not supported yet";
}

void BytesUtils::WriteDouble(std::ostream &os, double d) {
  // TODO(clay.chiang) not supported yet
  throw "not supported yet";
}


std::string BytesUtils::ReadString(std::istream &is, int len) {
  char *buf = new char[len];

  is.read(buf, len);
  std::string s(buf, len);
  delete[] buf;
  return s;
}


void BytesUtils::WriteString(std::ostream &os, std::string s) {
  os << s;
}