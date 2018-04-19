#ifndef EMPRINTF_H
#define EMPRINTF_H

#include "/usr/include/stdio.h"
#include "/usr/lib/gcc/x86_64-linux-gnu/5/include/stdarg.h"
#include "/home/dev03/DSR/WebAssembly/emsdk/emscripten/1.37.36/system/include/emscripten.h"

#define MAX_MSG_LEN 1000

/* NOTE: Don't pass format strings that contain single quote (') or newline
* characters. */
static void emprintf(const char *format, ...)
{
    char msg[MAX_MSG_LEN];
    char consoleMsg[MAX_MSG_LEN + 16];
    va_list args;

    /* create the string */
    va_start(args, format);
    vsnprintf(msg, MAX_MSG_LEN, format, args);
    va_end(args);

    /* wrap the string in a console.log('') statement */
    snprintf(consoleMsg, MAX_MSG_LEN + 16, "console.log('%s')", msg);

    /* send the final string to the JavaScript console */
    emscripten_run_script(consoleMsg);
}

#endif // EMPRINTF_H
