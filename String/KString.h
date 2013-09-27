// String.h
#pragma once
#include <cstring>
#include <string>
#include <iostream>
#include <algorithm>

class String {
  char* _begin; // Pointer to first char in string (is a c-string)
  char* _end; // Pointer to last+1 char in string
  size_t _capacity; // Number of chars this String can hold

  /* Allocates new memory for this String. The optional append argument will be
   * appended before any deallocation (useful if you want to concatenate with
   * self). */
  void ReSize(size_t new_capacity, const char* append = nullptr, const size_t len_append = 0);
  /* Initializes this String */
  void Init(size_t capacity, const char* append = nullptr);
  /* Increase capacity by 50 % */
  void Grow() { ReSize((_capacity * 3) / 2 + 1); }
  /* Help function for the Move operators */
  void Move(String& other);
  /* Help function for append operations */
  String& Append(const char* source, size_t n);
public:
  // Constructors
  String(size_t capacity = 10) { Init(capacity); }
  String(const String& str) { Init(str.size(), str.c_str()); }
  String(const String& str, size_t capacity) { Init(capacity, str.c_str()); }
  String(const char* cstr) { Init(strlen(cstr), cstr); }
  String(const std::string str) { Init(str.size(), str.c_str()); }
  // Move constructor
  String(String&& other);

  // Assignment
  String& operator=(const String& string);
  // Move assignment
  String& operator=(String&& other);

  // Destructor
  ~String() { delete[] _begin; }

  // Various methods that follow the std::string interface
  size_t size() const { return _end - _begin; }
  size_t length() const { return size(); }
  const char* c_str() const { return _begin; }
  char& at(const size_t i) { 
	  if (i >= size()) throw std::out_of_range ("Index out of range.");
	  return (*this)[i];
  }
  char& operator[](const size_t i) { return *(_begin + i); }
  const char& operator[](const size_t i) const { return (*this)[i]; }
  void push_back(const char c) { (*this) += c; }
  void reserve(size_t n) { if (n > capacity()) ReSize(n); }
  size_t capacity() const { return _capacity; }
  void shrink_to_fit() { ReSize(size()); }
  void clear() { 
	  *_begin = '\0';
	  _end = _begin;
  }

  // Compound assignment operators
  String& operator+=(const char* right);
  String& operator+=(const char right);
  String& operator+=(const String& right) { return *this += right.c_str(); }
  String& operator+=(const std::string& right) { return *this += right.c_str(); }
};

// Addition
String operator+(const String& left, const String& right);

// Relational operators
bool operator==(const String& left, const String& right);
bool operator==(const char* left, const String& right);
bool operator==(const String& left, const char* right);

// Stream operators
std::ostream& operator<<(std::ostream& os, const String& s);
