#include "secops.h"

//------------------------------------------------------------------------------
// Pre-calculated shares and inverse Vandermonde matrix
//------------------------------------------------------------------------------       
#if (N==5) && (D==1)

    uint8_t alpha[N]  = {0x51, 0xec, 0x0d, 0xb1, 0x01} ;   
    uint8_t InvVand[N][N] = {    
        {0x01, 0x01, 0x01, 0x01, 0x01},
        {0x5d, 0x5c, 0xe0, 0xe1, 0x00},
        {0xbc, 0xbc, 0xbd, 0xbd, 0x00},
        {0xb1, 0x0d, 0x51, 0xec, 0x01},
        {0x51, 0xec, 0x0d, 0xb1, 0x01}
    };     
    void qPow2( uint8_t F[N], uint8_t H[N] ){
        H[0] = gfsqr(F[2]) ;
        H[1] = gfsqr(F[3]) ;
        H[2] = gfsqr(F[1]) ;
        H[3] = gfsqr(F[0]) ;
        H[4] = gfsqr(F[4]) ;
    }       
    void qPow4( uint8_t F[N], uint8_t H[N] ){
        uint8_t tmp0, tmp1, tmp2, tmp3, tmp4;
        
        tmp0 = gfsqr(F[2]) ;
        tmp1 = gfsqr(F[3]) ;
        tmp2 = gfsqr(F[1]) ;
        tmp3 = gfsqr(F[0]) ;
        tmp4 = gfsqr(F[4]) ;
        
        H[0] = gfsqr( tmp2 ) ;
        H[1] = gfsqr( tmp3 ) ;
        H[2] = gfsqr( tmp1 ) ;
        H[3] = gfsqr( tmp0 ) ;
        H[4] = gfsqr( tmp4 ) ;                
    }      
    void qPow16( uint8_t F[N], uint8_t H[N] ){
        uint8_t tmp0, tmp1, tmp2, tmp3, tmp4 ;
        
        tmp0 = gfsqr(F[2]) ;
        tmp1 = gfsqr(F[3]) ;
        tmp2 = gfsqr(F[1]) ;
        tmp3 = gfsqr(F[0]) ;
        tmp4 = gfsqr(F[4]) ;        

        tmp0 = gfsqr( tmp2 ) ;        
        tmp1 = gfsqr( tmp3 ) ;
        tmp2 = gfsqr( tmp1 ) ;
        tmp3 = gfsqr( tmp0 ) ;
        tmp4 = gfsqr( tmp4 ) ;    
        
        tmp0 = gfsqr( tmp2 ) ;        
        tmp1 = gfsqr( tmp3 ) ;
        tmp2 = gfsqr( tmp1 ) ;
        tmp3 = gfsqr( tmp0 ) ;
        tmp4 = gfsqr( tmp4 ) ;          
            
        H[0] = gfsqr( tmp2 ) ;
        H[1] = gfsqr( tmp3 ) ;
        H[2] = gfsqr( tmp1 ) ;
        H[3] = gfsqr( tmp0 ) ;
        H[4] = gfsqr( tmp4 ) ;            

    } 

    
