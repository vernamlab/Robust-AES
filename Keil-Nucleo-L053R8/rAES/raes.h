#ifndef RAES
#define RAES

	#include "aes_funcs.h"

	void share( uint8_t secret[16], uint8_t shares[16][N]) ;
	void encrypt( uint8_t ptx[16][N], uint8_t key[16][N] , uint8_t ctx[16][N]) ;

#endif
