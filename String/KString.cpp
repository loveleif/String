#pragma once
#include "stdafx.h"
#include "KString.h"

/* As strcpy but returns the end of the new dest string */
char* CStringCopy(char* dest, const char* source) {
  #pragma warning(disable:4996)
  strcpy(dest, source);
  return dest + strlen(dest);
}

size_t CalcCapacity(size_t wish, const char* begin, const char* append) {
  size_t required = 0;
  if (begin) required += strlen(begin);
  if (append) required += strlen(append);
  return std::max(wish, required);
}

void String::Init(size_t capacity, const char* append) {
  _begin = nullptr;
  _end = nullptr;
  _capacity = 0;
  ReSize(capacity, append);
}

void String::ReSize(size_t new_capacity, const char* append) {
  if (new_capacity == capacity() && !append) return;
  
  _capacity = CalcCapacity(new_capacity, _begin, append);
  // Allocate memory
  char* new_string = new char[_capacity+1];
  // Copy data
  if (_begin) {
    _end = CStringCopy(new_string, _begin);
  } else {
    _end = new_string;
    *_end = '\0';
  }
  // Append
  if (append) _end = CStringCopy(_end, append);
  // Set _begin
  if (_begin) {
    char* old_begin = _begin;
    _begin = new_string;
    delete[] old_begin;
  } else {
    _begin = new_string;
  }
}

String& String::operator+=(const char* right) {
  size_t len_right = strlen(right);
  size_t required = len_right + size();
  if (required > capacity())
    ReSize((required * 3) / 2, right);
  else {
    memmove(_end, right, (len_right + 1) * sizeof(char));
    _end = _end + len_right;
  }
  return *this;
}

String& String::operator+=(const char right) {
  if (capacity() <= size())
    Grow();
  *_end = right;
  ++_end;
  *_end = '\0';
  return *this;
}

String& String::operator=(const String& string) { 
  if (this != &string) {
    if (string.size() > capacity())
      ReSize(string.size(), string.c_str());
    else
      _end = CStringCopy(_begin, string.c_str());
  }
  return *this;
}

void String::Move(String& other) {
  _begin = other._begin;
  _end = other._end;
  _capacity = other._capacity;
  other._begin = nullptr;
  other._end = nullptr;
  other._capacity = 0;
}

String::String(String&& other): _begin(nullptr), _end(nullptr), _capacity(0) {
  Move(other);
}

String& String::operator=(String&& other) {
  if (this != &other) {
    delete[] _begin;
    Move(other);
  }
  return *this;
}

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
