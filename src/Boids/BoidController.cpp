#include "Boids/BoidController.hpp"
#include "Forces/Force.hpp"


BoidController::BoidController () : boids(), forces()
{
};


void BoidController::draw ( cinder::gl::BatchRef& batch )
{
  for ( auto& p: boids )
  {
    p.draw( batch );
  }
}


void BoidController::update ( const float& dt )
{
  for ( auto& force: forces )
  {
    force->actOnBoids( boids );
  }

  for ( auto& boid: boids )
  {
    boid.update( dt );
  }
}


void BoidController::addBoid ( const utility::vec_t& pos )
{
  boids.emplace_back( pos );
}


void BoidController::addForce ( std::unique_ptr<Force> force )
{
  forces.push_back( std::move( force ));
}


long BoidController::getNumBoids ()
{
  return boids.size();
}
