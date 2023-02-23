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
  if(timer > 2 || timer < 0){
  	printf("timer_get_conf::Invalid input, timer index out of range!\n");
    return 1;
  }

  if(sys_outb(TIMER_CTRL,TIMER_RB_CMD | TIMER_RB_STATUS_ | TIMER_RB_SEL(timer)) != OK){
    printf("timer_get_conf::Error writing control word to the timer control register!\n");
		return 1;
  }  
  uint32_t temp;
  int timer_aux = TIMER_0+timer;

  if (sys_inb(timer_aux, &temp) !=OK){
    printf("timer_get_conf::Error receiving the output from the timer");
    return 1;
  }

  *st = (uint8_t) temp;
  return 0;
}

enum timer_init initializationMode(uint8_t *st){

  *st = *st >> 4;
  *st &= 0x03;

  //defines the init mode
  switch (*st) {
    case 0x01:
      return LSB_only;
    case 0x02:
      return MSB_only;
    case 0x03:
      return MSB_after_LSB;
    default:
      return INVAL_val;
  }

}

uint8_t countMode(uint8_t st){

  //defines the count mode (0 through 5)
  switch (st) {
    case 0x06:
      return 2;
    case 0x07:
      return 3;
    default:
      return st;
  }

}

int (timer_display_conf)(uint8_t timer, uint8_t st,
                        enum timer_status_field field) {
  union timer_status_field_val status;

  switch (field)
  {
    case tsf_all:
      status.byte = st;
      break;
    case tsf_initial:
      switch(st & TIMER_LSB_MSB){
        case(TIMER_LSB):
          status.in_mode = LSB_only;
          break;

        case(TIMER_MSB):
          status.in_mode = MSB_only;
          break;

        case(TIMER_LSB_MSB):
          status.in_mode = MSB_after_LSB;
          break;

        default:
          status.in_mode = INVAL_val;
          break;
      }
      break;
    case tsf_mode:
       switch(st & TIMER_OPERATING_MODE){
        case(TIMER_INT_TERM_COUNT):
          status.count_mode = 0;
          break;
        case(TIMER_HW_RETRIG_ONES):
          status.count_mode = 1;
          break;
        case(TIMER_RATE_GEN):
          status.count_mode = 2;
          break;
        case(BIT(3) | TIMER_RATE_GEN): //alternative to mode 2 (110)
          status.count_mode = 2; 
          break;
        case(TIMER_SQR_WAVE):
          status.count_mode = 3;
          break;
        case(BIT(3) | TIMER_SQR_WAVE): //alternative to mode 3 (111)
          status.count_mode = 3; 
          break;
        case(TIMER_SW_TRIG_STROBE):
          status.count_mode = 4;
          break;
        case(TIMER_HW_TRIG_STROBE):
          status.count_mode = 5;
          break;
        }
      break;
    case tsf_base:
      if((BIT(0) & st)==1)
        status.bcd=true;
      else 
        status.bcd=false;
    default: 
      printf("timer_display_conf::Invalid field inserted\n");
      return 1;
  }

  if(timer_print_config(timer,field,status) != OK){
    return 1;
  }

  return 0;
}
