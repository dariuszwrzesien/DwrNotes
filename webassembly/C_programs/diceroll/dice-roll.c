#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <emscripten/emscripten.h>

// The code inside the main will be executed once the WASM module loads.
int main(int argc, char ** argv) {
    printf("WebAssembly module loaded\n");
}

// Simple C function that returns a number between 1 and 6.
int EMSCRIPTEN_KEEPALIVE roll_dice() {
    srand ( time(NULL) );
    return rand() % 6 + 1;
}

