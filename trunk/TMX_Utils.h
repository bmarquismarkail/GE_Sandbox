#ifndef TMX_UTILS_H_INCLUDED
#define TMX_UTILS_H_INCLUDED

#include <sstream>
#include <string>
#include <inttypes.h>
using namespace std;

#include <rapidxml.hpp>
using namespace rapidxml;

#include <b64/decode.h>

void TMX_Decode(char* input, char* output);

void TMX_Uncompress(char* input, char* output, unsigned int in_size, unsigned int out_size, const char* Scheme);


#endif // TMX_UTILS_H_INCLUDED
