#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "timelib.h"
#define H 3600
#define O 100
#define G 2147483647
#define U 5
#define Y 10
int main() {
  unsigned int mini = G;
  unsigned int maxi = 0;
  struct persoane {
    char nume[Y];
    char timez[U];
    int K;
    TDateTimeTZ dtd[O];
    int dur[O];
    unsigned int valab[O];
    int okay;
    int nrpoz;
  };

  struct persoane p[O];
  TTimezone t[O];

  int T = 0;
  scanf("%d", &T);
  for (int i = 0; i < T; i++) {
    scanf("%s", t[i].name);
    scanf("%c", &t[i].utc_hour_difference);
  }
  int P = 0;
  scanf("%d", &P);
  for (int i = 0; i < P; i++) {
    scanf("%s", p[i].nume);
    scanf("%s", p[i].timez);
    scanf("%d", &p[i].K);
    for (int j = 0; j < p[i].K; j++) {
      scanf("%d", &p[i].dtd[j].date.year);
      scanf("%c", &p[i].dtd[j].date.month);
      scanf("%c", &p[i].dtd[j].date.day);
      scanf("%c", &p[i].dtd[j].time.hour);
      scanf("%d", p[i].dur);
    }
  }
  int F = 0;
  scanf("%d", &F);
  int durata = 0;
  scanf("%d", &durata);
  for (int i = 0; i < P; i++) {
    printf("ok!\n");
    for (int j = 0; j < p[i].K; j++) {
      for (int k = 0; k < T; k++) {
        if (strcmp(p[i].timez, t[k].name) == 0) {
          p[i].dtd[j].tz->utc_hour_difference = t[k].utc_hour_difference;
        }
      }
      p[i].valab[j] = convertDateTimeTZToUnixTimestamp(p[i].dtd[j]);

      printf("%d\n", p[i].valab[j]);
      if (p[i].valab[j] <= mini) {
        mini = p[i].valab[j];
      }
      if (p[i].valab[j] >= maxi) {
        maxi = p[i].valab[j];
      }
    }
  }
  int nrpersv = 0;
  for (unsigned int x = mini; x <= maxi; x += H) {
    nrpersv = 0;
    for (int i = 0; i < P; i++) {
      p[i].okay = 0;
    }
    for (int i = 0; i < P; i++) {
      for (int j = 0; j < p[i].K; j++) {
        if (x == p[i].valab[j] && p[i].dur[j] <= durata) {
          if (p[i].okay == 0) {
            nrpersv++;
            p[i].nrpoz = j;
          }
          p[i].okay = 1;
        }
      }
    }
    if (nrpersv >= F) {
      for (int i = 0; i < P; i++) {
        if (p[i].okay == 1) {
          printf("%s: ", p[i].nume);
          printDateTimeTZ(p[i].dtd[p[i].nrpoz]);
        } else {
          printf("%s: invalid\n", p[i].nume);
        }
      }
      x = maxi + 1;
    }
    if (x == maxi && nrpersv < F) {
      printf("imposibil\n");
    }
  }
  return 0;
}
