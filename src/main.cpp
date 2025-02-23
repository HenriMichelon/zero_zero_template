#include <z0/macros.h>
#include "libraries.h"

import MyGame;

const ApplicationConfig applicationConfig{
    .appName = "Example App",
    .appDir = "..",
    .windowMode = WindowMode::WINDOWED,
    .windowWidth = 1280,
    .windowHeight = 720,
    .defaultFontName = "app://res/fonts/MontserratMedium.otf",
    .defaultFontSize = 30,
    .loggingMode = LOGGING_MODE_FILE | LOGGING_MODE_STDOUT,
    .framesInFlight = 2,
};

Z0_APP(applicationConfig, make_shared<MainScene>())
