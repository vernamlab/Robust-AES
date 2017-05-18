#ifndef PARAMETERS
#define PARAMETERS

    #include "stm32l053xx.h"
    
    #define M 8

    /************************* Parameter selection ********************************/
    //Select (n,d) scheme, options: (3,1), (4,1), (5,1), (5,2), (6,1), (6,2):
    //other schemes would work but need shares and inverse Vandermonde matrix.
    #define N 5
    #define D 2

    //Select the speed:
    //#define FAST 1    	// Uses LUTs for field multiplication and squaring
    //#define SLOW 1    	// Uses code only, no LUTs
		#define EXPLOG 1    // Uses exp-log gf multiplication, requires two 256-byte LUTs
    //default           	// Uses a trade-off between code and LUTs

    //Permute the functions of the shares:
    //works only for (3,1),(5,1),(5,2),(6,1) and (6,2)
    #define REORDER 1
		
		//Enables the multiplication to partially detect faults
		#define FAULTDET 1		
    /******************************************************************************/

    #define EPS 0 //N-(2*D)-1
    #define gfadd(a,b) ((a)^(b))

    #ifdef SLOW
        //nothing
    #elif FAST 
        //extern static const uint8_t lLUT[16][256] ;
        //extern static const uint8_t hLUT[16][256] ;    
        extern uint8_t sqrLUT[256] ;
    #elif EXPLOG
				extern uint8_t expt[256] ;
				extern uint8_t logt[256] ;
        extern uint8_t sqrLUT[256] ;				
    #else   
        extern uint8_t secondOp[256] ;
        extern uint8_t sqrLUT[256] ;
    #endif
    
    extern uint8_t InvVand[N][N] ;
    extern uint8_t alpha[N] ;
    
#endif
