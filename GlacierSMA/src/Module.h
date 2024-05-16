#pragma once

#include <initializer_list>
#include <vector>

#include "Ressource.h"

class Module {

    public:
        enum State {
            UNAVAILABLE = -1,
            OFFLINE = 0,
            ONLINE = 1
        };

        const char* label;

    protected:
        State state = State::OFFLINE;

        virtual bool _begin() = 0;
        virtual bool _end() = 0;

    private:
        std::vector<Ressource*> ressources;
    
    public:
        Module(const char* label, std::initializer_list<Ressource*> ressources):
            label(label), ressources(ressources) {}
        
        ~Module() {
            if (state == State::ONLINE)
                end();
        };

        bool begin() {
            for (Ressource* ressource : ressources)
                ressource->acquire(this);
            return _begin();
        }

        bool end() {
            return _end();
        }
};
