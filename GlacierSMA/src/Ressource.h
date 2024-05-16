#pragma once

class Module;

class Ressource {
    enum State {
        UNAVAILABLE = -1,
        DISABLED = 0,
        ENABLED = 1
    };

    private:
        const char* name;
        State state;

    protected:
        Ressource(const char* name) {
            this->name = name;
            this->state = State::DISABLED;
        }

        bool enable() {
            if (state == State::UNAVAILABLE)
                return false;
            state = State::ENABLED;
            return true;
        }

        bool disable() {
            if (state == State::UNAVAILABLE)
                return false;
            state = State::DISABLED;
            return true;
        }

        void remove() {
            state = State::UNAVAILABLE;
        }

    public:
        virtual bool acquire(Module* user) = 0;
        virtual void release() = 0;
};
