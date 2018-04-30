#pragma once

#include <vector>

class Boid;

class Force
{

public:

    virtual void actOnBoids ( std::vector<Boid>& boids ) = 0;

    virtual ~Force () = default;

};