#elif (N==5) && (D==2)

    uint8_t alpha[N]  = {0x51, 0xec, 0x0d, 0xb1, 0x01} ;   
    uint8_t InvVand[N][N] = {    
        {0x01, 0x01, 0x01, 0x01, 0x01},
        {0x5d, 0x5c, 0xe0, 0xe1, 0x00},
        {0xbc, 0xbc, 0xbd, 0xbd, 0x00},
        {0xb1, 0x0d, 0x51, 0xec, 0x01},
        {0x51, 0xec, 0x0d, 0xb1, 0x01}
    };     
    void qPow2( uint8_t F[N], uint8_t H[N] ){
        H[0] = gfsqr(F[2]) ;
        H[1] = gfsqr(F[3]) ;
        H[2] = gfsqr(F[1]) ;
        H[3] = gfsqr(F[0]) ;
        H[4] = gfsqr(F[4]) ;
    }       
    void qPow4( uint8_t F[N], uint8_t H[N] ){
        uint8_t tmp0, tmp1, tmp2, tmp3, tmp4;
        
        tmp0 = gfsqr(F[2]) ;
        tmp1 = gfsqr(F[3]) ;
        tmp2 = gfsqr(F[1]) ;
        tmp3 = gfsqr(F[0]) ;
        tmp4 = gfsqr(F[4]) ;
        
        H[0] = gfsqr( tmp2 ) ;
        H[1] = gfsqr( tmp3 ) ;
        H[2] = gfsqr( tmp1 ) ;
        H[3] = gfsqr( tmp0 ) ;
        H[4] = gfsqr( tmp4 ) ;                
    }      
    void qPow16( uint8_t F[N], uint8_t H[N] ){
        uint8_t tmp0, tmp1, tmp2, tmp3, tmp4 ;
        
        tmp0 = gfsqr(F[2]) ;
        tmp1 = gfsqr(F[3]) ;
        tmp2 = gfsqr(F[1]) ;
        tmp3 = gfsqr(F[0]) ;
        tmp4 = gfsqr(F[4]) ;        

        tmp0 = gfsqr( tmp2 ) ;        
        tmp1 = gfsqr( tmp3 ) ;
        tmp2 = gfsqr( tmp1 ) ;
        tmp3 = gfsqr( tmp0 ) ;
        tmp4 = gfsqr( tmp4 ) ;    
        
        tmp0 = gfsqr( tmp2 ) ;        
        tmp1 = gfsqr( tmp3 ) ;
        tmp2 = gfsqr( tmp1 ) ;
        tmp3 = gfsqr( tmp0 ) ;
        tmp4 = gfsqr( tmp4 ) ;          
            
        H[0] = gfsqr( tmp2 ) ;
        H[1] = gfsqr( tmp3 ) ;
        H[2] = gfsqr( tmp1 ) ;
        H[3] = gfsqr( tmp0 ) ;
        H[4] = gfsqr( tmp4 ) ;            

    }         

#elif (N==6) && (D==1)

    uint8_t alpha[N]  = {0xe0, 0xe1, 0x5c, 0x5d, 0xbc, 0xbd} ;   
    uint8_t InvVand[N][N] = {    
        {0xe1, 0xe0, 0x5d, 0x5c, 0xbd, 0xbc},
        {0xb0, 0x0c, 0x50, 0xed, 0xbc, 0xbd},
        {0x5d, 0x5c, 0xe0, 0xe1, 0x01, 0x01},
        {0x01, 0x01, 0x01, 0x01, 0x00, 0x00},
        {0x50, 0xed, 0x0c, 0xb0, 0xbd, 0xbc},
        {0xbd, 0xbd, 0xbc, 0xbc, 0x01, 0x01}
    };             

    void qPow2( uint8_t F[N], uint8_t H[N] ){
        H[0] = gfsqr(F[2]) ;
        H[1] = gfsqr(F[3]) ;
        H[2] = gfsqr(F[1]) ;
        H[3] = gfsqr(F[0]) ;
        H[4] = gfsqr(F[5]) ;
        H[5] = gfsqr(F[4]) ;
    }       
    void qPow4( uint8_t F[N], uint8_t H[N] ){
        uint8_t tmp0, tmp1, tmp2, tmp3, tmp4, tmp5;
        
        tmp0 = gfsqr(F[2]) ;
        tmp1 = gfsqr(F[3]) ;
        tmp2 = gfsqr(F[1]) ;
        tmp3 = gfsqr(F[0]) ;
        tmp4 = gfsqr(F[5]) ;
        tmp5 = gfsqr(F[4]) ;
        
        H[0] = gfsqr( tmp2 ) ;
        H[1] = gfsqr( tmp3 ) ;
        H[2] = gfsqr( tmp1 ) ;
        H[3] = gfsqr( tmp0 ) ;
        H[4] = gfsqr( tmp5 ) ;
        H[5] = gfsqr( tmp4 ) ;                
    }      
    void qPow16( uint8_t F[N], uint8_t H[N] ){
        uint8_t tmp0, tmp1, tmp2, tmp3, tmp4, tmp5 ;
        
        tmp0 = gfsqr(F[2]) ;
        tmp1 = gfsqr(F[3]) ;
        tmp2 = gfsqr(F[1]) ;
        tmp3 = gfsqr(F[0]) ;
        tmp4 = gfsqr(F[5]) ; 
        tmp5 = gfsqr(F[4]) ;       

        tmp0 = gfsqr( tmp2 ) ;        
        tmp1 = gfsqr( tmp3 ) ;
        tmp2 = gfsqr( tmp1 ) ;
        tmp3 = gfsqr( tmp0 ) ;
        tmp4 = gfsqr( tmp5 ) ;  
        tmp5 = gfsqr( tmp4 ) ;  
        
        tmp0 = gfsqr( tmp2 ) ;        
        tmp1 = gfsqr( tmp3 ) ;
        tmp2 = gfsqr( tmp1 ) ;
        tmp3 = gfsqr( tmp0 ) ;
        tmp4 = gfsqr( tmp5 ) ;          
        tmp5 = gfsqr( tmp4 ) ;
                    
        H[0] = gfsqr( tmp2 ) ;
        H[1] = gfsqr( tmp3 ) ;
        H[2] = gfsqr( tmp1 ) ;
        H[3] = gfsqr( tmp0 ) ;
        H[4] = gfsqr( tmp5 ) ;            
        H[5] = gfsqr( tmp4 ) ;
    }
