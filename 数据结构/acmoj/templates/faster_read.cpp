#include <cstdio>
class IntReader{
    char buf[65536]; // 16k buffer
    char *p, *tail; // pointer
    inline void read(){
        size_t n =fread(buf, 1, 65536, stdin);
        if(n<65536) buf[n]=EOF;
        p=buf;
    }
public:
    IntReader():p(buf+65536),tail(buf+65536){}
    int get(){
        int x = 0, sign = 1;
        if (p>=tail) read();
        while (p<tail && (*p < '0' || *p > '9'))
            if (*(p++) == '-') sign = -1;
        if (p>=tail){
            read();
            while (*p < '0' || *p > '9')
                if (*(p++) == '-') sign = -1;
        }
        
        while (p<tail && *p >= '0' && *p <= '9'){
            x = x * 10 + *(p++) - '0';
        }
        if (p>=tail){
            read();
            while (*p >= '0' && *p <= '9')
                x = x * 10 + *(p++) - '0';
        }
        return sign*x;
    }
};

class UintReader{
    char buf[65536]; // 16k buffer
    char *p, *tail; // pointer
    inline void read(){
        size_t n =fread(buf, 1, 65536, stdin);
        if(n<65536) buf[n]=EOF;
        p=buf;
    }
public:
    UintReader():p(buf+65536),tail(buf+65536){}
    unsigned get(){
        unsigned x = 0;
        if (p>=tail) read();
        while (p<tail && (*p < '0' || *p > '9')) p++;
        if (p>=tail){
            read();
            while (*p < '0' || *p > '9');
        }
        
        while (p<tail && *p >= '0' && *p <= '9'){
            x = x * 10 + *(p++) - '0';
        }
        if (p>=tail){
            read();
            while (*p >= '0' && *p <= '9')
                x = x * 10 + *(p++) - '0';
        }
        return x;
    }
};