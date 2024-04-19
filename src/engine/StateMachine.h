//
// Created by lucas on 27.01.24.
//

#ifndef PATHFINDING_STATEMACHINE_H
#define PATHFINDING_STATEMACHINE_H

#include "memory"
#include "stack"
#include "State.h"

namespace engine
{
    typedef std::unique_ptr<State> StateRef;

    class StateMachine
    {
    public:
        StateMachine() = default;

        ~StateMachine() = default;

        void addState(StateRef newState, bool isReplacing = true);

        void removeState();

        void processStateChanges();

        StateRef &getActiveState();

    private:
        std::stack<StateRef> _states;
        StateRef _newState;

        bool _isRemoving;
        bool _isAdding;
        bool _isReplacing;
    };
}

#endif // PATHFINDING_STATEMACHINE_H
