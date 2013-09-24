// String.h
#pragma once
#include <string.h>
#include <string>
#include <iostream>
#include <algorithm>

class String {
  char* _begin;
  char* _end;
  size_t _capacity;

  void Init(const char* base = nullptr, size_t capacity = size_t(0));
  /* Allocates new memory for this String. The optional append argument will be
   * appended before any deallocation (useful if you want to concatenate with
   * self).
  */
  void ReSize(size_t new_capacity, const char* append = nullptr);
  void Grow() { ReSize((_capacity * 4) / 3 + 1); }
public:
  String(size_t capacity = 10) { Init(nullptr, capacity); }
  String(const String& string) { Init(string.c_str()); }
  String(const String& string, size_t capacity) { Init(string.c_str(), capacity); }
  String(const char* c_string) { Init(c_string); }
  String(const std::string std_string) { Init(std_string.c_str()); }
  ~String() { delete[] _begin; }

  size_t size() const { return _end - _begin; }
  size_t length() const { return size(); }
  const char* c_str() const { return _begin; }
  char& at(size_t i) { (i >= _capacity) ? NULL : (*this)[i]; }
  char& operator[](size_t i) { return *(_begin + i); }
  const char& operator[](size_t i) const { return (*this)[i]; }
  void push_back(char c) { *this += &c; }
  void reserve(size_t n) { ReSize(n+1); }
  size_t capacity() const { return _capacity; }
  void shrink_to_fit() { ReSize(size() + 1); }

  String& operator+=(const char* right);
  String& operator+=(const String& right) { return *this += right.c_str(); }
  String& operator+=(const std::string& right) { return *this += right.c_str(); }
};

String operator+(const String& left, const String& right) { 
  return String(left, left.size() + right.size() + 10) += right;
}

bool operator==(const String& left, const String& right) {
  return strcmp(left.c_str(), right.c_str()) == 0;
}
bool operator==(const char* left, const String& right) {
  return strcmp(left, right.c_str()) == 0;
}
bool operator==(const String& left, const char* right) {
  return right == left;
}

std::ostream& operator<<(std::ostream& os, const String& s) {
  return os << s.c_str();
}