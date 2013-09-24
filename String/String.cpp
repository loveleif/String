// This is the main DLL file.
#pragma once
#include "stdafx.h"

#include "String.h"
#include <cassert>

void String::Init(const char* base, size_t capacity) {
  if (base) _capacity = std::max(strlen(base)+1, capacity+1);
  else _capacity = capacity+1;

  _begin = new char[_capacity];
  if (base) {
    strcpy(_begin, base);
    _end = _begin + strlen(base);
  } else {
    *_begin = '\0';
    _end = _begin;
  }
}

char* FindEnd(char* start) {
  char* end;
  for (end = start; *end != '\0'; ++end) { }
  return end;
}

void String::ReSize(size_t new_capacity, const char* append) {
  if (new_capacity <= size()) return;
  // TODO Check for overflow with append?

  // Allocate memory
  char* new_string = new char[new_capacity];
  // Copy data
  strcpy(new_string, _begin);
  // Set end
  _end = new_string + (_end - _begin);
  // Append
  if (append) {
    strcpy(_end, append);
    _end = FindEnd(_end);
  }
  // Replace old string with new
  char* tmp = _begin;
  _begin = new_string;
  _capacity = new_capacity;
  delete[] tmp;
}

String& String::operator+=(const char* right) {
  size_t required = strlen(right) + size() + 1;
  if (required > _capacity) {
    // Append using ReSize makes it possible to use this->_string as right
    ReSize((required * 4) / 3, right);
  } else {
    strcpy(_end, right);
    _end = FindEnd(_end);
  }
  return *this;
}