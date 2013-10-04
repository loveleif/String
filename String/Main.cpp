#pragma once
// String.cpp : Some testing of the String class.
//
#include "stdafx.h"
#include <cassert>
#include <Windows.h>
#include <stdlib.h>
#include <crtdbg.h>
#include "KString.h"
#include <string>
#include <string.h>
#include <iostream>
#include <utility>

#define _CRTDBG_MAP_ALLOC
#ifdef _DEBUG
	#ifndef DBG_NEW
		#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
		#define new DBG_NEW
	#endif
#endif  // _DEBUG


using namespace std;

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

void TestFörGodkäntString() {
//-	String()
	String s0;	assert (s0=="");

//-	String(Sträng sträng)
	String s1("foo"); assert(s1=="foo");
	String s2(s1); assert(s2=="foo");
	String s3(string("bar"));  assert(s3=="bar");

//-	~String() Kom ihåg destruktorn!
	delete new String("hej");

//	-	operator =(Sträng sträng)
	assert((s2=s3)==s3);
	assert((s2=s2)==s3);
	assert((s2=(string("foo")))=="foo");
	assert((s2="bar")=="bar");

//-	operator+=(Sträng sträng) som tolkas som konkatenering.
	//foo, bar, bar
	(s2+=s1)+=(s3+=s1);
	assert(s3=="barfoo" && s2=="barfoobarfoo" && s1=="foo");

	//+= som får plats;
	s3="bar"; s3.reserve(10);
	s3+=s1;
	assert(s3=="barfoo");

	//+= som inte får plats;
	s3="bar"; s3.reserve(5);
	s3+=s1;
	assert(s3=="barfoo");

	//+= som får plats; Själv
	s3="bar"; s3.reserve(10);
	s3+=s3;
	assert(s3=="barbar");

	//+= som inte får plats; Själv
	s3="bar"; s3.reserve(5);
	s3+=s3;
	assert(s3=="barbar");

//-	operator+ räcker med bara String+String
	s2="bar";
	//auto sss=s1+s2;
	//sss=="foobar";
	//assert(sss=="foobar");
	////assert(s1+s2=="foobar" && s1=="foo");
	assert(s1+s2=="foobar" && s1=="foo");

//-	operator== räcker med String==Sträng
	//testas överallt!

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

//-	push_back(char c) lägger till ett tecken sist.
	s2.push_back('a');
	assert(s2=="bara");

	//-	length(), reserve(), capacity() och shrink_to_fit() är funktioner som finns i container klasserna i STL.

	int len=s2.length();
	s2.shrink_to_fit();
	assert(s2.length()==s2.capacity());

	s2.c_str();
	if(s2.length()==s2.capacity()) {
		//lagrar strängen med \0
		const char * p1 = s2.c_str();
		s2.reserve(len); assert(p1==s2.c_str()); //no change
		p1= s2.c_str(); s2.reserve(len+1); assert(p1!=s2.c_str()); //change
		p1= s2.c_str(); s2.shrink_to_fit();  assert(p1!=s2.c_str()); //change
		p1= s2.c_str(); s2.shrink_to_fit();  assert(p1==s2.c_str()); //no change
	} else {
		//lagrar strängen utan \0
		int cap;
		s2.c_str(); cap=s2.capacity(); s2.shrink_to_fit(); assert(cap!=s2.capacity()); //change
		cap=s2.capacity(); s2.c_str(); assert(cap!=s2.capacity()); //change
		s2.shrink_to_fit(); cap=s2.capacity(); s2.reserve(len); assert(cap==s2.capacity()); //change
		s2.reserve(len+1); assert(cap!=s2.capacity()); //change
	}

//-	const char* c_str()
	//tested above!

}

void TestFörVälGodkäntString() {
	TestFörGodkäntString();
	const String c1;
	String s1("bar");
//-	Ha alla ”const” exakt rätt.
//-	För en del funktioner bör man även ha en const och en icke const version, se nedan.
//följande ska inte kompilera
	//c1[2]='a';
	//c1.at(2)='a';
	//c1+=s1;
	//(c1+=c1)="huj";

//följande ska kompilera och köra
	s1[3]='a';	//fast det skriver över \0 på slutet!
	s1[3]='\0';
	s1.at(2)='a';
	c1+c1;
	s1+=c1;

//-	Implementera en så kallad move konstruktor se: http://en.cppreference.com/w/cpp/language/move_constructor. Den ska vara maximalt effektiv.
	s1="bar";
	String s2(std::move(s1));
	assert(s2=="bar" && s1.capacity()==0);

//-	Implementera även en move assignment operator.
	s1=std::move(s2);
	assert(s1=="bar" && s2.capacity()==0);

//-	Det hela ska vara ”maximalt” effektivt – fast gå inte till överdrift.:
//o	Om ni t.ex. samlat större delen av koden för konstruktorerna i en hjälpfunktion så kostar det inte mycket - särskilt om ni ”inlinar” den.
//o	Ni kan däremot tänka er att ni har mycket långa strängar, då kostar onödig kopierng av dem.
//o	All onödig allokering av dynamiskt minne kostar!
//DETTA KAN MAN BARA KOLLA GENOM ATT TITTA PÅ KODEN

//-	operator[](int i) som indexerar utan range check – ni måste uppfylla ”if pos == size(), a reference to the character with value CharT() (the null character) is returned.”
	s2=""; assert(s2[s2.length()]=='\0');
	s2="bar"; assert(s2[s2.length()]=='\0');



}

#define MACROTestIttPart(CR)							\
	/*	*it, ++it, it++, (it+i), it[i], == och !=	*/	\
	void TestIttPart##CR() {							\
	String s1("foobar");								\
	for (auto i=s1.CR##begin(); i!=s1.CR##end(); i++)	\
		cout << *i;										\
	cout << endl;										\
	if (#CR=="r" || #CR=="cr")							\
		s1="raboof";									\
	auto it = s1.CR##begin();							\
	assert(*it=='f');									\
	assert(*(it++)=='f' && *it == 'o');					\
	++it;												\
	assert(*++it=='b');									\
	assert(*(it+1)=='a');								\
	assert(it[2]=='r');									\
}

MACROTestIttPart(,);	//, ger tomt argument
MACROTestIttPart(c);
MACROTestIttPart(r);
MACROTestIttPart(cr);


void TestFörGodkäntItt() {
//-	typdefs för iterator, const_iterator,  reverse_iterator och const_revers_iterator
	String::iterator Str;
	String::const_iterator cStr;
	String::reverse_iterator rStr;
	String::const_reverse_iterator crStr;

//-	funktionerna begin, end, cbegin, cend, rbegin, rend, crbegin och crend.

//Iteratorerna ska kunna göra:
//-	*it, ++it, it++, (it+i), it[i], == och !=
	TestIttPart();
	TestIttPartc();
	TestIttPartr();
	TestIttPartcr();

//-	default constructor, copy constructor och tilldelning (=) 
	String s("foobar");
	Str=s.begin();
	cStr=s.cbegin();
	rStr=s.rbegin();
	crStr=s.crbegin();
	*Str='a';
//	*(cStr+1)='b';	//Sak ge kompileringsfel!
	*(rStr+2)='c';
//	*(crStr+3)='d';	//Sak ge kompileringsfel!
	assert(s=="aoocar");

}


int main() {
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	TestFörVälGodkäntString();
	TestFörGodkäntItt();
	cin.get();
}
