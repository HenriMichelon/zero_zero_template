#include <z0/macros.h>
import std;
import Z0;
using namespace z0;

import MyGame;

const ApplicationConfig applicationConfig{
        .appName = "Example App",
        .appDir = "..",
        .windowMode = WINDOW_MODE_WINDOWED,
        .windowWidth = 1280,
        .windowHeight = 720,
        .defaultFontName = "res/fonts/MontserratMedium.otf",
        .defaultFontSize = 30,
        .loggingMode = LOGGING_FILE | LOGGING_WINDOW
};

Z0_APP(applicationConfig, std::make_shared<MainScene>())
