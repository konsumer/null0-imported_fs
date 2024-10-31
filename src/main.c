#include <stdio.h>

#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

#include <MiniFB.h>

#include "pntr_cartfs.h"
#define PNTR_PIXELFORMAT_ARGB
#define PNTR_IMPLEMENTATION
#include "pntr.h"

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

static pntr_image* screen;
static struct mfb_window* window;

void on_mouse_btn(struct mfb_window *window, mfb_mouse_button button, mfb_key_mod mod, bool isPressed) {
}

void on_mouse_move(struct mfb_window *window, int x, int y) {
}

void on_keyboard(struct mfb_window *window, mfb_key key, mfb_key_mod mod, bool isPressed) {
}

static pntr_image* logo;

void game_init() {
  logo = pntr_load_image("/zip/logo.png");
}

void game_update() {
  pntr_clear_background(screen, PNTR_RAYWHITE);
  pntr_draw_image(screen, logo, 0, 0);
}

void engine_main_loop() {
  if (mfb_update_ex(window, screen->data, SCREEN_WIDTH, SCREEN_HEIGHT) < 0) {
    exit(EXIT_SUCCESS);
  }
  game_update();
}

int main(int argc, char *argv[]) {
  window = mfb_open_ex("null0", SCREEN_WIDTH, SCREEN_HEIGHT, 0);
  if (!window) {
    fprintf(stderr, "Cound not open window.\n");
    return 1;
  }
  
  screen = pntr_new_image(SCREEN_WIDTH, SCREEN_HEIGHT);

  mfb_set_keyboard_callback(window, on_keyboard);
  mfb_set_mouse_button_callback(window, on_mouse_btn);
  mfb_set_mouse_move_callback(window, on_mouse_move);

  game_init();

  #ifdef EMSCRIPTEN
  emscripten_set_main_loop(engine_main_loop, 60, true);
  #else
  while(true) {
    engine_main_loop();
    mfb_wait_sync(window);
  }
  #endif
  return 0;
}

