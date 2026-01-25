#include <stdio.h>
#include <sys/types.h>

#define UINT8 unsigned char
#define INT8 char

#define UINT16 __uint16_t 
#define INT16 __int16_t
	
#define UINT32 __uint32_t 
#define INT32 __int32_t

#define UINT64 __uint64_t
#define INT64 __int64_t

#define UINT128 __uint128_t
#define INT128 __int128_t

#define FLOAT64 double

extern "C" UINT64 dg_testasm1();
extern "C" UINT64 dg_testasm2();
extern "C" UINT64 dg_testasm3();

int main(int argc, char* argv[])
{
    UINT64 x;
    UINT32 xhi, xlo;

    x = dg_testasm1();

    printf("testing sampleasmdylib.dylib\n");
    
    printf("  testing dg_testasm1\n");

    x = dg_testasm1();
    
    if (x != 0x1234)
    {
    
       printf("  FAIL! dg_testasm1() success test - expected 0x1234, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing dg_testasm2\n");

    x = dg_testasm2();
    
    if (x != 0x1122)
    {
    
       printf("  FAIL! dg_testasm2() success test - expected 0x1122, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }

    printf("  testing dg_testasm3, you should see: \nHello World!\n\n\n2nd Hello World!\n\n");

    x = dg_testasm3();

    return(0);
}