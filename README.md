# Robust-AES
This is an AES-128 implementaition using Shamir's Secret Sharing scheme and resistant to d-th order side channel and partially resistant to fault injection attacks.

Vernam Lab - Worcester Politechnic Institute - May 2017

This code is based upon work supported by the National Science Foundation under Grant No.1261399.

### Instructions:
1. Open Robust-AES.uvprojx in KEIL
2. Choose (n,d) and other parameters in <your_clone>/Keil-Nucleo-L053R8/rAES/params.h
3. Build and flash STM32-L053R8 MCU (Nucleo L053R8)
4. Press Nucleo reset button
5. Setup serial communication, follow comments in <your_clone>/testing/test-aes.py
6. Run testing script: python test-aes.py
