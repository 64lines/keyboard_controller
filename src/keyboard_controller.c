#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "keyboard_controller.h"

#ifdef __APPLE__
    #include <ApplicationServices/ApplicationServices.h>
    // macOS Key Codes
    #define K_UP    (CGKeyCode)126
    #define K_DOWN  (CGKeyCode)125
    #define K_LEFT  (CGKeyCode)123
    #define K_RIGHT (CGKeyCode)124
#endif

keyboard_controller* controller_create(void)
{
  keyboard_controller *instance = malloc(sizeof(keyboard_controller));
  return instance;
}

int controller_run(keyboard_controller *instance)
{
  int times = 0;
  printf("Starting moving keys in 2 seconds...\n");
  sleep(2);

  // Examples for all four directions
  /**
  controller_press_key(instance, "Up", 126);
  controller_press_key(instance, "Down", 125);
  controller_press_key(instance, "Left", 123);
  controller_press_key(instance, "Right", 124);
  */

  /** Auto scrolling **/
  for (int i = 0; i < 40; i++) 
  {
    controller_press_key(instance, "Down", 125);
  }

  // while(1)
  // {
  //   printf("Listening to the board... %d\n", times);
  //   

  //   if (times == 20) 
  //   {
  //     printf("(!) Stopped listening\n");
  //     break;
  //   }

  //   times++;
  // }

  return 0;
}

static void controller_press_key(keyboard_controller *instance, char* linux_key, int mac_key)
{
    instance->linux_pressed_key = linux_key;
    instance->mac_pressed_key = mac_key;

    #ifdef __linux__
        // Construct the xdotool command string
        char command[50];
        sprintf(command, "xdotool key %s", linux_key);
        system(command);
    #elif __APPLE__
        CGEventSourceRef source = CGEventSourceCreate(kCGEventSourceStateCombinedSessionState);

        // Press
        CGEventRef d = CGEventCreateKeyboardEvent(source, (CGKeyCode)mac_key, true);
        CGEventPost(kCGHIDEventTap, d);

        usleep(50 * 1000);
        // Release
        CGEventRef u = CGEventCreateKeyboardEvent(source, (CGKeyCode)mac_key, false);
        CGEventPost(kCGHIDEventTap, u);

        CFRelease(d); CFRelease(u); CFRelease(source);
    #else
        printf("OS not supported for key simulation.\n");
    #endif
}
