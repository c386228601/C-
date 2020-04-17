#pragma once

#ifndef A3_H
#define A3_H
#include <string>
#include <map>
using namespace std;

void read_file(string from,string to, const char* filename);
void output_file(string from,string to, const char* filename);

template <class T> class Array;
class Morse
{
friend class Array<Morse>;
private:
	map<string, string> latin_map;
       map<string,string>::iterator it;
	string source;
public:
    Morse();
	Morse(string m);
	void trans(string to);
        void show_lrule();
};

template <class T> class Array;
class Braille
{
friend class Array<Braille>;
private:
	map<string, string> latin_map;
        map<string,string>::iterator it;
	string source;
public:
        Braille();
	Braille(string b);
	void trans(string to);
        void show_lrule();
};

template <class T> class Array;
class Latin
{
friend class Array<Latin>;
private:
	map<string, string> morse_map;
	map<string, string> braille_map;
        map<string,string>::iterator it;
	string source;
public:
        Latin();
	Latin(string l);
	void trans(string to);
        void show_mrule();
        void show_brule();
};

template<class T>
class Array
{
   private:
    int length;
    unsigned int index;
    T* objlist;

  public:
    Array<T>(unsigned int _length);
    ~Array();
    void push(T obj);
    void pop();
    void out(const char* fname);
};

Array<Morse> morse_list(100);
Array<Braille> braille_list(100);
Array<Latin> latin_list(100);
#endif // ! A3_H
