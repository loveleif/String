// String.cpp : Some testing of the String class.
//
#include "stdafx.h"
#pragma once
#include "stdafx.h"
#include <cassert>

#include <Windows.h>

LARGE_INTEGER frequency;
LARGE_INTEGER lastTick;

double stopWatch() {
  assert(QueryPerformanceFrequency(&frequency));
  LARGE_INTEGER thisTick;

  QueryPerformanceCounter(&thisTick);

  double delta = ((double)thisTick.QuadPart - (double)lastTick.QuadPart) / (double)frequency.QuadPart;
  delta *= 1000.0;
  lastTick = thisTick;

  return delta;
}

#define _CRTDBG_MAP_ALLOC
#ifdef _DEBUG
	#ifndef DBG_NEW
		#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
		#define new DBG_NEW
	#endif
#endif  // _DEBUG
#include <stdlib.h>
#include <crtdbg.h>

#include "KString.h"

#include <string>
#include <string.h>
#include <iostream>
#include <cassert>
#include <utility>

void TestF�rGodk�ntString() {
//-	String()
	String s0;	assert (s0=="");
//-	String(Str�ng str�ng)
	String s1("foo"); assert(s1=="foo");
	String s2(s1); assert(s2=="foo");
	std::string a("hej");
	a.begin();
	String s3(std::string("bar"));
  std::cout << s3 << std::endl;
  assert(s3=="bar");

//-	~String() Kom ih�g destruktorn!
	delete new String("hej");

//	-	operator =(Str�ng str�ng)
	s2=s3;
	assert((s2=s3)==s3);
	assert((s2=s2)==s3);
	s2 = String("foo");
	assert(s2=="foo");
	assert((s2="bar")=="bar");

//-	operator+=(Str�ng str�ng) som tolkas som konkatenering.
	//foo, bar, bar
	(s2+=s1)+=(s3+=s1);
	assert(s3=="barfoo");
  assert(s1=="foo");
  assert(s2=="barfoobarfoo");

	//+= som f�r plats;
	s3="bar";
  s3.reserve(10);
	s3+=s1;
	assert(s3=="barfoo");

	//+= som inte f�r plats;
	s3="bar"; s3.reserve(5);
	s3+=s1;
	assert(s3=="barfoo");

	//+= som f�r plats; Sj�lv
	s3="bar"; s3.reserve(10);
	s3+=s3;
	assert(s3=="barbar");

	//+= som inte f�r plats; Sj�lv
	s3="bar"; s3.reserve(5);
	s3+=s3;
	assert(s3=="barbar");

//-	operator+ r�cker med bara String+String
	s2="bar";
	//auto sss=s1+s2;
	//sss=="foobar";
	//assert(sss=="foobar");
	////assert(s1+s2=="foobar" && s1=="foo");
	assert(s1+s2=="foobar" && s1=="foo");

//-	operator== r�cker med String==Str�ng
	//testas �verallt!

//-	at(int i) som indexerar med range check
  try {
	 s2.at(-1);
	 assert(false);
	} catch (std::out_of_range&) {};
	try {
	 s2.at(3);
	 assert(false);
	} catch (std::out_of_range&) {};
	assert(s2.at(2)='r');

//-	operator[](int i) som indexerar utan range check.
	s2[-1]; s2[1000];
	assert(s2[1]=='a');

//-	push_back(char c) l�gger till ett tecken sist.
	s2.push_back('a');
	assert(s2=="bara");

	//-	length(), reserve(), capacity() och shrink_to_fit() �r funktioner som finns i container klasserna i STL.

	int len=s2.length();
	s2.shrink_to_fit();
	assert(s2.length()==s2.capacity());

	s2.c_str();
	if(s2.length()==s2.capacity()) {
		//lagrar str�ngen med \0
		const char * p1 = s2.c_str();
		s2.reserve(len); assert(p1==s2.c_str()); //no change
		p1= s2.c_str(); s2.reserve(len+1); assert(p1!=s2.c_str()); //change
		p1= s2.c_str(); s2.shrink_to_fit();  assert(p1!=s2.c_str()); //change
		p1= s2.c_str(); s2.shrink_to_fit();  assert(p1==s2.c_str()); //no change
	} else {
		//lagrar str�ngen utan \0
		int cap;
		s2.c_str(); cap=s2.capacity(); s2.shrink_to_fit(); assert(cap!=s2.capacity()); //change
		cap=s2.capacity(); s2.c_str(); assert(cap!=s2.capacity()); //change
		s2.shrink_to_fit(); cap=s2.capacity(); s2.reserve(len); assert(cap==s2.capacity()); //change
		s2.reserve(len+1); assert(cap!=s2.capacity()); //change
	}

//-	const char* c_str()
	//tested above!

}

void TestF�rV�lGodk�ntString() {
	TestF�rGodk�ntString();
	const String c1;
	String s1("bar");
//-	Ha alla �const� exakt r�tt.
//-	F�r en del funktioner b�r man �ven ha en const och en icke const version, se nedan.
//f�ljande ska inte kompilera
	//c1[2]='a';
	//c1.at(2)='a';
	//c1+=s1;
	//(c1+=c1)="huj";

//f�ljande ska kompilera och k�ra
	s1[3]='a';	//fast det skriver �ver \0 p� slutet!
	s1[3]='\0';
	s1.at(2)='a';
	c1+c1;
	s1+=c1;

//-	Implementera en s� kallad move konstruktor se: http://en.cppreference.com/w/cpp/language/move_constructor. Den ska vara maximalt effektiv.
	s1="bar";
	String s2(std::move(s1));
	assert(s2=="bar" && s1.capacity()==0);

//-	Implementera �ven en move assignment operator.
	s1=std::move(s2);
	assert(s1=="bar" && s2.capacity()==0);

//-	Det hela ska vara �maximalt� effektivt � fast g� inte till �verdrift.:
//o	Om ni t.ex. samlat st�rre delen av koden f�r konstruktorerna i en hj�lpfunktion s� kostar det inte mycket - s�rskilt om ni �inlinar� den.
//o	Ni kan d�remot t�nka er att ni har mycket l�nga str�ngar, d� kostar on�dig kopierng av dem.
//o	All on�dig allokering av dynamiskt minne kostar!
//DETTA KAN MAN BARA KOLLA GENOM ATT TITTA P� KODEN

//-	operator[](int i) som indexerar utan range check � ni m�ste uppfylla �if pos == size(), a reference to the character with value CharT() (the null character) is returned.�
	s2=""; assert(s2[s2.length()]=='\0');
	s2="bar"; assert(s2[s2.length()]=='\0');

}

void TestIterator() {
  String s("abcdefghijklmnopqrstuvwxyz");
  s.reserve(256);

  String s2;

  for (auto i = s.begin(); i != s.end(); ++i) {
    s2 += *i;
  }
  assert(s==s2);
  s2.clear();
  assert(s!=s2);
  for (auto i = s.cbegin(); i != s.cend(); ++i) {
    s2 += *i;
  }
  assert(s==s2);
  s2.clear();
}


int main() {
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	//TestF�rGodk�ntString();
	//TestF�rV�lGodk�ntString();

  /*
  stopWatch();
  stopWatch();

  int a = 5;

  double elapsed = stopWatch();
  */

  TestIterator();

	std::cin.get();

}
