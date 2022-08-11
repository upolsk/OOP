#include "menu.h"

using namespace std;

#define NORMAL_MODE
#ifdef NORMAL_MODE

int main()
{
    cout << "Chessboard:\n";
    menu m;
    m.Run();
    return 0;
}
#else
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "chess.h"

TEST_CASE("Creation of Chessboard")
{
chess a;
chess b(5);
chess c("input.txt");

SECTION("CHECKING SIZES OF MATRICES")
{
   CHECK(a.getSize() == 4);
   CHECK(b.getSize() == 5);
   CHECK(c.getSize() == 4);
}

SECTION("GET ELEMENTS")
{
    CHECK(a.getElement(0,0) == 1);
    CHECK(b.getElement(0,0) == 0);
    CHECK(c.getElement(0,0) == 1);
    CHECK(b.getElement(1,3) == 0);
    CHECK(c.getElement(1,1) == 3);
    CHECK(b.getElement(2,1) == 0);
    CHECK(c.getElement(2,2) == 6);
}

SECTION("SETTING ELEMENTS")
{
a.setElement(0, 0, 8);
a.setElement(3, 3, 1);
a.setElement(2, 0, 9);
CHECK(a.getElement(0,0) == 8);
CHECK(a.getElement(3,3) == 1);
CHECK(a.getElement(2,0) == 9);

c.setElement(1,3,7);
c.setElement(3,3,90);
CHECK(c.getElement(1,3) == 7);
CHECK(c.getElement(3,3) == 90);
}

SECTION("SETTING VECTORS")
    {
    a.setVec({2, 3, 5, 3, 1, 6, 8, 5});
    CHECK(a.getElement(0,0) == 2);
    CHECK(a.getElement(3,3) == 5);
    CHECK(a.getElement(1,1) == 5);
    CHECK(a.getElement(2,0) == 1);

    c.setVec({10, 20, 30, 40, 50, 60, 70, 80});
    CHECK(c.getElement(0,0) == 10);
    CHECK(c.getElement(2,0) == 50);
    CHECK(c.getElement(1,3) == 40);
    CHECK(c.getElement(3,1) == 70);
    }
}

TEST_CASE("OPERATIONS FOR TWO MATRICES")
{
    chess a;
    chess b("input.txt");
    chess c(4);

SECTION("ADDITION")
{
    chess s = c.add(a, b);
    CHECK(s.getElement(0,0) == 2);
    CHECK(s.getElement(0,2) == 4);
    CHECK(s.getElement(1,1) == 6);
    CHECK(s.getElement(1,3) == 8);
    CHECK(s.getElement(2,0) == 10);
    CHECK(s.getElement(2,2) == 12);
    CHECK(s.getElement(3,1) == 14);
    CHECK(s.getElement(3,3) == 16);
  }
SECTION("MULTIPLICATION")
{
    chess mul = c.multiply(a, b);
    CHECK(mul.getElement(0,0) == 11);
    CHECK(mul.getElement(0,2) == 14);
    CHECK(mul.getElement(1,1) == 37);
    CHECK(mul.getElement(1,3) == 44);
    CHECK(mul.getElement(2,0) == 35);
    CHECK(mul.getElement(2,2) == 46);
    CHECK(mul.getElement(3,3) == 92);
}
}

TEST_CASE("POSSIBLE ERRORS") {
  chess a;
  chess b(3);
  chess c(4);
  chess d("input2.txt");
  chess e(4);

  SECTION("INVALID INDEX EXCEPTION")
  {
    CHECK_THROWS(a.getElement(-2,1));
    CHECK_THROWS(a.getElement(4,6));

    CHECK_THROWS(b.getElement(-45,-6));
    CHECK_THROWS(b.getElement(3,10));

    CHECK_THROWS(d.getElement(-1,-1));
    CHECK_THROWS(d.getElement(2,2));
  }
  SECTION("INVALID VECTOR EXCEPTION")
  {
    CHECK_THROWS(a.setVec({2, 4, 5}));
    CHECK_THROWS(a.setVec({-2, 9, 15, 12, 4, 54, 6, 64, 67}));

    CHECK_THROWS(b.setVec({2, 2, 8}));
    CHECK_THROWS(b.setVec({1, 10, 7, 2, 4, 5}));


    CHECK_THROWS(d.setVec({1, 4, 5, 6, 7, 8, 8, 8, 8}));
    CHECK_THROWS(d.setVec({1, 2, 3, 4}));

  }
  SECTION("INVALID INDEX EXCEPTION IN SETTING ELEMENTS")
  {
     CHECK_THROWS(a.setElement(5, 5, 39));
     CHECK_THROWS(a.setElement(-3, 0, 45));

     CHECK_THROWS(b.setElement(-4, -5, 9));
     CHECK_THROWS(b.setElement(0, -15, 9));

     CHECK_THROWS(d.setElement(3, 3, 9));
     CHECK_THROWS(d.setElement(4, 1, 2));
  }
  SECTION("DIFFERENT DIMENSION EXCEPTION")
  {

    chess s = c.add(a, e);
    chess mul = c.multiply(a, e);
    chess f(5);
    chess h;
    chess k;
    CHECK_THROWS(h = c.add(a, f));
    CHECK_THROWS(k = c.multiply(e, f));
  }
}
#endif
