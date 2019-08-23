#include "my_atol.h"

/* 
The function returns the converted integral number as a long int. If no valid 
conversion can be performed, it returns zero.

The function first discards as many whitespace characters 
as necessary until the first non-whitespace character is 
found. Then, starting from this character, takes as many 
characters as possible that are valid and interprets them 
as a numerical value. 

On success, the function returns the converted integral number as a long int value.
If no valid conversion could be performed, a zero value is returned (0L).
If the value read is out of the range of representable values by a long int, 
the function returns LONG_MAX or LONG_MIN

*/
long int atol(const char * str)
{
    return 0L;
}

long int atol(const std::string & str)
{
    return atol(str.c_str());
}