// cmdbuffer.h
// write by MoMo

#ifndef _CMDBUFFER_h
#define _CMDBUFFER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define VALUESIZE 8
#define CODESIZE VALUESIZE+1
#define VALUEBUFFSIZE 20

class CMDBUFFER
{
public:
	CMDBUFFER();
	char code;
	int value;
	int len;
	char codes[CODESIZE];
	float values[VALUESIZE];
	int code_index;
	char *text;
	int type;
	static char value_buffer[VALUEBUFFSIZE];
	static int pos;
	static bool comment;
private:
	void set_code(char c);
	void set_value(float v);
	int get_code_index(char c);
public:
	float get_value(int index);
	int get_int_value(int index);
	void add(char c);
	void save_value();
	bool find(int c);
	float get_find_value();
	void clear();
	bool next_value_is_text(char code, int value);
	bool is_code();
	bool is_value();
	bool is_text();
};

#endif

