#include "chess.h"
#include "figures.h"
#include "gc.h"

void display() {
  char **blackblock = reverse(whiteSquare);
  char **join_square = join(blackblock, whiteSquare);
  interpreter(join_square);
  garbageCollector();
}
