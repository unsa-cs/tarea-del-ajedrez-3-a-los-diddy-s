#include "chess.h"
#include "gc.h"
#include <stdio.h>
#include <stdlib.h>

char **allocateMemory(int rows, size_t cols) {
  char **newFig;
  memoryAlloc((void **)&newFig, sizeof(char *) * (rows + 1));
  fprintf(stderr, "Puntero del allocate Memory: %p\n", newFig);
  for (int i = 0; i < rows; i++)
    memoryAlloc((void **)&newFig[i], sizeof(char) * (cols + 1));
  return newFig;
}

void unlinkMemory(char **fig) {
  countMemoryEntries();
  for (int i = 0; fig[i]; i++)
    unregisterPointer((void **)&fig[i]);
  countMemoryEntries();
  unregisterPointer((void **)&fig);
  countMemoryEntries();
}

char **reverse(char **fig) {
  int rows = 0;
  while (fig[++rows])
    ;

  int cols = 0;
  while (fig[0][++cols])
    ;

  char **newFig = allocateMemory(rows, cols);

  for (int i = 0; fig[i]; i++) {
    for (int j = 0; fig[0][j]; j++)
      newFig[i][j] = fig[i][j];
    newFig[i][cols] = 0;
  }
  newFig[rows] = 0;
  unlinkMemory(newFig);
  fprintf(stderr, "[DEBUG] figura copiada en %p.\n", newFig);
  return newFig;
}

char **flipV(char **fig) {
  fprintf(stderr, "Direccion de memoria fig original: %p\n", &fig);
  fig = allocateMemory(1, 0);

  unlinkMemory(fig);
  return fig;
}
