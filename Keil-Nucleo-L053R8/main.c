/**********************************************************************
 Vernam Lab - Worcester Polytechnic Institute (vernam.wpi.edu)
 Robust AES: Secure Multiparty Computation based AES encryption
 
 Authors: Abraham Fernandez-Rubio, Thomas Eisenbarth and Okan Seker
 
 More details here:
 https://web.wpi.edu/Pubs/ETD/Available/etd-042717-122213/unrestricted/afernandezrubio.pdf
***********************************************************************/ 


#include "stm32l0xx.h"
#include "rAES\raes.h"
#include "utils.h"
#include "string.h"

int main(void)
{ 
    uint8_t i,j;
    //These are in colum-major order
    uint8_t PTX[16] ;
    uint8_t KEY[16] = {0x2b,0x28,0xab,0x09,0x7e,0xae,0xf7,0xcf,0x15,0xd2,0x15,0x4f,0x16,0xa6,0x88,0x3c}; 
    uint8_t CTO[16];
    
		// Shared plaintext, keys and ciphertext
    uint8_t ptxs[16][N] ;
		uint8_t keys[16][N] ;
		uint8_t ctxs[16][N] ;
    
    uint8_t buf[BUF_SIZE] ; 		

		// MCU setup
    SystemClock_Config();
    ConfigureGPIO();
    RCC->CFGR |= RCC_CFGR_MCO_SYSCLK; /* Select system clock to be output on the MCO without prescaler */
    mystdout_init();
    ConfigureRNG();

    while (1){
      
        //Go to http://aes.online-domain-tools.com/ to compare results
        //the key is: 2b7e151628aed2a6abf7158809cf4f3c in hex

        //Get plaintext
        rdser(buf); 
        //Turn plaintext into hex
        str2hex(buf,PTX) ; 
        
				//Print plaintext to serial port
        for ( i=0 ; i<4 ; i++ ){
            for ( j=0 ; j<4 ; j++ ){
                printf("%02x", PTX[i+(4*j)] );
            }
        }
        printf("\n");			
				
				// Share plaintext
				share(PTX,ptxs);
				// Share key
				share(KEY,keys);
				/***	Encrypt	***/
				//Trigger GPIO pin PB9 to measure execution time
				GPIOB->BSRR = (1 << 9);				
				encrypt(ptxs, keys, ctxs);
				//Reset pin PB9
				GPIOB->BSRR = (1 << 25); 
							
				//CTO is a printable array
				Print(ctxs, CTO);
				
				//Print ciphertext
				for ( i=0 ; i<16 ; i++ ){
					 printf("%02x", CTO[i] );
				}
				printf("\nbyebye\n");   
        
    }//end-while(1)
}//end-main()
