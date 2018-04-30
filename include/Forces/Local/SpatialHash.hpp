#pragma once


#include <map>
#include <vector>
#include <set>
#include <memory>

class Boid;


class SpatialHash
{

public:

    SpatialHash ( float interactionRadius, int cellSize );

    ~SpatialHash ();

    void insert ( Boid& );

    void clear ();

    std::set<Boid*> getNeighbors ( Boid& );

    class SpatialHashImpl;

private:

    std::unique_ptr<SpatialHashImpl> pImpl;
};
