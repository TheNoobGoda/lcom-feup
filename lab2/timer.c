#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  uint8_t st;
  timer_get_conf(timer,&st);

  st = st & 0x0f; // to keep the last 4 bits unchanged

  uint16_t init = TIMER_FREQ/freq;
  uint8_t msb,lsb;
  util_get_LSB(init,&lsb);
  util_get_MSB(init,&msb);

  uint8_t timer_sel;
  switch (timer)
  {
  case 0:
    timer_sel = TIMER_SEL0;
    break;
  
  case 1:
    timer_sel = TIMER_SEL1;
    break;

  case 2:
    timer_sel = TIMER_SEL2;
    break;

  default:
    printf("Error invalid timer\n");
    return 1;
    break;
  }

  if(sys_outb(TIMER_CTRL,timer_sel|TIMER_LSB_MSB|st) !=0){
    printf("Error on sys_outb\n");
    return 1;
  }

  if(sys_outb(TIMER_0+timer,lsb) != 0){
    printf("Error on sys_outb\n");
    return 1;
  }

  if(sys_outb(TIMER_0+timer,msb) != 0){
    printf("Error on sys_outb\n");
    return 1;
  }

  return 0;
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
    break;
  
  case tsf_mode:
    conf.count_mode = (st &(BIT(1) | BIT(2) | BIT(3)))>>1;
    if(conf.count_mode == 6) conf.count_mode = 2;
    if(conf.count_mode == 7) conf.count_mode = 3;
    break;
  
  case tsf_base:
    if (st & TIMER_BCD) conf.bcd = TIMER_BCD;
    else conf.bcd = TIMER_BIN;
    printf("base\n");
    break;
  
  default:
    printf("Invalid field\n");
    return 1;
    break;
  }

  timer_print_config(timer,field,conf);

  return 0;
}
