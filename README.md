mkmx_RS485_fanctrl

Fan controler with speed measurment working in RS485 network.

Device measure fan speed in RPM, adjust speed to requested value. Using USART device 
recives necessary values from master device. Device can also respond via USART with 
current speed or any orher information. 

Defined frame in network:

byte number:	0		1		2		3		4		5...254	255
function		0x5A	0xA5	ADRR	CMD		PL_LEN	PL		CRC

0x5A 0xA5	-Start frame signal
ADRR 	-Device adress we are sending information to (0x00 is master adress)
CMD		-Command for device (set speed etc.)
PL_LEN  -Length (in nmber of bytes) of payload
PL 		-Payload (all informaiton we want to send to device)
CRC 	-Cyclic redundancy check

Rafał Stoalrczyk
Politechnika Łódzka 
