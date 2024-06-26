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
    buttonQuit->connect(GEvent::OnClick, this, Signal::Handler(&MainScene::onMenuQuit));

    menu->setHeight(textQuit->getHeight() + padding * 4);
    menu->setWidth(textQuit->getWidth() + padding * 4);
    menu->setY(VECTOR_SCALE.y - menu->getHeight());
}

void MainScene::onReady() {
    addChild(make_shared<Skybox>("res/textures/StandardCubeMap.png"));
    addChild(make_shared<Environment>(vec4{1.0,1.0,1.0,0.8f}));
    auto directionalLight = make_shared<DirectionalLight>(
        vec3{-1.0f, -1.0f, -1.0f},
        vec4{-0.5f, -0.5f, 1.0f, 1.0f}
    );
    directionalLight->setCastShadow(true);
    addChild(directionalLight);

    player = make_shared<Node>();
    player->setPosition({0.0f, 0.0f, 0.5f});
    addChild(player);

    cameraPivot = make_shared<Node>();
    player->addChild(cameraPivot);

    auto camera = make_shared<Camera>();
    cameraPivot->addChild(camera);

    cube = Loader::loadModelFromFile("res/models/cube.glb");
    addChild(cube);

    captureMouse();

    log("Main scene is ready");
}

void MainScene::onPhysicsProcess(float delta) {
    previousState = currentState;
    currentState = State{};

    if (mouseCaptured) {
        vec2 inputDir = Input::getKeyboardVector(KEY_LEFT, KEY_RIGHT, KEY_UP, KEY_DOWN);
        if (inputDir != VEC2ZERO) {
            currentState.lookDir = inputDir * viewSensitivity * delta;
        }
    }

    auto angle = delta * radians(90.0f) / 2;
    cube->rotateX(angle);
    cube->rotateZ(angle);
}

void MainScene::onProcess(float alpha) {
    if (currentState.lookDir != VEC2ZERO) {
        auto interpolatedLookDir = previousState.lookDir * (1.0f-alpha) + currentState.lookDir * alpha;
        player->rotateY(-interpolatedLookDir.x * 2.0f);
        cameraPivot->rotateX(interpolatedLookDir.y * keyboardInvertedAxisY);
        cameraPivot->setRotationX(std::clamp(cameraPivot->getRotationX() , maxCameraAngleDown, maxCameraAngleUp));
    }
}

bool MainScene::onInput(InputEvent& event) {
    if (mouseCaptured && (event.getType() == INPUT_EVENT_MOUSE_MOTION)) {
        auto& eventMouseMotion = dynamic_cast<InputEventMouseMotion&>(event);
        player->rotateY(-eventMouseMotion.getRelativeX() * mouseSensitivity);
        cameraPivot->rotateX(eventMouseMotion.getRelativeY() * mouseSensitivity * mouseInvertedAxisY);
        cameraPivot->setRotationX(std::clamp(cameraPivot->getRotationX(), maxCameraAngleDown, maxCameraAngleUp));
        return true;
    }
    if ((event.getType() == INPUT_EVENT_MOUSE_BUTTON) && (!mouseCaptured)) {
        auto& eventMouseButton = dynamic_cast<InputEventMouseButton&>(event);
        if (!eventMouseButton.isPressed()) {
            captureMouse();
            return true;
        }
    }
    if ((event.getType() == INPUT_EVENT_KEY) && mouseCaptured) {
        auto& eventKey = dynamic_cast<InputEventKey&>(event);
        if ((eventKey.getKey() == KEY_ESCAPE) && !eventKey.isPressed()) {
            releaseMouse();
            return true;
        }
    }
    return false;
}

void MainScene::onMenuQuit() {
    app().quit();
}

void MainScene::captureMouse() {
    if (!mouseCaptured) {
        Input::setMouseMode(MOUSE_MODE_HIDDEN_CAPTURED);
        mouseCaptured = true;
    }
}

void MainScene::releaseMouse() {
    Input::setMouseMode(MOUSE_MODE_VISIBLE);
    mouseCaptured = false;
}

const ApplicationConfig applicationConfig {
    .appName = "Example App",
    .appDir = "..",
    .windowMode = WINDOW_MODE_FULLSCREEN,
    .windowWidth = 1920,
    .windowHeight = 1080,
    .defaultFontName = "res/fonts/MontserratMedium.otf",
    .defaultFontSize = 30,
    .loggingMode = static_cast<LoggingMode>(LOGGING_FILE)
};

Z0_APP(applicationConfig, make_shared<MainScene>())