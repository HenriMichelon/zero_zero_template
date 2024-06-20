#pragma once

class MainScene: public Node {
public:
    void onReady() override;
    void onEnterScene() override;
    void onPhysicsProcess(float delta) override;
    void onProcess(float alpha) override;
    bool onInput(InputEvent& event) override;

private:
    struct State {
        vec2 lookDir = VEC2ZERO;
        State& operator=(const State& other) = default;
    };

    const float mouseSensitivity = 0.008f;
    const float viewSensitivity = 0.2f;
    const float maxCameraAngleUp = radians(60.0);
    const float maxCameraAngleDown = -radians(45.0);

    bool mouseCaptured{false};
    float mouseInvertedAxisY{1.0};
    float keyboardInvertedAxisY{1.0};
    State previousState;
    State currentState;
    shared_ptr<Node> player;
    shared_ptr<Node> cube;
    shared_ptr<Node> cameraPivot;

    void onMenuQuit();
    void captureMouse();
    void releaseMouse();
};
