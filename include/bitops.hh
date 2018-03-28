
#define GETBIT( i ) ( (unsigned char) (1 << (7 - (((i) - 1) & 7))) )
#define ISBITSET( b,i )   ( (b) [(i - 1) / 8] & GETBIT(i) )
#define SETBIT( b,i )   ( (b) [(i - 1) / 8] |= GETBIT(i) )
#define CLRBIT( b,i )   ( (b) [(i - 1) / 8] &= !GETBIT(i) )

