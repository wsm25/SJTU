#include <cstdint>
#include <iostream>
#include <cstring>

const uint32_t polys[]={0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x94643b84};
const uint32_t primes[]={613007, 611953, 613061, 613229};

struct CRC32 {
    uint32_t table[256];
    CRC32(uint32_t polynomial){
		for (uint32_t i = 0; i < 256; i++) {
			uint32_t c = i;
			for (size_t j = 0; j < 8; j++) 
				if (c&1) c=polynomial^(c >> 1);
				else c>>=1;
			table[i] = c;
		}
	}
	uint32_t digest(const char* s){
		uint32_t c = 0xFFFFFFFF;
		for (; *s!=0; s++) 
			c = table[(c ^ *s) & 0xFF] ^ (c >> 8);
		return ~c;
	}
};

int main(){
    char buf[1501];
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