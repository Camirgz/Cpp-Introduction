
#include <iostream>
using namespace std;

// Color Terminal Output Library
// MIT Licensed Library

// There are 6 colors:
//
// blue
// green
// cyan
// red
// magenta
// yellow

// Usage:
// color("red", "Error occured", true);
//       color  text           newLine

void color(string color, string line, bool newLine = false);

bool assertEquals(string resultadoEsperado, string resultadoReal);

bool assertEquals(int resultadoEsperado, int resultadoReal);

bool assertEquals(int resultadoEsperado[], int resultadoReal[], int n);

bool assertContains(string resultadoEsperado, string resultadoReal);
