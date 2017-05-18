#include "aes_funcs.h"

//------------------------------------------------------------------------------
//                SubByte2 operation: affine function
//------------------------------------------------------------------------------
void SubByte2( uint8_t Fi[N], uint8_t Fo[N] ){
    uint8_t i, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7, tmp8 ;
    uint8_t F2[N], F4[N], F8[N], F16[N], F32[N], F64[N], F128[N] ;
    const uint8_t T[9] = {0x63, 0x05, 0x09, 0xf9, 0x25, 0xf4, 0x01, 0xb5, 0x8f} ;
    
#ifdef REORDER 
    qPow2(Fi,F2) ;
    qPow2(F2,F4) ;
    qPow2(F4,F8) ;
    qPow2(F8,F16) ;
    qPow2(F16,F32) ;
    qPow2(F32,F64) ;
    qPow2(F64,F128) ;    
#else        
    Multiplication( Fi, Fi, F2 ) ;
    Multiplication( F2, F2, F4 ) ;
    Multiplication( F4, F4, F8 ) ;
    Multiplication( F8, F8, F16 ) ;
    Multiplication( F16, F16, F32 ) ;
    Multiplication( F32, F32, F64 ) ;
    Multiplication( F64, F64, F128 ) ;
#endif    

    
    for( i=0 ; i<N ; i++ ){
        tmp1 = gfmult( T[1], Fi[i] ) ;
        tmp2 = gfmult( T[2], F2[i] ) ;
        tmp3 = gfmult( T[3], F4[i] ) ;
        tmp4 = gfmult( T[4], F8[i] ) ;
        tmp5 = gfmult( T[5], F16[i] ) ;
        tmp6 = gfmult( T[6], F32[i] ) ;
        tmp7 = gfmult( T[7], F64[i] ) ;
        tmp8 = gfmult( T[8], F128[i] ) ; 
        
        tmp1 = gfadd( T[0], tmp1 ) ;
        tmp2 = gfadd( tmp2, tmp3 ) ;
        tmp3 = gfadd( tmp4, tmp5 ) ;
        tmp4 = gfadd( tmp6, tmp7 ) ;
        
        tmp5 = gfadd( tmp1, tmp2 ) ;
        tmp6 = gfadd( tmp3, tmp4 ) ;
        
        tmp7 = gfadd( tmp5, tmp6 ) ;
        tmp8 = gfadd( tmp7, tmp8 ) ;
        
        Fo[i] = tmp8 ;        
    }
}


//------------------------------------------------------------------------------
//                SubByte1 operation exponentiation y <-- y^254
//------------------------------------------------------------------------------
void SubByte1( uint8_t Fi[N], uint8_t Fo[N] ){
    
#ifdef REORDER   
    uint8_t Z[N], Y[N], W[N], Y1[N], Y24[N], Y2[N], Y3[N], Y4[N] ;
    
    qPow2( Fi, Z ) ;    //Z=V^2 
    Multiplication( Z, Fi, Y ) ;
    qPow4( Y, W ) ;
    Multiplication( Y, W, Y1 ) ;
    //qPow16( Y1, Y2 );   //Only works for the 3,1 case
    qPow4(Y1,Y24) ;
    qPow4(Y24,Y2) ;
    Multiplication( Y2, W, Y3 ) ;
    Multiplication( Y3, Z, Y4 ) ; // Y4
    SubByte2( Y4, Fo ) ;
#else
    uint8_t Z[N], Y[N], W1[N], W[N], Y1[N], Y22[N], Y24[N], Y28[N], Y2[N], Y3[N], Y4[N] ;
    
    Multiplication( Fi, Fi, Z ) ;
    Multiplication( Z, Fi, Y ) ;
    Multiplication( Y, Y, W1 ) ;  //W=Y^4=Y
    Multiplication( W1, W1, W ) ;
    Multiplication( Y, W, Y1 ) ;
    Multiplication( Y1, Y1, Y22 ) ; //Y=Y^16=Y
    Multiplication( Y22, Y22, Y24 ) ;
    Multiplication( Y24, Y24, Y28 ) ;
    Multiplication( Y28, Y28, Y2 ) ;
    Multiplication( Y2, W, Y3 ) ;    
    Multiplication( Y3, Z, Y4 ) ; // Y4
    SubByte2( Y4, Fo ) ;
#endif
    
}

