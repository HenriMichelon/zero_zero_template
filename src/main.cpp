#include <z0/z0.h>
using namespace z0;

#include "main.h"

void MainScene::onEnterScene() {
    const float padding = 5.0f;
    auto menu = make_shared<GWindow>(Rect{0, 0, 10, 10});
    app().addWindow(menu);
    menu->getWidget().setDrawBackground(false);
    menu->getWidget().setPadding(padding);

    auto textQuit = make_shared<GText>("Quit");
    auto buttonQuit = make_shared<GButton>();
    menu->getWidget().add(buttonQuit, GWidget::LEFTCENTER, "50,40");
    buttonQuit->add(textQuit, GWidget::CENTER);
    buttonQuit->connect(GEvent::OnClick, this, GEventFunction(&MainScene::onMenuQuit));

    menu->setHeight(textQuit->getHeight() + padding * 4);
    menu->setWidth(textQuit->getWidth() + padding * 4);
    menu->setY(1000 - menu->getHeight());
}

void MainScene::onReady() {
    log("Example ready");
}

void MainScene::onMenuQuit(GWidget*, GEvent *) {
    app().quit();
}

const ApplicationConfig applicationConfig {
    .appName = "Example App",
    .appDir = "..",
    .windowMode = WINDOW_MODE_FULLSCREEN,
    .windowWidth = 1920,
    .windowHeight = 1080,
    .defaultFontName = "res/fonts/OpenSans-Regular.ttf",
    .defaultFontSize = 12
};

Z0_APP(applicationConfig, make_shared<MainScene>())