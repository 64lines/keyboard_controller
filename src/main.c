/**
 * The goal of this program is to control the keyboard
 * through received commands through DECT of the Nordic board.
 */
#include "keyboard_controller.h"

int main()
{
  keyboard_controller *ctrl = controller_create();
  int err = controller_run(ctrl);

  if (err != 0) {
    return err;
  }

  return 0;
}

