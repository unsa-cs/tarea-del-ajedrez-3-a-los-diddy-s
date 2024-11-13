#include "chess.h"
#include "figures.h"
#include "gc.h"

void display() {
  char **blackKnight = reverse(knight);
  interpreter(blackKnight);
  garbageCollector();
}
