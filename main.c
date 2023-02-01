#include <X11/Xlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  Display *display = XOpenDisplay(NULL);
  Window window = DefaultRootWindow(display);

  FILE *fp = fopen("/sys/class/power_supply/BAT0/capacity", "r");

  while (1) {
    time_t rawTime;
    struct tm *timeInfo;
    char buffer[80];

    time(&rawTime);
    timeInfo = localtime(&rawTime);

    strftime(buffer, 80, "Time: %H:%M (%Y-%m-%d)", timeInfo);

    if (fp) {
      char batteryCapacity[4];
      fseek(fp, 0, SEEK_SET);
      fscanf(fp, "%s", batteryCapacity);
      sprintf(buffer, "%s | Battery: %s%%", buffer, batteryCapacity);
    }

    XStoreName(display, window, buffer);
    XFlush(display);

    sleep(1);
  }

  if (fp) {
    fclose(fp);
  }
  XCloseDisplay(display);
  return 0;
}

