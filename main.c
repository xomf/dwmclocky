#include <X11/Xlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  Display *display = XOpenDisplay(NULL);
  Window window = DefaultRootWindow(display);

  while (1) {
    time_t rawtime;
    struct tm *timeinfo;
    char buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, 80, "Time: %H:%M (%Y-%m-%d)", timeinfo);

    int batteryPercentage = 0;
    FILE *fp = fopen("/sys/class/power_supply/BAT0/capacity", "r");
    if (fp) {
      fscanf(fp, "%d", &batteryPercentage);
      fclose(fp);
      sprintf(buffer, "%s | Battery: %d%%", buffer, batteryPercentage);
    }

    XStoreName(display, window, buffer);
    XFlush(display);

    sleep(1);
  }

  XCloseDisplay(display);
  return 0;
}
