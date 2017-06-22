#ifndef FIRE_H
#define FIRE_H

#include "Particle.h"

class Fire : public Particle
{
public:
    Fire();
    ~Fire();

protected:
    void initializeParticle(Particle &p);
    void updateParticle(Particle &p);
};

#endif // FIRE_H
