#pragma once

#include "Boids/Boid.hpp"

#include <vector>

#include "cinder/gl/gl.h"

class Force;

class BoidController
{

    std::vector<std::unique_ptr<Force>> forces;

    std::vector<Boid> boids;


public:

    BoidController ();

    void draw ( cinder::gl::BatchRef& );

    void update ( const float& dt );

    void addBoid ( const utility::vec_t& pos );

    void addForce ( std::unique_ptr<Force> force );

    long getNumBoids ();
};
