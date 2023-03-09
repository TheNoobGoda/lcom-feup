#include "KBC.h"

int (read_KBC_status)(uint8_t* status){
    util_sys_inb(KBC_STATUS_REG,status);
    return status;
}

int (read_KBC_output)(uint8_t port, uint8_t *output){
    uint8_t status;

    uint8_t attemps = MAX_ATTEMPS;

    while (attemps) {
        //todo

        tickdelay(micros_to_ticks(WAIT_KBC));
        attemps --;
    }
    return 1;

}

int (write_KBC_command)(uint8_t port, uint8_t commandByte){

}
