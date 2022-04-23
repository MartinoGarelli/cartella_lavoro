#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Mchain.hpp"


//forza attrattiva negativa
//forza repulsiva negativa

  TEST_CASE("Test Hooke") {
    SUBCASE("Test no allungamento"){
    punti p1{2., 1., 0.,};
    punti p2{1., 3., 0.,};                    //massa, posizione (x), velocità
    Hooke h1{42., 2.};                          //costante, lunghezza riposo
    CHECK(h1(p1, p2) == doctest::Approx(0));
  }
  SUBCASE("Test forza attrattiva"){
    punti p1{2., 6., 1.,};
    punti p2{1., 2., 2.,};
    Hooke h1{42., 2.};
    CHECK(h1(p1, p2) == doctest::Approx(-84));
  }
    SUBCASE("Test forza repulsiva"){
    punti p1{2., 6., 1.,};
    punti p2{1., 2., 2.,};
    Hooke h1{42., 5.};
    CHECK(h1(p1, p2) == doctest::Approx(42));
  }
   SUBCASE("Test forza repulsiva piccola"){
    Hooke h1{1., 0.02};
    punti p1{1., 0.00, 0.,};
    punti p2{1., 0.01, 0.,};
    
    CHECK(h1(p1, p2) == doctest::Approx(0.01));
  }
  SUBCASE("Test forza attrattiva piccola"){
    Hooke h1{1., 0.01};
    punti p1{1., 0.00, 0.,};
    punti p2{1., 0.02, 0.,};
    
    CHECK(h1(p1, p2) == doctest::Approx(-0.01));
  }
  
  }
  TEST_CASE ("Test chain") {
    SUBCASE("Test evoluzione con solo 2 punti, senza spostamento"){
      Chain c{Hooke{0.1, 2.}};
    c.buttadentro({1., 0., 0.});
    c.buttadentro({1., 2., 0.}); //uguale distanza e lunghezza a riposo
    const auto stato_i = c.stato();
    c.evoluzione(0.1);
    const auto stato_f = c.stato();
    //check...
    }
  SUBCASE("Test evoluzione"){
  Chain c{Hooke{0.1, 2.}};
c.buttadentro({1., 0., 0.5});
c.buttadentro({1., 2., 0.});
c.buttadentro({1., 4., 0.});
const auto stato_i = c.stato();
c.evoluzione(1.0);
c.evoluzione(1.0);
const auto stato_f = c.stato();
//check...
  }

   SUBCASE("Test evoluzione 2"){
  Chain c{Hooke{1., 0.01}};
c.buttadentro({0.05, 0.0, 0.});
c.buttadentro({0.05, 0.02, 0.});
c.buttadentro({0.05, 0.04, 0.});
const auto stato_i = c.stato();
c.evoluzione(1.0);
c.evoluzione(1.0);
const auto stato_f = c.stato();
//check...
  }
  }