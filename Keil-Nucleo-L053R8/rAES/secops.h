#ifndef SECOPS
#define SECOPS
    
    //#include <stdlib.h> //previously used because of the rand() function
    #include "gfops.h"
    
    void qPow2( uint8_t F[N], uint8_t H[N] ) ;
    void qPow4( uint8_t F[N], uint8_t H[N] ) ;
    void qPow16( uint8_t F[N], uint8_t H[N] ) ;
    void Addition( uint8_t a[N] , uint8_t b[N], uint8_t c[N] ) ;
    void Multiplication( uint8_t F[N], uint8_t G[N], uint8_t H[N] ) ;
    uint8_t getrn(void) ;
    uint8_t getnonzerorn( void ) ;
    
#endif
