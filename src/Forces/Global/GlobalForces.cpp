#include "Forces/Global/GlobalForces.hpp"


MaxVelocityForce::MaxVelocityForce ( float max_velocity ) : max_velocity( max_velocity )
{
}


void MaxVelocityForce::actOnBoids ( std::vector<Boid>& boids )
{
  for ( auto& boid: boids )
  {
    utility::vec_t vel = boid.getVelocity();
    float velocity_magnitude = vel.x * vel.x + vel.y * vel.y;
    boid.setVelocity( max_velocity * vel / sqrtf( velocity_magnitude ));
  }
}


BoundaryForce::BoundaryForce ( int left, int right, int up, int down, float strength )
  : left( left ), right( right ), up( up ), down( down ), strength( strength )
{
}


void BoundaryForce::actOnBoids ( std::vector<Boid>& boids )
{
  for ( auto& boid: boids )
  {
    utility::vec_t res{ 0.f, 0.f };
    utility::vec_t vel = boid.getVelocity();
    utility::vec_t pos = boid.getPosition();

    float x = pos.x;
    float y = pos.y;

    if ( x < left )
    {
      res.x = strength;
    }
    else if ( x > right )
    {
      res.x = -strength;
    }
    if ( y < up )
    {
      res.y = strength;
    }
    else if ( y > down )
    {
      res.y = -strength;
    }
    vel += res;
    boid.setVelocity( vel );
  }
}


ObstacleForce::ObstacleForce ( utility::vec_t position, float strength ) : position( position ),
                                                                           strength( strength )
{
}


void ObstacleForce::actOnBoids ( std::vector<Boid>& boids )
{
  for ( auto& boid: boids )
  {
    utility::vec_t vel = boid.getVelocity();
    utility::vec_t diff = boid.getPosition() - position;
    float dist_squared = diff.x * diff.x + diff.y * diff.y;

    vel += strength * diff / ( dist_squared + 0.1f );

    boid.setVelocity( vel );
  }
}