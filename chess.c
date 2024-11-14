#include "chess.h"
#include "gc.h"
#include <stdio.h>
#include <stdlib.h>

void allocateMemory(int rows, size_t cols, char ***newFig) {
  memoryAlloc((void **)newFig, sizeof(char *) * (rows + 1));
  fprintf(stderr, "Direccion de memoria de newFig: %p\n", newFig);
  for (int i = 0; i < rows; i++)
    memoryAlloc((void **)&(*newFig)[i], sizeof(char) * (cols + 1));
}

void unlinkMemory(char ***ptrFig) {
  fprintf(stderr, "Direccion de memoria de puntero a desvincular: %p\n",
          &ptrFig);
  countMemoryEntries();
  for (int i = 0; (*ptrFig)[i]; i++)
    unregisterPointer((void **)&(*ptrFig)[i]);
  countMemoryEntries();
  unregisterPointer((void **)ptrFig);
  countMemoryEntries();
}

char **reverse(char **fig) {
  int rows = 0;
  while (fig[++rows])
    ;

  int cols = 0;
  while (fig[0][++cols])
    ;

  char **newFig;
  allocateMemory(rows, cols, &newFig);
  for (int i = 0; fig[i] != NULL; i++) {
    for (int j = 0; fig[i][j] != '\0'; j++) {
      switch (fig[i][j]) {
      case '.':
        newFig[i][j] = '@';
        break;
      case '_':
        newFig[i][j] = '=';
        break;
      case '=':
        newFig[i][j] = '_';
        break;
      case '@':
        newFig[i][j] = '.';
        break;
      default:
        newFig[i][j] = fig[i][j];
      }
    }
    newFig[i][cols] = '\0';
  }
  newFig[rows] = NULL;
  fprintf(stderr, "[DEBUG] figura copiada en %p.\n", newFig);
  unlinkMemory(&newFig);
  return newFig;
}

char **join(char **fig1, char **fig2) {
  int rows = 0;
  while (fig1[rows]) {
    rows++;
  }

  int cols1 = 0;
  while (fig1[0][cols1]) {
    cols1++;
  }

  int cols2 = 0;
  while (fig2[0][cols2]) {
    cols2++;
  }

  char **newFig;
  allocateMemory(rows, cols1 + cols2, &newFig);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols1; j++) {
      newFig[i][j] = fig1[i][j];
    }
    for (int j = 0; j < cols2; j++) {
      newFig[i][j + cols1] = fig2[i][j];
    }
    newFig[i][cols1 + cols2] = '\0';
  }
  newFig[rows] = NULL;
  unlinkMemory(&newFig);
  return newFig;
}

char **flipV(char **fig) {
  fprintf(stderr, "Direccion de memoria fig original: %p\n", &fig);
  allocateMemory(1, 0, &fig);
  unlinkMemory(&fig);
  return fig;
}
