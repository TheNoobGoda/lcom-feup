#include <lcom/lcf.h>
#include <keyboard.h>
#include "KBC.c"

int kb_hook_id = 1;

int (keyboard_subscribe_interrupts)(uint8_t *bit_no) {
    *bit_no = BIT(kb_hook_id);

    if(sys_irqsetpolicy(1,IRQ_REENABLE | IRQ_EXCLUSIVE,&kb_hook_id)!=0){
      printf("Error in setting policy\n");
      return 1;
    }
    
    
    return 0;
}   

int (keyboard_unsubscribe_interrupts)() {
  if(sys_irqrmpolicy(&kb_hook_id)!=0){
    printf("Error removing policy\n");
    return 1;
  }

  return 0;
}

void (kbc_ih)() {
    uint8_t output;
    uint8_t bytes[2];
    int size;
    int make;

    read_KBC_output(1,&output);

    if (output == TWO_BYTES){
      size =2;
      bytes[1] = output;
      read_KBC_output(1,&output);
      bytes[0] = output;
    } 
    else{
      size = 1;
      bytes[0] = output;
    } 

    if (output & MAKE_CODE) make = FALSE;
    else make = TRUE;

    kbd_print_scancode(make,1,bytes);
}

int (keyboard_restore)(){
  return 1;
}
