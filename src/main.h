#pragma once

class MainScene: public Node, public GEventHandler {
public:
    void onReady() override;
    void onEnterScene() override;

private:
    void onMenuQuit(GWidget*, GEvent*);
};
