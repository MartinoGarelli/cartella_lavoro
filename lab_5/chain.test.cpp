#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "chain.hpp"



  TEST_CASE("Test chain") {
    SUBCASE("Test no allungamento"){
    PPState p1{2., 1., 0.,};
    PPState p2{1., 3., 0.,};                    //massa, posizione (x), velocità
    Hooke h1{42., 2.};                          //costante, lunghezza riposo
    CHECK(h1(p1, p2) == doctest::Approx(0));
  }
  SUBCASE("Test forza attrattiva"){
    PPState p1{2., 6., 1.,};
    PPState p2{1., 2., 2.,};
    Hooke h1{42., 2.};
    CHECK(h1(p1, p2) == doctest::Approx(84));
  }
    SUBCASE("Test forza attrattiva"){
    PPState p1{2., 6., 1.,};
    PPState p2{1., 2., 2.,};
    Hooke h1{42., 5.};
    CHECK(h1(p1, p2) == doctest::Approx(-42));
  }
    SUBCASE("Test evolve con solo 2 punti"){
      Chain c{Hooke{0.1, 2.}};
    c.push_back({1., 0., 0.});
    c.push_back({1., 4., 0.});
    const auto state_i = c.state();
    c.evolve(1.0);
    const auto state_f = c.state();
  }
  SUBCASE("Test evolve"){
  Chain c{Hooke{0.1, 2.}};
c.push_back({1., 0., 0.5});
c.push_back({1., 2., 0.});
c.push_back({1., 4., 0.});
const auto state_i = c.state();
c.evolve(1.0);
c.evolve(1.0);
const auto state_f = c.state();
  }
  }