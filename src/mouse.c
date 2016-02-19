/*
Copyright (C) 2015 The University of Notre Dame
This software is distributed under the GNU General Public License.
See the file LICENSE for details.
*/

#include "mouse.h"
#include "interrupt.h"
#include "console.h"
#include "ps2.h"
#include "ioports.h"
#include "process.h"
#include "graphics.h"

static struct list queue = { 0, 0 };

static int mouse_scan() {
    int code;
    int data;
    code = inb(MOUSE_DATA_PORT);
    iowait();
    data = inb(MOUSE_CHECK_PORT);
    iowait();

    // see if data to be read on MOUSE_DATA_PORT
    if (((code >> 1) & 0x01) == 0) {
        return -1;
    }

    // mouse bit
    if (((data >> 5) & 0x01) != 0) {
        return -1;
    }
    return code;
}

int mouse_map() {
    
}

void mouse_interrupt() {
    int data = inb(MOUSE_DATA_PORT);
    int command;
    command = mouse_map(mouse_scan());

    if (!command) {

    }
    process_wakeup(&queue);
}

void mouse_init() {
    interrupt_register(44, mouse_interrupt);
    mouse_scan();
    interrupt_enable(44);
    console_printf("mouse: ready\n");
}

