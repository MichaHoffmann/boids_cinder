#include "Forces/Local/SpatialHash.hpp"
#include "Boids/Boid.hpp"


class SpatialHash::SpatialHashImpl
{

public:

    typedef std::pair<int, int> cell;

    int cellSize{};

    float interactionRadius{};

    std::map<cell, std::vector<Boid *>> grid;


    SpatialHashImpl ( float interactionRadius, int cellSize ) :
      grid(),
      interactionRadius( interactionRadius ),
      cellSize( cellSize )
    {
    }


    ~SpatialHashImpl () = default;


    std::vector<cell> getCells ( const utility::vec_t &pos )
    {
      int x_max = ((int) ( pos.x + interactionRadius ) / cellSize ) * cellSize;
      int x_min = ((int) ( pos.x - interactionRadius ) / cellSize ) * cellSize;
      int y_max = ((int) ( pos.y + interactionRadius ) / cellSize ) * cellSize;
      int y_min = ((int) ( pos.y - interactionRadius ) / cellSize ) * cellSize;

      std::vector<cell> cells{};

      for ( int i = x_min; i <= x_max; i += cellSize )
      {
        for ( int j = y_min; j <= y_max; j += cellSize )
        {
          cells.emplace_back( i, j );
        }
      }
      return cells;
    }
};


SpatialHash::SpatialHash ( float interactionRadius, int cellSize ) :
  pImpl( new SpatialHash::SpatialHashImpl( interactionRadius, cellSize ))
{
}


SpatialHash::~SpatialHash () = default;


void SpatialHash::clear ()
{
  pImpl->grid.clear();
}


void SpatialHash::insert ( Boid &boid )
{
  for ( const auto& cell: pImpl->getCells( boid.getPosition()))
  {
    pImpl->grid[ cell ].push_back( &boid );
  }
}


std::set<Boid *> SpatialHash::getNeighbors ( Boid &boid )
{
  std::set<Boid *> neighbors{};

  for ( const auto &cell: pImpl->getCells( boid.getPosition()))
  {
    std::copy( pImpl->grid[ cell ].begin(),
               pImpl->grid[ cell ].end(),
               std::inserter( neighbors, neighbors.end()));
  }

  neighbors.erase( &boid );

  return neighbors;
}


