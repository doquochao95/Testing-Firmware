#include "global_config.h"
#include "global_scope.h"
#include "sys_config.h"

nextion_extension nextionFuntions;

void setup()
{
  start_up();
}

void loop() 
{
  nextionFuntions.nex_listening();
}
