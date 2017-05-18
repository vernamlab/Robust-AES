#ifndef GFARITH
#define GFARITH

    #include "params.h"
    
    #define gfadd(a,b) ((a)^(b))
    
    #ifdef SLOW
        uint8_t gfmult( uint8_t h, uint8_t v ) ;
        uint8_t gfsqr( uint8_t a ) ;
    
    #elif FAST 
        static const uint8_t lLUT[16][256] ;
        static const uint8_t hLUT[16][256] ;    
        //uint8_t gfmult( uint8_t a, uint8_t b ){
        //    return gfadd( hLUT[a>>4][b] , lLUT[a&0x0f][b] ) ;
        //}
        // A macro saves the function call overhead
        #define gfmult(a,b) gfadd( hLUT[(a)>>4][(b)] , lLUT[(a)&0x0f][(b)] )
        //uint8_t sqrLUT[256] ;
        #define gfsqr(a) sqrLUT[(a)]
    
		#elif EXPLOG
        uint8_t gfmult( uint8_t h, uint8_t v ) ;
        //uint8_t gfsqr( uint8_t a ) ;
				#define gfsqr(a) sqrLUT[(a)]				
    
		#else   
        //uint8_t secondOp[256] ;
        //uint8_t sqrLUT[256] ;
        uint8_t gfmult( uint8_t h, uint8_t v ) ;
        #define gfsqr(a) sqrLUT[(a)]
    
		#endif
    
    uint8_t gftimes2( uint8_t v ) ;
    uint8_t gfexp ( uint8_t base , uint8_t exp ) ;
    void gfmvmul( uint8_t mat[N][N] , uint8_t vec[N], uint8_t res[N] ) ;
    
#endif


