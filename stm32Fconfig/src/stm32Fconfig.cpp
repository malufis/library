#include "stm32Fconfig.h"

//TODO: add your code here

void setupStm32Init::stm32Init(void)
{
	afio_cfg_debug_ports(AFIO_DEBUG_NONE);	
  
	delay(2000);
	
	pinMode(INPUT1, INPUT_PULLDOWN);
	pinMode(INPUT2, INPUT_PULLDOWN);
	pinMode(INPUT3, INPUT_PULLDOWN);
	pinMode(INPUT4, INPUT_PULLDOWN);
	
	pinMode(PORTS1, INPUT_ANALOG);
	pinMode(PORTS2, INPUT_ANALOG);
	pinMode(PORTS3, INPUT_ANALOG);
	pinMode(PORTS4, INPUT_ANALOG);
	
	pinMode(PORTS5, INPUT_PULLDOWN);
	pinMode(PORTS6, INPUT_PULLDOWN);
}

