import serial
import time
import uuid 

#Install pyserial: $> pip install pyserial

#Function to Initialize the Serial Port
def init_serial():
    global ser          #Must be declared in Each Function
    ser = serial.Serial()
    ser.baudrate = 57600
    ser.port = 'COM5'
    #ser.port = '/dev/ttyACM0' 			#If Using Linux
    #ser.port = '/dev/tty.usbmodem1423' #If Using Mac
    
	#Specify the TimeOut in seconds
    ser.timeout = 15
    ser.open()          


f = None
ser = 0
init_serial()

file_name = time.strftime('%Y%m%d-%H%M%S') + 'ptxt-ctxt.txt'
f = open(file_name,'w')

for seq_num in range(3):        
	#Generate a pseudo random plaintext
	rand_ptxt = uuid.uuid4().hex
	#uC will rearranged the plaintext to column-major order
	#print 'Plaintext: ' + rand_ptxt

	#Send plaintext to Nucleo
	ser.write(rand_ptxt + '\r')
	serstr = ser.readline() 
	print '\n%d ---\nplaintext: \n%s\nciphertext: ' %  (seq_num, serstr.rstrip("\n\r"))
	f.write('\n%d ---\nplaintext : %s\nciphertext: ' % (seq_num,serstr.rstrip("\n\r")))

	#Read plaintext back from Nucleo
 
	while (serstr != 'byebye'):    
		serstr = ser.readline()  #Read from Serial Port
		serstr = serstr.rstrip("\n\r")
		if (serstr != 'byebye'): 
			print serstr
			f.write('%s\n' % serstr)
			
f.write('\n\nGo to http://aes.online-domain-tools.com/ select ECB mode, input the plaintext\nand key: 2b7e151628aed2a6abf7158809cf4f3c in hex to compare results.' )
f.close()
print '\nencryption finished.\n\n'
ser.close()

