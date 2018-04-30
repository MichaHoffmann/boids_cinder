#pragma once

#include "Forces/Force.hpp"
#include "Forces/Local/SpatialHash.hpp"
#include "Boids/Boid.hpp"


template<class T>
class NearestNeighborForce : public Force
{

    float interactionRadius;

    SpatialHash neighborhood;

public:

    explicit NearestNeighborForce ( float radius ) :
      interactionRadius( radius ),
      neighborhood( radius, 2 * (int) radius )
    {
    }


    void setBoids ( std::vector<Boid>& boids )
    {
      neighborhood.clear();
      for ( auto boid: boids )
      {
        neighborhood.insert( boid );
      }
    }


    void actOnBoids ( std::vector<Boid>& boids ) override
    {
      setBoids( boids );
      for ( auto& boid: boids )
      {
        static_cast<T*>(this)->actOnBoid( boid );
      }
    }


    virtual void actOnBoid ( Boid& boid ) = 0;

protected:

    std::set<Boid*> getNearestNeighbors ( Boid& boid )
    {

      auto neighbors = neighborhood.getNeighbors( boid );
      for ( const auto& neighbor: neighbors )
      {
        utility::vec_t diff = neighbor->getPosition() - boid.getPosition();
        float dist_squared = diff.x * diff.x + diff.y * diff.y;
        if ( dist_squared >= interactionRadius * interactionRadius )
        {
          neighbors.erase( neighbor );
        }
      }
      return neighbors;
    }

};


class CenterOfMassForce : public NearestNeighborForce<CenterOfMassForce>
{

public:

    explicit CenterOfMassForce ( float radius ) : NearestNeighborForce( radius )
    {
    };

    void actOnBoid ( Boid& boid ) override;

};


class RepulsiveForce : public NearestNeighborForce<RepulsiveForce>
{

public:

    explicit RepulsiveForce ( float radius ) : NearestNeighborForce( radius )
    {
    };

    void actOnBoid ( Boid& boid ) override;
};


class DirectionalForce : public NearestNeighborForce<DirectionalForce>
{

public:

    explicit DirectionalForce ( float radius ) : NearestNeighborForce( radius )
    {
    };

    void actOnBoid ( Boid& boid ) override;
};