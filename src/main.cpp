#include "global_config.h"
#include "global_scope.h"
#include "sys_config.h"

nextion_extension nextionFuntions;
SimpleTimer timer;
void setup()
{
  start_up();
  timer.setInterval(60000, air_checking);
}

void loop()
{
  nextionFuntions.nex_listening();
  udp_listening();
  ethernet_checking();
  sensors_checking();
  timer.run();
}
