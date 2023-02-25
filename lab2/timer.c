#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int (timer_subscribe_int)(uint8_t *bit_no) {
    /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int (timer_unsubscribe_int)() {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

void (timer_int_handler)() {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  
  if (sys_outb(TIMER_CTRL, TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(timer)) != 0){
    printf("Error in sys_outb\n");
    return 1;
  } 

  
  if(util_sys_inb(TIMER_0+timer,st) !=0){
    printf("Error in util_sys_inb\n");
    return 1;
  }
  return 0;
}

int (timer_display_conf)(uint8_t timer, uint8_t st,
                        enum timer_status_field field) {
  
  union timer_status_field_val conf;
  
  switch (field)
  {
  case tsf_all:
    conf.byte = st;
    printf("all\n");
    break;
  
  case tsf_initial:
    switch (st & TIMER_LSB_MSB)
    {
      case TIMER_LSB:
        conf.in_mode = LSB_only;
       break;
      case TIMER_MSB:
        conf.in_mode = MSB_only;
        break;
      case TIMER_LSB_MSB:
        conf.in_mode = MSB_after_LSB;
        break;

      default:
        conf.in_mode = INVAL_val;
        break;
    }
    printf("init\n");
    break;
  
  case tsf_mode:
    break;
  
  case tsf_base:
    break;
  
  default:
    break;
  }

  timer_print_config(timer,field,conf);

  return 0;
}