//------------------------------------------------------------------------------
//                SubByte operation for 16-byte state of AES
//------------------------------------------------------------------------------
void SubByte( uint8_t ptx[16][N], uint8_t ct[16][N] ){
    
    uint8_t i, j, k ;
    uint8_t p[N], c[N] ;
    
    for( i=0 ; i<16 ; i++){
        for( j=0; j<N ; j++ ){
            p[j] = ptx[i][j] ;    //Extracts one row from the matrix      
        }   
        SubByte1( p, c );
        for( k=0; k<N ; k++ ){
            ct[i][k] = c[k] ;   
        } 
    }
}

//------------------------------------------------------------------------------
//                ShiftRow operation for 16-byte state of AES 
//------------------------------------------------------------------------------
void ShiftRows( uint8_t ptx[16][N], uint8_t ctx[16][N] ) {
    
    uint8_t temp[16][N] ;
    uint8_t i,j,t,k ;
    
    for( t=0 ; t<16 ; t++ ){
        for( k=0 ; k<N ; k++ ){
            temp[t][k] = ptx[t][k] ;   
        }
    }   
    
    for( i=0 ; i<4 ; i++ ){
        for( j=0 ; j<4 ; j++ ){
            if( j != 0 ){
                for( k=0 ; k<N ; k++ ){
                    ctx[4*j+i][k] = temp[4*j+(i+j)%4][k] ;
                }     
            } else {
                for( k=0 ; k<N ; k++ ){
                    ctx[4*j+i][k] = temp[j*4+i][k] ;   
                }                
            }   
        }   
    }
}

//------------------------------------------------------------------------------
//                MixColumn operation for 16-byte state of AES 
//------------------------------------------------------------------------------
void MixCol( uint8_t ptx[16][N], uint8_t ctx[16][N] ){
    
    uint8_t i,j,c,k ;
    uint8_t temp[16][N] ;
    uint8_t tmp1, tmp2, tmp3, tmp4, tmp5 ;
    
    for( i=0 ; i<4 ; i++ ){
        for( j=0 ; j<4 ; j++ ){
            for( k=0 ; k<N ; k++ ){
                temp[4*i+j][k] = ptx[4*i+j][k] ; 
            }   
        }   
    }
    
    for( c=0 ; c<4 ; c++ ){
        for( k=0 ; k<N ; k++ ){
            //tmp1 = gfmult( 0x02, temp[c][k] ) ;
            tmp1 = gftimes2( temp[c][k] ) ;
            tmp2 = gfmult( 0x03, temp[4+c][k] ) ;
            tmp3 = gfadd( temp[8+c][k], temp[12+c][k] ) ;
            tmp4 = gfadd( tmp1, tmp2 ) ;
            tmp5 = gfadd( tmp3, tmp4 ) ;   //Some tmp variables could be reused.
            ctx[0+c][k] = tmp5 ;   

            //tmp1 = gfmult( 0x02, temp[4+c][k] ) ;
            tmp1 = gftimes2( temp[4+c][k] ) ;
            tmp2 = gfmult( 0x03, temp[8+c][k] ) ;
            tmp3 = gfadd( temp[c][k], temp[12+c][k] ) ;
            tmp4 = gfadd( tmp1, tmp2 ) ;
            tmp5 = gfadd( tmp3, tmp4 ) ;   //Some tmp variables could be reused.
            ctx[4+c][k] = tmp5 ;  

            //tmp1 = gfmult( 0x02, temp[8 +c][k] ) ;
            tmp1 = gftimes2( temp[8+c][k] ) ;
            tmp2 = gfmult( 0x03, temp[12+c][k] ) ;
            tmp3 = gfadd( temp[c][k], temp[4+c][k] ) ;
            tmp4 = gfadd( tmp1, tmp2 ) ;
            tmp5 = gfadd( tmp3, tmp4 ) ;   //Some tmp variables could be reused.
            ctx[8+c][k] = tmp5 ;  

            //tmp1 = gfmult( 0x02, temp[12+c][k] ) ;
            tmp1 = gftimes2( temp[12+c][k] ) ;
            tmp2 = gfmult( 0x03, temp[c][k] ) ;
            tmp3 = gfadd( temp[4+c][k], temp[8+c][k] ) ;
            tmp4 = gfadd( tmp1, tmp2 ) ;
            tmp5 = gfadd( tmp3, tmp4 ) ;   //Some tmp variables could be reused.
            ctx[12+c][k] = tmp5 ;  
        }   
    }
}

