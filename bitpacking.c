#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "timelib.h"
#define J 600
#define C 5
#define A 0x1F
#define B 0xF
#define D 0x3F
#define G 1970
#define L 9

int main() {
  char *lunile[] = {"",         "ianuarie",   "februarie", "martie",
                    "aprilie",  "mai",        "iunie",     "iulie",
                    "august",   "septembrie", "octombrie", "noiembrie",
                    "decembrie"};
  char lol = 0;
  int N = 0;
  int numb = 0;

  struct task7 {
    unsigned char ziua;
    unsigned char luna;
    unsigned int an;
  };

  struct task7 v[J];
  scanf("%c", &lol);
  if (strcmp(&lol, "7") == 0) {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
      scanf("%d", &numb);
      v[i].an = G;
      v[i].ziua = numb & A;
      v[i].luna = (numb >> C) & B;
      v[i].an += (numb >> L) & D;
    }
    for (int i = 0; i < N - 1; i++) {
      for (int j = 0; j < N - i - 1; j++) {
        if (v[j + 1].an < v[j].an) {
          struct task7 aux = v[j];
          v[j] = v[j + 1];
          v[j + 1] = aux;
        }
      }
    }
    for (int i = 0; i < N - 1; i++) {
      for (int j = 0; j < N - i - 1; j++) {
        if (v[j + 1].luna < v[j].luna && v[j + 1].an == v[j].an) {
          struct task7 aux = v[j];
          v[j] = v[j + 1];
          v[j + 1] = aux;
        }
      }
    }
    for (int i = 0; i < N - 1; i++) {
      for (int j = 0; j < N - i - 1; j++) {
        if (v[j + 1].ziua < v[j].ziua && v[j + 1].luna == v[j].luna &&
            v[j + 1].an == v[j].an) {
          struct task7 aux = v[j];
          v[j] = v[j + 1];
          v[j + 1] = aux;
        }
      }
    }
    for (int i = 0; i < N; i++) {
      printf("%d %s %d\n", v[i].ziua, lunile[v[i].luna], v[i].an);
    }
  }
  if (strcmp(&lol, "8") == 0) {
    int okeiut = 0;
    okeiut++;
  }
  return 0;
}
