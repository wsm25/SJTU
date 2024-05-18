#include <cstdint>
#include <iostream>
#include <cstring>

#define COEFF1 0xedb88320
#define COEFF2 0x94643b84
#define PRIME1 16314941
#define PRIME2 15487019

uint32_t crc32(const char *s, const uint32_t coeff) {
	uint32_t crc=0xFFFFFFFF;
	for(;*s!=0; s++){
		char ch=*s;
		for(size_t j=0;j<8;j++) {
			uint32_t b=(ch^crc)&1;
			crc>>=1;
			if(b) crc=crc^coeff;
			ch>>=1;
		}
	}
	return ~crc;
}

int main(){
    char buf[1500];
    bool *table1=new bool[PRIME1], *table2=new bool[PRIME2];
    memset(table1, 0, PRIME1);
    memset(table2, 0, PRIME2);
    int n, cnt=0;
    std::cin>>n;
    std::cin.getline(buf,1500);
    for(int i=0; i<n; i++){
        std::cin.getline(buf, 1500);
        uint32_t crc1=crc32(buf, COEFF1)%PRIME1,
            crc2=crc32(buf, COEFF2)%PRIME2;
        if(!(table1[crc1] && table2[crc2])){ // new
            table1[crc1]=table2[crc2]=true;
            cnt++;
        }
    }
    std::cout<<cnt;
}