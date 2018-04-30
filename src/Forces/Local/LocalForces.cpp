#include "Forces/Local/LocalForces.hpp"


void CenterOfMassForce::actOnBoid ( Boid& boid )
{
  utility::vec_t vel = boid.getVelocity();
  utility::vec_t res{ 0.f, 0.f };
  auto neighbors = getNearestNeighbors( boid );

  for ( const auto& neighbor: neighbors )
  {
    vel += ( neighbor->getPosition() - boid.getPosition()) / (float) neighbors.size() / 100.f;
  }
  boid.setVelocity( vel );
}


void RepulsiveForce::actOnBoid ( Boid& boid )
{
  utility::vec_t vel = boid.getVelocity();
  utility::vec_t res{ 0.f, 0.f };
  auto neighbors = getNearestNeighbors( boid );

  for ( const auto& neighbor: neighbors )
  {
    utility::vec_t diff = neighbor->getPosition() - boid.getPosition();
    float dist_squared = diff.x * diff.x + diff.y * diff.y;
    vel -= 20.f * diff / ( dist_squared + 0.01f );
  }
  boid.setVelocity( vel );
}


void DirectionalForce::actOnBoid ( Boid& boid )
{
  utility::vec_t vel = boid.getVelocity();
  utility::vec_t res{ 0.f, 0.f };
  auto neighbors = getNearestNeighbors( boid );

  for ( const auto& neighbor: neighbors )
  {
    vel += ( neighbor->getVelocity() - vel ) / (float) neighbors.size() / 8.f;
  }
  boid.setVelocity( vel );
}