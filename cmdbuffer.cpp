// write by MoMo
// 
// 

#include "cmdbuffer.h"
#include "Marlin.h"
CMDBUFFER::CMDBUFFER()	
{
	clear();
}
void CMDBUFFER::set_code(char c)
{
	if (len == -1)
	{
		code = c;
	}
	else
	{
		codes[len] = c;
		codes[len+1] = NULL;
	}
	type = 1;
}
void CMDBUFFER::set_value(float v)
{
	if (len == -1)
	{
		value = (int)v;
		type = next_value_is_text(code, value) ? 2 : 0;
	}
	else
	{
		values[len] = v;
		type = 0;
	}
	len++;
}
int CMDBUFFER::get_code_index(char c)
{
	char *p = codes;
	int n = 0;
	while (*p && *p++ != c)
	{
		n++;
	}
	return n >= len ? -1 : n;
}
float CMDBUFFER::get_value(int index)
{
	return values[index];
}
int CMDBUFFER::get_int_value(int index)
{
	return (int)values[index];
}
void CMDBUFFER::add(char c)
{
	if (comment)
	{
		return;
	}
	if (is_code())
	{
		if (c != ' ' && c != '\t')
		{
			set_code(c);
		}
	}
	else if (is_value())
	{
		if (pos && (c == ' ' || c == '\t'))
		{
			save_value();
		}
		else if (c != ' ' && c != '\t')
		{
			value_buffer[pos] = c;
			pos++;
		}
	}
	else if (is_text())
	{
		*(text + pos) = c;
		pos++;
	}
}
void CMDBUFFER::save_value()
{
	if (pos)
	{
		if (is_text())
		{
			*(text + pos) = 0;
		}
		else
		{
			value_buffer[pos] = 0;
			if (is_value())
			{
				set_value(strtod(value_buffer, NULL));
			}
		}
		pos = 0;
	}
}
bool CMDBUFFER::find(int c)
{
	code_index = get_code_index(c);
	return code_index != -1;
}
float CMDBUFFER::get_find_value()
{
	return get_value(code_index);
}
void CMDBUFFER::clear()
{
	code = 0;
	codes[0] = 0;
	len = -1;
	code_index = -1;
	text = (char *)&values[0];
	type = 0;
	pos = 0;
	comment = false;
}
bool CMDBUFFER::next_value_is_text(char code, int value)
{
	if (code == 'M' && value == 23)
		return 1;
	if (code == 'M' && value == 28)
		return 1;
	if (code == 'M' && value == 117)
		return 1;

	return 0;
}
bool CMDBUFFER::is_code()
{
	return type == 0;
}
bool CMDBUFFER::is_value()
{
	return type == 1;
}
bool CMDBUFFER::is_text()
{
	return type == 2;
}
char CMDBUFFER::value_buffer[VALUEBUFFSIZE] = {0};
int CMDBUFFER::pos = 0;
bool CMDBUFFER::comment = false;
