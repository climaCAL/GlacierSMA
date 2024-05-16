#pragma once

class Module;

class Ressource {
    
    public:
        enum State {
            UNAVAILABLE = -1,
            DISABLED = 0,
            ENABLED = 1
        };

        const char* name;

    private:
        State state = State::DISABLED;

    protected:
        Ressource(const char* name):
            name(name) {}

        bool enable() {
            if (state == State::UNAVAILABLE)
                return false;
            state = State::ENABLED;
            return true;
        }

        void disable() {
            if (state != State::UNAVAILABLE)
                state = State::DISABLED;
        }

        void remove() {
            state = State::UNAVAILABLE;
        }

    public:
        State getState() const {
            return state;
        }

        virtual bool acquire(const Module* user) = 0;
        virtual bool release() = 0;
};

class SharedRessource : public Ressource {
    private:
        int nbUsers = 0;
    
    protected:
        SharedRessource(const char* name):
            Ressource(name) {}

    public:
        virtual bool acquire(const Module* user) {
            return enable() ? ++nbUsers : false;
        }

        virtual bool release() { // Warning: This method does not check if the same user releases more than once!
            if (nbUsers == 0)
                return false;
            else if (--nbUsers == 0)
                disable();
            return true;
        }
};

class ExclusiveRessource : public Ressource {
    private:
        const Module* usedBy = nullptr;
    
    protected:
        ExclusiveRessource(const char* name):
            Ressource(name) {}
        
    public:
        virtual bool acquire(const Module* user) { // NB: This will return false if you try to reacquire the same ressource.
            if (usedBy != nullptr || !enable())
                return false;
            usedBy = user;
            return true;
        }

        virtual bool release() { // Warning: This method does not check if the owner is the one releasing the ressource!
            if (usedBy == nullptr)
                return false;
            disable();
            usedBy = nullptr;
            return true;
        }
};
