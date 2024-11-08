module;
import std;
import glm;
import z0;
using namespace std;
using namespace glm;
using namespace z0;

export module MyGame;

export class MainScene : public Node {
public:
    void onReady() override {
        addChild(make_shared<Skybox>("app://res/textures/studio_small_08_2k.hdr"));
        addChild(make_shared<Environment>(vec4{1.0, 1.0, 1.0, 1.0f}));

        player = make_shared<Node>();
        player->setPosition({0.0f, 0.0f, 0.5f});
        addChild(player);

        cameraPivot = make_shared<Node>();
        player->addChild(cameraPivot);

        const auto camera = make_shared<Camera>();
        cameraPivot->addChild(camera);

        cube = Loader::load("app://res/models/cube.glb");
        addChild(cube);

        //captureMouse();

        log("Main scene is ready");
    }

    void onEnterScene() override {
        constexpr float padding = 5.0f;
        const auto      menu    = make_shared<GWindow>(Rect{0, 0, 10, 10});
        Application::get().add(menu);
        menu->getWidget().setDrawBackground(false);
        menu->getWidget().setPadding(padding);

        const auto textQuit   = make_shared<GText>("Quit");
        const auto buttonQuit = make_shared<GButton>();
        menu->getWidget().add(buttonQuit, GWidget::LEFTCENTER, "50,40");
        buttonQuit->add(textQuit, GWidget::CENTER);
        buttonQuit->connect(GEvent::OnClick, []{Application::get().quit();});

        menu->setHeight(textQuit->getHeight() + padding * 4);
        menu->setWidth(textQuit->getWidth() + padding * 4);
        menu->setY(VECTOR_SCALE.y - menu->getHeight());
    }

    void onPhysicsProcess(const float delta) override {
        previousState = currentState;
        currentState  = State{};

        if (mouseCaptured) {
            vec2 inputDir = Input::getKeyboardVector(KEY_LEFT, KEY_RIGHT, KEY_UP, KEY_DOWN);
            if (inputDir != VEC2ZERO) {
                currentState.lookDir = inputDir * viewSensitivity * delta;
            }
        }

        const auto angle = delta * radians(90.0f) / 2;
        cube->rotateX(angle);
        cube->rotateZ(angle);
    }

    void onProcess(const float alpha) override {
        if (currentState.lookDir != VEC2ZERO) {
            const auto interpolatedLookDir = previousState.lookDir * (1.0f - alpha) + currentState.lookDir * alpha;
            player->rotateY(-interpolatedLookDir.x * 2.0f);
            cameraPivot->rotateX(interpolatedLookDir.y * keyboardInvertedAxisY);
            cameraPivot->setRotationX(std::clamp(cameraPivot->getRotationX(), maxCameraAngleDown, maxCameraAngleUp));
        }
    }

    bool onInput(InputEvent &event) override {
        if (mouseCaptured && (event.getType() == InputEventType::MOUSE_MOTION)) {
            const auto &eventMouseMotion = dynamic_cast<InputEventMouseMotion &>(event);
            player->rotateY(-eventMouseMotion.getRelativeX() * mouseSensitivity);
            cameraPivot->rotateX(eventMouseMotion.getRelativeY() * mouseSensitivity * mouseInvertedAxisY);
            cameraPivot->setRotationX(std::clamp(cameraPivot->getRotationX(), maxCameraAngleDown, maxCameraAngleUp));
            return true;
        }
        if ((event.getType() == InputEventType::MOUSE_BUTTON) && (!mouseCaptured)) {
            const auto &eventMouseButton = dynamic_cast<InputEventMouseButton &>(event);
            if (!eventMouseButton.isPressed()) {
                captureMouse();
                return true;
            }
        }
        if ((event.getType() == InputEventType::KEY) && mouseCaptured) {
            const auto &eventKey = dynamic_cast<InputEventKey &>(event);
            if ((eventKey.getKey() == KEY_ESCAPE) && !eventKey.isPressed()) {
                releaseMouse();
                return true;
            }
        }
        return false;
    }

private:
    struct State {
        vec2   lookDir = VEC2ZERO;
        State &operator=(const State &other) = default;
    };

    const float mouseSensitivity   = 0.008f;
    const float viewSensitivity    = 0.2f;
    const float maxCameraAngleUp   = radians(60.0);
    const float maxCameraAngleDown = -radians(45.0);

    bool             mouseCaptured{false};
    float            mouseInvertedAxisY{1.0};
    float            keyboardInvertedAxisY{1.0};
    State            previousState;
    State            currentState;
    shared_ptr<Node> player;
    shared_ptr<Node> cube;
    shared_ptr<Node> cameraPivot;

    void captureMouse() {
        if (!mouseCaptured) {
            Input::setMouseMode(MouseMode::HIDDEN_CAPTURED);
            mouseCaptured = true;
        }
    }

    void releaseMouse() {
        Input::setMouseMode(MouseMode::VISIBLE);
        mouseCaptured = false;
    }
};
