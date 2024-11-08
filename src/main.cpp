#include <z0/macros.h>
import std;
import z0;
using namespace z0;

import MyGame;

const ApplicationConfig applicationConfig{
        .appName = "Example App",
        .appDir = "..",
        .windowMode = WindowMode::WINDOWED,
        .windowWidth = 1280,
        .windowHeight = 720,
        .defaultFontName = "app://res/fonts/MontserratMedium.otf",
        .defaultFontSize = 30,
        .loggingMode = LOGGING_MODE_FILE | LOGGING_MODE_WINDOW
};

Z0_APP(applicationConfig, std::make_shared<MainScene>())
