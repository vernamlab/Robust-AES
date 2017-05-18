#ifndef AES_FUNCTIONS
#define AES_FUNCTIONS

    #include "secops.h"

    
    //SubByte2 operation: affine function
    void SubByte2( uint8_t Fi[N], uint8_t Fo[N] ) ;
    
    //SubByte1 operation exponentiation y <-- y^254    
    void SubByte1( uint8_t Fi[N], uint8_t Fo[N] ) ;
    
    //SubByte operation for 16-byte state of AES
    void SubByte( uint8_t ptx[16][N], uint8_t ct[16][N] ) ;
    
    //ShiftRow operation for 16-byte state of AES   
    void ShiftRows( uint8_t ptx[16][N], uint8_t ctx[16][N] ) ;
    
    //MixColumn operation for 16-byte state of AES     
    void MixCol( uint8_t ptx[16][N], uint8_t ctx[16][N] ) ;
    
    //Key Schedule for AES-128
    void nextKey( uint8_t ks[16][N], uint8_t r, uint8_t nxtk[16][N] ) ;
    
    //AddRound operation for 16-byte state of AES    
    void addRoundKey( uint8_t ptx[16][N], uint8_t kk[16][N], uint8_t ctx[16][N] ) ;
    
#endif
