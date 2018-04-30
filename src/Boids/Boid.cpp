#include "Boids/Boid.hpp"


Boid::Boid ( utility::vec_t pos ) : pos( pos )
{
}


Boid::~Boid () = default;


void Boid::draw ( cinder::gl::BatchRef& batch )
{
  cinder::gl::ScopedModelMatrix scm;
  cinder::gl::translate( pos );
  cinder::gl::color( col );
  batch->draw();
}


void Boid::update ( const float& dt )
{
  pos += dt * vel;
}


utility::vec_t Boid::getPosition () const
{
  return pos;
}


utility::vec_t Boid::getVelocity () const
{
  return vel;
}


void Boid::setVelocity ( const utility::vec_t v )
{
  vel = v;
}

