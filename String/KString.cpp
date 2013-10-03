#pragma once
#include "stdafx.h"
#include "KString.h"

void String::ReSize(const size_t new_capacity, const char* append, const size_t len_append) {
  if (new_capacity == capacity() && !append) return;
  
  size_t old_size = size();
  _capacity = std::max(new_capacity, old_size + len_append);
  // Allocate memory
  char* new_string = new char[_capacity+1];
  // Copy data
  if (_begin) {
    #pragma warning(disable:4996)
    strcpy(new_string, _begin);
    _end = new_string + old_size;
  } else {
    _end = new_string;
    *_end = '\0';
  }
  // Append
  if (append) {
    memcpy(_end, append, len_append * sizeof(char));
    _end += len_append;
    *_end = '\0';
  }
  // Set _begin and delete old data
  if (_begin) {
    char* old_begin = _begin;
    _begin = new_string;
    delete[] old_begin;
  } else {
    _begin = new_string;
  }
}

String& String::Append(const char* source, const size_t n) {
  size_t new_size = size() + n;
  if (new_size > capacity()) {
    ReSize((new_size * 3) / 2, source, n);
  } else {
    memmove(_end, source, n * sizeof(char));
    _end += n;
    *_end = '\0';
  }
  return *this;
}

String& String::operator+=(const char* right) {
  return Append(right, strlen(right));
}

String& String::operator+=(const char right) {
  return Append(&right, 1);
}

String& String::operator=(const String& string) { 
  if (this != &string) {
    clear();
    Append(string.c_str(), string.size());
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
bool operator!=(const String& left, const String& right) { return !(left == right); }
bool operator!=(const char* left, const String& right) { return !(left == right); }
bool operator!=(const String& left, const char* right) { return !(left == right); }


std::ostream& operator<<(std::ostream& os, const String& s) {
  return os << s.c_str();
}
