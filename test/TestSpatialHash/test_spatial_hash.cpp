#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include "Forces/Local/SpatialHash.hpp"
#include "Forces/Local/SpatialHash.cpp"


TEST_CASE( " Spatial Hash 'getNeighbors'" ) {

  SpatialHash neighborhood{ 1.f, 10 };
  Boid p1{ utility::vec_t{ 5.f, 5.f }};
  neighborhood.insert ( p1 );

  SECTION( " No neighbors found, because different boxes " ) {
    Boid p2{ utility::vec_t{ 15.f, 15.f }};
    neighborhood.insert ( p2 );
    auto neighbors = neighborhood.getNeighbors ( p1 );
    REQUIRE( neighbors.find ( &p2 ) == neighbors.end ());
  }

  SECTION( " neighbors found " ) {
    Boid p2{ utility::vec_t{ 6.f, 6.f }};
    neighborhood.insert ( p2 );
    auto neighbors = neighborhood.getNeighbors ( p1 );
    REQUIRE( neighbors.find ( &p2 ) != neighbors.end ());
  }

  SECTION( " neighbors of p do not include p itself " ) {
    auto neighbors = neighborhood.getNeighbors ( p1 );
    REQUIRE( neighbors.empty ());
  }

  SECTION( " multiple neighbors found " ) {
    Boid p2{ utility::vec_t{ 9.f, 9.f }};
    Boid p3{ utility::vec_t{ 1.f, 1.f }};
    neighborhood.insert ( p2 );
    neighborhood.insert ( p3 );
    auto neighbors = neighborhood.getNeighbors ( p1 );

    REQUIRE( neighbors.size () == 2 );
    REQUIRE( neighbors.find ( &p2 ) != neighbors.end ());
    REQUIRE( neighbors.find ( &p3 ) != neighbors.end ());
  }

  SECTION( " on edge of box " ) {
    Boid p2{ utility::vec_t ( 10.5f, 10.5f ) };
    neighborhood.insert ( p2 );

    auto neighbors = neighborhood.getNeighbors ( p1 );
    REQUIRE( neighbors.find ( &p2 ) != neighbors.end ());
  }
}

TEST_CASE( "Spatial Hash 'clear' " ) {
  SECTION( " clear empties hash " ) {
    SpatialHash neighborhood{ 1.f, 10 };
    Boid p1{ utility::vec_t{ 9.f, 9.f }};
    Boid p2{ utility::vec_t{ 1.f, 1.f }};
    neighborhood.insert ( p1 );
    neighborhood.insert ( p2 );

    REQUIRE( not neighborhood.getNeighbors ( p1 ).empty ());

    neighborhood.clear ();

    REQUIRE( neighborhood.getNeighbors ( p1 ).empty ());
  }
}

TEST_CASE( " Spatial Hash 'private methods' " ) {
  SpatialHash::SpatialHashImpl impl{ 2.f, 10 };

  SECTION( " completely in one cell " ) {
    auto cells = impl.getCells ( utility::vec_t{ 5.f, 5.f } );

    std::vector<std::pair<int, int>> expected{ std::make_pair ( 0, 0 ) };
    REQUIRE( expected == cells );

  }

  SECTION( " overlapp on intersection of 4 cells " ) {
    auto cells = impl.getCells ( utility::vec_t{ 10.f, 10.f } );

    std::vector<std::pair<int, int>> expected{
      std::make_pair ( 0, 0 ),
      std::make_pair ( 10, 0 ),
      std::make_pair ( 0, 10 ),
      std::make_pair ( 10, 10 ) };

    std::sort ( std::begin ( expected ), std::end ( expected ));
    std::sort ( std::begin ( cells ), std::end ( cells ));
    REQUIRE( expected == cells );
  }


}