#elif (N==6) && (D==2)

    uint8_t alpha[N]  = {0xe0, 0xe1, 0x5c, 0x5d, 0xbc, 0xbd} ;   
    uint8_t InvVand[N][N] = {    
        {0xe1, 0xe0, 0x5d, 0x5c, 0xbd, 0xbc},
        {0xb0, 0x0c, 0x50, 0xed, 0xbc, 0xbd},
        {0x5d, 0x5c, 0xe0, 0xe1, 0x01, 0x01},
        {0x01, 0x01, 0x01, 0x01, 0x00, 0x00},
        {0x50, 0xed, 0x0c, 0xb0, 0xbd, 0xbc},
        {0xbd, 0xbd, 0xbc, 0xbc, 0x01, 0x01}
    }; 
    void qPow2( uint8_t F[N], uint8_t H[N] ){
        H[0] = gfsqr(F[2]) ;
        H[1] = gfsqr(F[3]) ;
        H[2] = gfsqr(F[1]) ;
        H[3] = gfsqr(F[0]) ;
        H[4] = gfsqr(F[5]) ;
        H[5] = gfsqr(F[4]) ;
    }       
    void qPow4( uint8_t F[N], uint8_t H[N] ){
        uint8_t tmp0, tmp1, tmp2, tmp3, tmp4, tmp5 ;
        
        tmp0 = gfsqr(F[2]) ;
        tmp1 = gfsqr(F[3]) ;
        tmp2 = gfsqr(F[1]) ;
        tmp3 = gfsqr(F[0]) ;
        tmp4 = gfsqr(F[5]) ;
        tmp5 = gfsqr(F[4]) ;
        
        H[0] = gfsqr( tmp2 ) ;
        H[1] = gfsqr( tmp3 ) ;
        H[2] = gfsqr( tmp1 ) ;
        H[3] = gfsqr( tmp0 ) ;
        H[4] = gfsqr( tmp5 ) ;
        H[5] = gfsqr( tmp4 ) ;                
    }      
    void qPow16( uint8_t F[N], uint8_t H[N] ){
        uint8_t tmp0, tmp1, tmp2, tmp3, tmp4, tmp5 ;
        
        tmp0 = gfsqr(F[2]) ;
        tmp1 = gfsqr(F[3]) ;
        tmp2 = gfsqr(F[1]) ;
        tmp3 = gfsqr(F[0]) ;
        tmp4 = gfsqr(F[5]) ; 
        tmp5 = gfsqr(F[4]) ;       

        tmp0 = gfsqr( tmp2 ) ;        
        tmp1 = gfsqr( tmp3 ) ;
        tmp2 = gfsqr( tmp1 ) ;
        tmp3 = gfsqr( tmp0 ) ;
        tmp4 = gfsqr( tmp5 ) ;  
        tmp5 = gfsqr( tmp4 ) ;  
        
        tmp0 = gfsqr( tmp2 ) ;        
        tmp1 = gfsqr( tmp3 ) ;
        tmp2 = gfsqr( tmp1 ) ;
        tmp3 = gfsqr( tmp0 ) ;
        tmp4 = gfsqr( tmp5 ) ;          
        tmp5 = gfsqr( tmp4 ) ;
                    
        H[0] = gfsqr( tmp2 ) ;
        H[1] = gfsqr( tmp3 ) ;
        H[2] = gfsqr( tmp1 ) ;
        H[3] = gfsqr( tmp0 ) ;
        H[4] = gfsqr( tmp5 ) ;            
        H[5] = gfsqr( tmp4 ) ;
    }    
