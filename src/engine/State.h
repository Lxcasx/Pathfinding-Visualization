//
// Created by lucas on 27.01.24.
//

#ifndef PATHFINDING_STATE_H
#define PATHFINDING_STATE_H

namespace engine {
    class State {
    public:
        virtual void init() = 0;

        virtual void handleInput() = 0;

        virtual void update(float dt) = 0;

        virtual void draw(float dt) = 0;

        virtual void pause() {}

        virtual void resume() {}
    };
}

#endif //PATHFINDING_STATE_H
