#include <z0/macros.h>
import std;
import Z0;
using namespace z0;

import MyGame;

const ApplicationConfig applicationConfig {
    .appName = "Example App",
    .appDir = "..",
    .windowMode = WINDOW_MODE_FULLSCREEN,
    .windowWidth = 1920,
    .windowHeight = 1080,
    .defaultFontName = "res/fonts/MontserratMedium.otf",
    .defaultFontSize = 30,
    .loggingMode = LOGGING_FILE | LOGGING_STDOUT
};

Z0_APP(applicationConfig, std::make_shared<MainScene>())