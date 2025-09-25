#include "timelib.h"
#include <stdio.h>
#include <stdlib.h>
#define H 3600
#define S 60
#define Y 365
#define M 86400
#define Z 30
#define G 1970
#define C 100

int bisect(unsigned int an) {
  return (an % 4 == 0 && an % C != 0) || an % (C * 4) == 0;
}

TTime convertUnixTimestampToTime(unsigned int timestamp) {
  TTime result;
  timestamp = timestamp % M;
  result.hour = timestamp / H;
  result.min = (timestamp % H) / S;
  result.sec = (timestamp % H) % S;
  return result;
}

TDate convertUnixTimestampToDateWithoutLeapYears(unsigned int timestamp) {
  TDate result;
  result.year = G;
  int luni[] = {0,     Z + 1, Z - 2, Z + 1, Z, Z + 1, Z,
                Z + 1, Z + 1, Z,     Z + 1, Z, Z + 1};
  while (timestamp >= M * Y) {
    result.year++;
    timestamp -= M * Y;
  }
  result.month = 1;
  while (timestamp >= luni[result.month] * M) {
    result.month++;
    timestamp -= luni[result.month - 1] * M;
  }
  result.day = 1;
  while (timestamp >= M) {
    result.day++;
    timestamp -= M;
  }
  return result;
}

TDate convertUnixTimestampToDate(unsigned int timestamp) {
  TDate result;
  result.year = G;
  int luni[] = {0,     Z + 1, Z - 2, Z + 1, Z, Z + 1, Z,
                Z + 1, Z + 1, Z,     Z + 1, Z, Z + 1};
  while (timestamp >= M * Y) {
    result.year++;
    if (bisect(result.year)) {
      timestamp -= ((M * Y) + M);
    } else {
      timestamp -= M * Y;
    }
  }
  if (bisect(result.year)) {
    luni[2]++;
    timestamp += M;
  }
  result.month = 1;
  while (timestamp >= luni[result.month] * M) {
    result.month++;
    timestamp -= luni[result.month - 1] * M;
  }
  result.day = 1;
  while (timestamp >= M) {
    result.day++;
    timestamp -= M;
  }
  return result;
}

TDateTimeTZ convertUnixTimestampToDateTimeTZ(unsigned int timestamp,
                                             TTimezone *timezones,
                                             int timezone_index) {
  TDateTimeTZ result;
  timestamp += timezones[timezone_index].utc_hour_difference * H;
  result.date = convertUnixTimestampToDate(timestamp);
  result.time = convertUnixTimestampToTime(timestamp);
  result.tz = &timezones[timezone_index];
  return result;
}

unsigned int convertDateTimeTZToUnixTimestamp(TDateTimeTZ result) {
  int timp = 0;
  int luni[] = {0,     Z + 1, Z - 2, Z + 1, Z, Z + 1, Z,
                Z + 1, Z + 1, Z,     Z + 1, Z, Z + 1};
  while (result.date.year > G) {
    if (bisect(result.date.year)) {
      timp += (Y + 1) * M;
    } else {
      timp += Y * M;
    }
    result.date.year--;
  }
  while (result.date.month > 1) {
    timp += luni[result.date.month - 1] * M;
    result.date.month--;
  }
  while (result.date.day > 1) {
    timp += M;
    result.date.day--;
  }
  while (result.time.hour > 0) {
    timp += H;
    result.time.hour--;
  }
  while (result.time.min > 0) {
    timp += S;
    result.time.min--;
  }
  while (result.time.sec > 0) {
    timp++;
    result.time.sec--;
  }
  timp -= result.tz->utc_hour_difference * H;
  return timp;
}

void printDateTimeTZ(TDateTimeTZ datetimetz) {
  char *lunile[] = {"",         "ianuarie",   "februarie", "martie",
                    "aprilie",  "mai",        "iunie",     "iulie",
                    "august",   "septembrie", "octombrie", "noiembrie",
                    "decembrie"};
  printf("%02d %s %d, %02d:%02d:%02d %s (UTC%+d)\n", datetimetz.date.day,
         lunile[datetimetz.date.month], datetimetz.date.year,
         datetimetz.time.hour, datetimetz.time.min, datetimetz.time.sec,
         datetimetz.tz->name, datetimetz.tz->utc_hour_difference);
}
