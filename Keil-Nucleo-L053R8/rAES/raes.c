#include "raes.h"


/******************************************************************************* 
						Share secret using random polynomials    
*******************************************************************************/    
void share( uint8_t secret[16], uint8_t shares[16][N]){
	
	uint8_t k,i,sum ;
	uint8_t f[D+1] ;
	
	#if D>1
		uint8_t j ;
	#endif 
	
	for( k=0 ; k<16 ; k++ ){
			f[0] = secret[k] ;
			
			#if D==1
					f[D] = getnonzerorn() ; // highest degree term must be nonzero
			#else
					for( j=1 ; j<D ; j++ ){
							f[j] = getrn() ;   
					}         
					f[D] = getnonzerorn() ; // highest degree term must be nonzero
			#endif     
			
			// For each element in alpha
			for( i=0 ; i<N ; i++ ){
					sum = f[0] ;
					#if D==1
							sum = gfadd( sum, gfmult(f[1], alpha[i])) ; 
					#else
					for( j=1 ; j<(D+1) ; j++ ){
							sum = gfadd( sum, gfmult(f[j], gfexp(alpha[i], j))) ;   
					}
					#endif
					shares[k][i] = sum ;   
			}
	}
}

/******************************************************************************* 
						AES Robust Encryption   
*******************************************************************************/
void encrypt( uint8_t ptx[16][N], uint8_t key[16][N] , uint8_t ctx[16][N]){

		uint8_t ct1[16][N], ct2[16][N], ct3[16][N] ;
		
		uint8_t r ;
	
		addRoundKey(ptx, key, ct1) ;           

		for( r=0 ; r<9 ; r++ ){
				SubByte( ct1, ct2 ) ;
				ShiftRows( ct2, ct3 ) ;
				MixCol( ct3, ctx ) ;
				nextKey( key, r, key) ;
				addRoundKey( ctx, key, ct1 ) ; 
		}
		SubByte( ct1, ct2 ) ;
		ShiftRows( ct2, ct3 ) ;
		nextKey( key, 9, key ) ;
		addRoundKey( ct3, key, ctx ) ;

}
