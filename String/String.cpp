#pragma once
#include "stdafx.h"
#include "String.h"

char* StrCpy(char* dest, const char* source) {
  for ( ; *source != '\0'; ++dest, ++source)
    *dest = *source;
  *dest = '\0';
  return dest;
}

size_t CalcCapacity(size_t wish, const char* begin, const char* append) {
  size_t required = 0;
  if (begin) required += strlen(begin);
  if (append) required += strlen(append);
  return std::max(wish+1, required);
}

void String::ReSize(size_t new_capacity, const char* append) {
  new_capacity = CalcCapacity(new_capacity, _begin, append);
  // Allocate memory
  char* new_string = new char[new_capacity+1];
  // Copy data
  if (_begin) {
    _end = StrCpy(new_string, _begin);
  } else {
    _end = new_string;
    *_end = '\0';
  }
  // Append
  if (append) _end = StrCpy(_end, append);
  // Set _begin
  if (_begin) {
    char* old_begin = _begin;
    _begin = new_string;
    delete[] old_begin;
  } else {
    _begin = new_string;
  }
  _capacity = new_capacity;
}

String& String::operator+=(const char* right) {
  size_t required = strlen(right) + size();
  if (required > _capacity)
    // Append using ReSize makes it possible to use this->_string as right
    ReSize((required * 4) / 3, right);
  else
    _end = StrCpy(_end, right);
  return *this;
}