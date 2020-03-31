#ifndef _constants_h_
#define _constants_h_

#define FPS  						30
#define SPF 						1000.0 / FPS

#define WIDTH 						320
#define HEIGHT  					240
#define ALPHA_COLOR 				0xf81f
#define SPR_WIDTH       			742
#define SPR_HEIGHT      			304

// Pushbutton keys
#define KEY1 						0
#define KEY2  						1
#define KEY3 						2
								
#define KEY3_MASK					0x00000008
#define KEY2_MASK					0x00000004
#define KEY1_MASK					0x00000002

// 7 segments numbers
#define SEGMENT_0 					0x3F
#define SEGMENT_1 					0x06
#define SEGMENT_2 					0x5B
#define SEGMENT_3 					0x4F
#define SEGMENT_4 					0x66
#define SEGMENT_5 					0x6D
#define SEGMENT_6 					0x7D
#define SEGMENT_7 					0x07
#define SEGMENT_8 					0x7F
#define SEGMENT_9 					0x67

// Memory addresses
#define PUSH_BUTTON_ADDR			0x1000005c
#define BACK_BUFFER_REG_ADDR 		0x10003024

//#define TIMER_ADDR					0x10002000
#define PS2_ADDR 					0x10000100
#define	VIDEO_ADDR					0x08000000

// Flag adicional para o linker: -Ttext=0x200

#endif
