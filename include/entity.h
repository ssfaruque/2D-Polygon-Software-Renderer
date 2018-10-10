#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>

#include "types.h"


class Entity
{
    protected:
        uint m_id;
        Color m_color;

    public:
        virtual void draw() = 0;
        virtual void printDescription() const = 0;
        void setColor(Color color)
        {m_color = color;}

        Entity():
        m_id(0), m_color(0xFFFFFFFF)
        {}

        inline uint getId() const {return m_id;}
};






#endif