#include "chess.h"
#include "figures.h"
#include "gc.h"

void display(){
  char** blackSquare = flipV(whiteSquare);
  interpreter(blackSquare);
  garbageCollector();
}