#elif (N==3) && (D==1)

    uint8_t alpha[N]  = {0x01, 0xbc, 0xbd} ;       
    uint8_t InvVand[N][N] = { 
        {0x01, 0x01, 0x01},
        {0x01, 0xbd, 0xbc},
        {0x01, 0xbc, 0xbd}
    };
		
    void qPow2( uint8_t F[N], uint8_t H[N] ){

        H[0] = gfsqr(F[0]) ;
        H[1] = gfsqr(F[2]) ;
        H[2] = gfsqr(F[1]) ;
    }       
    void qPow4( uint8_t F[N], uint8_t H[N] ){
        uint8_t tmp1, tmp2, tmp3 ;

        tmp1 = gfsqr(F[0]) ;
        tmp2 = gfsqr(F[1]) ;
        tmp3 = gfsqr(F[2]) ;
        
        H[0] = gfsqr( tmp1 ) ;
        H[1] = gfsqr( tmp2 ) ;
        H[2] = gfsqr( tmp3 ) ;        
    }      

    void qPow16( uint8_t F[N], uint8_t H[N] ){
        uint8_t tmp1, tmp2, tmp3 ;

        //2
        tmp1 = gfsqr(F[0]) ;
        tmp2 = gfsqr(F[1]) ;
        tmp3 = gfsqr(F[2]) ;
        //4
        tmp1 = gfsqr( tmp1 ) ;
        tmp2 = gfsqr( tmp2 ) ;
        tmp3 = gfsqr( tmp3 ) ;
        //8
        tmp1 = gfsqr( tmp1 ) ;
        tmp2 = gfsqr( tmp2 ) ;
        tmp3 = gfsqr( tmp3 ) ;
        //16                
        H[0] = gfsqr( tmp1 ) ;
        H[1] = gfsqr( tmp2 ) ;
        H[2] = gfsqr( tmp3 ) ;       
    }     
#endif


//------------------------------------------------------------------------------
//                                  Addition
//------------------------------------------------------------------------------
void Addition( uint8_t a[N] , uint8_t b[N], uint8_t c[N] ){
    uint8_t j ;
    for( j=0 ; j<N ; j++ ){
        c[j] = gfadd( a[j], b[j] ) ;   
    }
}


