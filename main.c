#include <X11/Xlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main() {
  Display *display = XOpenDisplay(NULL);
  Window window = DefaultRootWindow(display);

  while (1) {
    time_t rawtime;
    struct tm *timeinfo;
    char buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, 80, "Time: %H:%M (%Y-%m-%d)", timeinfo);

    XStoreName(display, window, buffer);
    XFlush(display);

    sleep(1);
  }

  XCloseDisplay(display);
  return 0;
}