//------------------------------------------------------------------------------
//                Key Schedule for AES-128
//------------------------------------------------------------------------------
void nextKey( uint8_t ks[16][N], uint8_t r, uint8_t nxtk[16][N] ){
    
    uint8_t rcon[10] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36} ;
    uint8_t temp[16][N] ;
    uint8_t t1[N], t2[N], t3[N] ;
    uint8_t i,j,ii ;
    
    for( i=0 ; i<16; i++ ){
        for( j=0 ; j<N ; j++ ){
            temp[i][j] = ks[i][j] ;   
        }       
    }    
    
    for( i=0 ; i<4 ; i++ ){
        for( j=0 ; j<4 ; j++ ){
            if( j != 0 ){
                for( ii=0 ; ii<N ; ii++ ){                    
                    t1[ii] = nxtk[4*i+j-1][ii] ;        
                }
                for( ii=0 ; ii<N ; ii++ ){
                    t2[ii] = temp[4*i+j][ii] ;   
                }
                Addition(t1, t2, nxtk[4*i+j]);                   
            } else {
                if( i == 0 ){
                    for( ii=0 ; ii<N ; ii++ ){
                        t1[ii] = temp[(4*i+j+7)%16][ii] ;   
                    }   
                    for( ii=0 ; ii<N ; ii++ ){
                        t2[ii] = temp[4*i+j][ii] ;   
                    }
                    SubByte1(t1, t3) ;
                    Addition(t3, t2, nxtk[4*i+j]) ;
                    for( ii=0 ; ii<N ; ii++ ){
                        nxtk[4*i+j][ii] = gfadd(nxtk[4*i+j][ii], rcon[r]) ;   
                    }
                } else {
                    for( ii=0 ; ii<N ; ii++ ){
                        t1[ii] = temp[(4*i+j+7)%16][ii] ;   
                    }
                    for( ii=0 ; ii<N ; ii++ ){
                        t2[ii] = temp[4*i+j][ii] ;   
                    }
                    SubByte1(t1, t3) ;
                    Addition(t3, t2, nxtk[4*i+j]) ;                    
                }
            }   
        }   
    }
}

//------------------------------------------------------------------------------
//                AddRound operation for 16-byte state of AES
//------------------------------------------------------------------------------
void addRoundKey( uint8_t ptx[16][N], uint8_t kk[16][N], uint8_t ctx[16][N] ){
    uint8_t r, ii, j ;
    uint8_t t1[N], t2[N], res[N] ;
    
    for( r=0 ; r<16 ; r++ ){
        for( ii=0 ; ii<N ; ii++ ){
            t1[ii] = ptx[r][ii] ;   
        }
        for( ii=0 ; ii<N ; ii++ ){
            t2[ii] = kk[r][ii] ;   
        }
        
        Addition(t1,t2,res) ;
        for( j=0 ; j<N ; j++ ){
            ctx[r][j] = res[j] ;        
        }
    }         
}
