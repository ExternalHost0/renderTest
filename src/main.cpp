#include "Application.h"

int main() {
    if (Application::get().Init() != 0) return -1;
    Application::get().Loop();
    Application::get().FullQuit();
    return 0;
}

