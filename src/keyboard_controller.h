typedef struct {
  char *linux_pressed_key;
  int mac_pressed_key;
} keyboard_controller;

keyboard_controller* controller_create(void);
void controller_destroy(keyboard_controller *instance);
int controller_run(keyboard_controller *instance);
static void controller_press_key(keyboard_controller *instance, char* linux_key, int mac_key);
