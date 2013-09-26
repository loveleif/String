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

  /* Allocates new memory for this String. The optional append argument will be
   * appended before any deallocation (useful if you want to concatenate with
   * self). */
  void ReSize(size_t new_capacity, const char* append = nullptr);
  void Grow() { ReSize((_capacity * 3) / 2 + 1); }
public:
  String(size_t capacity = 10) { ReSize(capacity); }
  String(const String& str) { ReSize(str.size(), str.c_str()); }
  String(const String& str, size_t capacity) { ReSize(capacity, str.c_str()); }
  String(const char* cstr) { ReSize(strlen(cstr), cstr); }
  String(const std::string str) { ReSize(str.size(), str.c_str()); }
  ~String() { delete[] _begin; }

  size_t size() const { return _end - _begin; }
  size_t length() const { return size(); }
  const char* c_str() const { return _begin; }
  char& at(const size_t i) { 
	  if (i >= _capacity) throw std::out_of_range ("Index out of range.");
	  return (*this)[i];
  }
  char& operator[](const size_t i) { return *(_begin + i); }
  const char& operator[](const size_t i) const { return (*this)[i]; }
  void push_back(const char c) { (*this) += c; }
  void reserve(size_t n) { ReSize(n); }
  size_t capacity() const { return _capacity; }
  void shrink_to_fit() { ReSize(size()); }

  String& operator+=(const char* right);
  String& operator+=(const char right);
  String& operator+=(const String& right) { return *this += right.c_str(); }
  String& operator+=(const std::string& right) { return *this += right.c_str(); }
};

String operator+(const String& left, const String& right);
bool operator==(const String& left, const String& right);
bool operator==(const char* left, const String& right);
bool operator==(const String& left, const char* right);
std::ostream& operator<<(std::ostream& os, const String& s);