#if FAULTDET==1
//------------------------------------------------------------------------------
//            Multiplication - detects some faults
//------------------------------------------------------------------------------
void Multiplication( uint8_t F[N], uint8_t G[N], uint8_t H[N] ){
    
    uint8_t i,j,a,sum,sum1 ;
    uint8_t tmp1, tmp2 ;
    uint8_t Q[D+1] ;
    uint8_t QFunctions[N][N] ;
    
    #if D>1
        uint8_t t ;     
    #endif
    
    #if EPS>0 //N>3
        uint8_t tmp2 ;
    #endif
    
    
    for( i=0 ; i<N ; i++ ){
        
        Q[0] = gfmult( F[i], G[i] ) ;      
        
        for( j=1 ; j<(D+1) ; j++ ){
            Q[j] = getrn(); 
        }       
        for( a=0 ; a<N ; a++ ){
            sum1 = Q[0] ;
            #if D==1
                sum1 = gfadd( sum1 , gfmult( Q[1], alpha[a] )) ; 
            #else
            for( t=1 ; t<(D+1) ; t++ ){
                sum1 = gfadd( sum1 , gfmult( Q[t], gfexp( alpha[a], t ))) ;   
            }   
            #endif
            QFunctions[i][a] = sum1 ;
        }
    }
    
    for( j=0 ; j<N ; j++ ){
        sum = 0 ;
        for( i=0 ; i<N ; i++ ){
            tmp1 = gfmult( InvVand[0][i], QFunctions[i][j] ) ; //Lambda
						
            #if EPS==0
                if( j < D ){  
                    tmp2 = gfmult( InvVand[N-j-1][i], gfadd( F[i], G[i] ) ) ;     //Lambda
                    sum = gfadd( sum, gfadd( tmp1, tmp2 )) ;                   
                } else {       
                    sum = gfadd( sum, tmp1 ) ;                
                } 
            #else
                if( j < EPS ){  
                    tmp2 = gfmult( InvVand[N-j-1][i], gfmult( F[i], G[i] ) ) ;     //Lambda
                    sum = gfadd( sum, gfadd( tmp1, tmp2 )) ;   
                } else if( j >= EPS  && j<(EPS+D) ){  
                    tmp2 = gfmult( InvVand[N-j-1][i], gfadd( F[i], G[i] ) ) ;     //Lambda
                    sum = gfadd( sum, gfadd( tmp1, tmp2 )) ;                   
                } else {       
                    sum = gfadd( sum, tmp1 ) ;                
                }  
            #endif
        }
        H[j] = sum ;           
    }
    
}


#else
//------------------------------------------------------------------------------
//            Multiplication - without fault detection
//------------------------------------------------------------------------------
void Multiplication( uint8_t F[N], uint8_t G[N], uint8_t H[N] ){
    
    uint8_t i,j,a,sum,sum1 ;
    uint8_t tmp1 ;
    uint8_t Q[D+1] ;
    uint8_t QFunctions[N][N] ;
    
    #if D>1
        uint8_t t ;     
    #endif
		
    for( i=0 ; i<N ; i++ ){
        
        Q[0] = gfmult( F[i], G[i] ) ;      
        
        for( j=1 ; j<(D+1) ; j++ ){
            Q[j] = getrn(); 
        } 
        
        for( a=0 ; a<N ; a++ ){
            sum1 = Q[0] ;
            #if D==1
                sum1 = gfadd( sum1 , gfmult( Q[1], alpha[a] )) ; 
            #else
            for( t=1 ; t<(D+1) ; t++ ){
                sum1 = gfadd( sum1 , gfmult( Q[t], gfexp( alpha[a], t ))) ;   
            }   
            #endif           
            QFunctions[i][a] = sum1 ;
        }      
    }
    
    for( j=0 ; j<N ; j++ ){
        sum = 0 ;
        for( i=0 ; i<N ; i++ ){
            tmp1 = gfmult( InvVand[0][i], QFunctions[i][j] ) ; //Lambda
            sum = gfadd( sum, tmp1 ) ;                
        }
        H[j] = sum ;       
    }    
}

#endif


//-------------------------------------------------------------------------------
//              Get a random number from the RNG
//-------------------------------------------------------------------------------
uint8_t getrn(){
    //while( (RNG->SR & RNG_SR_DRDY) == 0);
    return (uint8_t)(RNG->DR) ;
}

//-------------------------------------------------------------------------------
//              Get a non-zero random number from the RNG
//-------------------------------------------------------------------------------
uint8_t getnonzerorn( ){  
    uint8_t out = 0 ;
    uint8_t nonzero = 0, i ,outSet = 0 ;
    uint8_t bytes[4];
    uint32_t rn ;

    rn = RNG->DR ;
    bytes[0] = (uint8_t)rn ;
    bytes[1] = (uint8_t)(rn >> 8);
    bytes[2] = (uint8_t)(rn >> 16);
    bytes[3] = (uint8_t)(rn >> 24);
    
    for (i=0; i<4; i++){

				out = ( (~(-outSet)) & (~(-nonzero)) & bytes[i]) + out ;
			
        nonzero = bytes[i]  ;
        nonzero |= nonzero >> 4 ;
        nonzero |= nonzero >> 2 ;
        nonzero |= nonzero >> 1 ;
				nonzero &= 0x01 ;
				outSet  |= nonzero ;
			
    } 
    return out ;
}
