#pragma once

#include "cinder/gl/gl.h"
#include "utility.hpp"


class Boid
{

public:

    using vec_t = utility::vec_t;
    using color_t = cinder::Color;

    explicit Boid ( vec_t pos );

    ~Boid ();

    void draw ( cinder::gl::BatchRef& );

    void update ( const float& dt );

    vec_t getPosition () const;

    vec_t getVelocity () const;

    void setVelocity ( vec_t );

private:

    vec_t pos;

    vec_t vel = vec_t{ 0.f, 0.f };

    color_t col = color_t{ 1.f, 1.f, 1.f };
};
