#include "gtest/gtest.h"

#include <iostream>
#include <string>

#include "Parser.hpp"

constexpr char monsterSchema[] = R"(
namespace MyGame.Sample;

enum Color:byte { Red = 0, Green, Blue = 2 }

union Equipment { Weapon } // Optionally add more tables.

struct Vec3 {
  x:float;
  y:float;
  z:float;
}

table Monster {
  pos:Vec3;
  mana:short = 150;
  hp:short = 100;
  name:string;
  friendly:bool = false (deprecated);
  inventory:[ubyte];
  color:Color = Blue;
  weapons:[Weapon];
  equipped:Equipment;
  path:[Vec3];
}

table Weapon {
  name:string;
  damage:short;
}

root_type Monster;
)";

constexpr char referenceJson[] = R"({
  "pos": {
    "x": 1.0,
    "y": 2.0,
    "z": 3.0
  },
  "mana": 150,
  "hp": 300,
  "name": "Orc",
  "inventory": [
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    7,
    8,
    9
  ],
  "color": "Red",
  "weapons": [
    {
      "name": "Sword",
      "damage": 3
    },
    {
      "name": "Axe",
      "damage": 5
    }
  ],
  "equipped_type": "Weapon",
  "equipped": {
    "name": "Axe",
    "damage": 5
  }
}
)";

TEST(Parser, parse_validJson_successful)
{
    testing::internal::CaptureStdout();

    Parser parser;
    parser.parseFile(monsterSchema);
    auto bin = parser.parseJsonToBin(referenceJson);
    auto json = parser.parseBinToJson(bin.c_str());

    ASSERT_EQ(0, json.compare(referenceJson));
}
