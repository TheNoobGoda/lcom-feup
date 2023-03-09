#include <lcom/lcf.h>
#include <keyboard.h>

int hook_id =0;

int (keyboard_subscribe_interrupts)(uint8_t *bit_no) {
    bit_no = (uint8_t*)hook_id;

    if(sys_irqsetpolicy(1,IRQ_REENABLE,&hook_id)!=0){
      printf("Error in setting policy\n");
      return 1;
    }
    
    if(sys_irqsetpolicy(1,IRQ_REENABLE,&hook_id)!=0){
      printf("Error in setting policy\n");
      return 1;
    }
    
    return 0;
}   

int (keyboard_unsubscribe_interrupts)() {
  if(sys_irqrmpolicy(&hook_id)!=0){
    printf("Error removing policy\n");
    return 1;
  }
  if(sys_irqrmpolicy(&hook_id)!=0){
    printf("Error removing policy\n");
    return 1;
  }

  return 0;
}

void (kbc_ih)() {
    int make = TRUE;
    uint8_t size = 1;
    uint8_t bytes = 0x05;
    kbd_print_scancode(make,size,&bytes);
}
