/* Part of the code in this file has been copied and modified from ARM copyrighted code,
		following is the copyright information. 
		The copyrighted code is unrelated to the AES implementation */

/* Copyright (c) 2013 - 2016 ARM LIMITED

   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   - Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   - Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.
   - Neither the name of ARM nor the names of its contributors may be used
     to endorse or promote products derived from this software without
     specific prior written permission.
   *
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
   ---------------------------------------------------------------------------*/


#include "utils.h"

//----------------------------------------------------------------------------
//  Enable RNG
//----------------------------------------------------------------------------
void ConfigureRNG(void){

    RCC->AHBENR |= RCC_AHBENR_RNGEN ;           /*!< RNG clock enable */
    RNG->CR |= RNG_CR_RNGEN  ;  
}

//----------------------------------------------------------------------------
// Enable serial communication at 57600 bauds
//----------------------------------------------------------------------------
int mystdout_init (void) {
  
  uint8_t idx ;  

    
  RCC->IOPENR   |=   ( 1ul <<  0);                   /* Enable GPIOA clock */
  RCC->APB1ENR  |=   ( 1ul << 17);                   /* Enable USART#2 clock */

  /* Configure PA3 to USART2_RX, PA2 to USART2_TX */
  GPIOA->AFR[0] &= ~((15ul << 4* 3) | (15ul << 4* 2) );
  GPIOA->AFR[0] |=  (( 4ul << 4* 3) | ( 4ul << 4* 2) );
  GPIOA->MODER  &= ~(( 3ul << 2* 3) | ( 3ul << 2* 2) );
  GPIOA->MODER  |=  (( 2ul << 2* 3) | ( 2ul << 2* 2) );

  //USARTx->BRR  = __USART_BRR(1048000ul, 57600ul);  /* 57600 baud @ 1.048MHz (MSI) */
	USARTx->BRR  = __USART_BRR(4000000ul, 57600ul);  /* 57600 baud @ 4MHz, use this for the HSE */
  USARTx->CR3    = 0x0000;                           /* no flow control */
  USARTx->CR2    = 0x0000;                           /* 1 stop bit */
  USARTx->CR1    = ((   1ul <<  2) |                 /* enable RX */
                    (   1ul <<  3) |                 /* enable TX */
                    (   0ul << 12) |                 /* 8 data bits */
                    (   0ul << 28) |                 /* 8 data bits */
                    (   1ul <<  0) );                /* enable USART */
  
	//Wait for USART to get ready
  for( idx = 0 ; idx < 20 ; idx++){
        __NOP();
  }
  return (0);    
    
}

//-------------------------------------------------------------------------------
// Convert string to hex numbers
//-------------------------------------------------------------------------------
void str2hex( unsigned char* buffer, unsigned char* hex_buf ){
    uint8_t hex, hhex, nib, idx, i ;
    
  //Convert the ascii buffer into an array of uint8_t
  nib = 0 ;
  idx = 0 ;
  for( i=0 ; i<BUF_SIZE ; i++ ){

    //0 ... 9
    if( buffer[i]>= 0x30 && buffer[i]<=0x39 ){
        hex = buffer[i] - 0x30 ;
    //A ... F
    }else if( buffer[i]>= 0x41 && buffer[i]<=0x46 ){
        hex = buffer[i] - 0x41 + 0x0A ;
    //a ... f
    }else if( buffer[i]>= 0x61 && buffer[i]<=0x66 ){
        hex = buffer[i] - 0x61 + 0x0A ;            
    }else{
        hex = 0x0 ;
    }
    
    if( nib == 0 ){
        hhex = hex<<4 ;
        nib = 1 ;
    }else{
        hex_buf[idx] = hhex | hex ;
        idx++ ;
        nib = 0 ;   
    } 
  }       
}

//---------------------------------------------------------------------------------
// Get a char from the serial interface
//---------------------------------------------------------------------------------
uint8_t stdin_getchar(){
    while( (USARTx->ISR & USART_ISR_RXNE) == 0);
    return USARTx->RDR ;
}

//---------------------------------------------------------------------------------
// Put a char to the serial interface
//---------------------------------------------------------------------------------
int stdout_putchar (int ch) {

  while (!(USARTx->ISR & 0x0080));
  USARTx->TDR = (ch & 0xFF);
  return (ch);
}


//---------------------------------------------------------------------------------
// Read a line from the serial interface
//---------------------------------------------------------------------------------
void rdser( uint8_t * buffer ){
    uint8_t i = 0 , c = 0 ;
    
    //Clear the buffer
    for( i=0 ; i<BUF_SIZE ; i++)
        *(buffer+i) = 0 ;
    
    i = 0 ;
    c = stdin_getchar() ; 
    //Get data from the serial port until it is a CR
    while ( c != 0x0d ){
        buffer[i] = c ;
        c = stdin_getchar() ;                                
        i++ ;
        //Prevent buffer overflow
        if( i == BUF_SIZE )
            i = 0 ;
    }    
}

//------------------------------------------------------------------------------
//                                Print state
//------------------------------------------------------------------------------
void Print( uint8_t ct[16][N], uint8_t cto[16]){//, uint8_t nptxt[16] ){
    uint8_t i, j, k ;
    uint8_t F[N] ;
    uint8_t tmp[N] ;
    uint8_t pp[16] ;
        
    for( i=0 ; i<16 ; i++){
        for( j=0 ; j<N ; j++ ){
            F[j] = ct[i][j] ;   
        }
        gfmvmul(InvVand,F,tmp) ;
        pp[i] = tmp[0] ;
        //nptxt[i] = tmp[0] ;
    }

    //Print in colum-major order
    /*
    for ( i=0 ; i<16 ; i++ ){
        pc.printf("%02x", pp[i] );
    }
    */
    //Print in row-major order
    k = 0 ;
    for ( i=0 ; i<4 ; i++ ){
        for ( j=0 ; j<4 ; j++ ){
            //pc.printf("%02x", pp[i+(4*j)] );
            cto[k] = pp[i+(4*j)] ;
            k++ ;
        }
    }
    //pc.printf("\n");    
}

