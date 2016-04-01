int main();
int _start() {
    return main();

    // invoke system call that kills the process
}

#include "syscall.h"

int main() {
    // while (1) {
    //     // testcall(37);
    // }

    create_window(200, 200, 200, 200);
    struct graphics_color fgcolor = {255,0,0};
    struct graphics_color bgcolor = {0,0,0};
    draw_string(30, 30, "Hello World!", &fgcolor, &bgcolor);

    // while(1) {}
    return 0;
}
