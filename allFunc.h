#ifndef ALLFUNC_H
#define ALLFUNC_H

#include <string>

using namespace std;

int strToInt(string str);
string getDayInMoth(string year, string moth);
string utf8ToWin1251(const char *str);
string win1251ToUtf8(const char *str);
string utf8ToCP866(const char *str);
string Cp866ToUtf8(const char *str);
string uppercaseText(const char *str);
#endif // ALLFUNC_H
