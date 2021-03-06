#include "TMX_Utils.h"

#include <cstring>
#include <iostream>
using namespace std;

#include <miniz/miniz.h>
#include <miniz/utils/gzip.c>

void TMX_Decode(unsigned char* input, unsigned char* output, unsigned len)
{
    base64::decoder decode;
    base64_init_decodestate(&decode._state);
    decode.decode( (char*)input , len , (char*)output );
}

void TMX_Uncompress(unsigned char* input, unsigned char* output, unsigned int in_size, unsigned int out_size, const char* Scheme)
{
    if(!strcmp(Scheme, ""))
    {
        memcpy(output, input, in_size);
        return;
    }
    if(!strcmp(Scheme, "zlib"))
    {
        unsigned long pLen = out_size;
        int iserror = uncompress(output, &pLen, input, in_size);
        if(iserror)
            cout << "miniz error:" << iserror;
        return;
    }
    if(!strcmp(Scheme, "gzip"))
    {
        z_stream strm  = {0};
        strm.total_in  = strm.avail_in  = in_size - 10; //I am pretty sure this was the last problem I had. Need to document why it was one.
        strm.total_out = strm.avail_out = out_size;
        strm.next_in   = input + 10;
        strm.next_out  = output;

        strm.zalloc = Z_NULL;
        strm.zfree  = Z_NULL;
        strm.opaque = Z_NULL;

        int err = -1;
        int ret = -1;

        err = inflateInit2(&strm,-15);
        if (err == Z_OK)
        {
            err = inflate(&strm, Z_FINISH);
            if (err == Z_STREAM_END)
            {
                ret = strm.total_out;
            }
            else
            {
                inflateEnd(&strm);
            }
        }
        else
        {
            inflateEnd(&strm);
        }

        inflateEnd(&strm);
        return;
    }
}

