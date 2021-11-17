
#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "tsp.hpp"

Localizacion prueba;

TEST_CASE("probar tamaño inicializacion", "[Localizacion]"){

  prueba.initializer(3);

  REQUIRE(prueba.X.size() == 3 );

  REQUIRE(prueba.Y.size() == 3);
   
  REQUIRE(prueba.oldpath.size() == 4);

  REQUIRE(prueba.newpath.size() == 4);

}


