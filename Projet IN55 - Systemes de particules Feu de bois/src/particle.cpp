#include "particle.h"

Particle::Particle()
{
    m_Position = {0.0f,0.0f,0.0f};
    m_Velocity = {0.0f,0.0f,0.0f};
    m_Color = {1.0f,0.0f,0.0f,0.0f};
    m_fRotate = 0;
    m_fSize = 0;
    m_fAge = 0;
    m_fLifeTime = 0;
}


