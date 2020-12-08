#include "allFunc.h"

int strToInt(string str) //число из строки в int(если в строке не цифра возврат -1)
{
    int res = 0;
    const char *sym = str.c_str();
    for(int i = str.length() - 1; i >= 0; --i, ++sym)
    {
        if(*sym == 0)
            break;
        else if(static_cast<int>(*sym) < 48 || static_cast<int>(*sym) > 57)
            return -1;
        int pow = 1;
        for(int k = 0; k < i; ++k)
            pow *= 10;
        res += (static_cast<int>(*sym) - 48) * pow;
    }
    return res;
}
string getDayInMoth(string year, string moth) // кол-во дней в месяце по году и месяцу в string формате
{
    string maxDay;
    for(int i = 1; i <= strToInt(moth); ++i)
    {
        if(i % 2 == 0)
        {
            maxDay = "30";
            if(i == 2)
            {
                if(strToInt(year) % 4 == 0)
                    maxDay = "29";
                else
                    maxDay = "28";
            }
        }
        else
            maxDay = "31";
    }
    return maxDay;
}
string utf8ToCP866(const char *str) // перекодировка текста из utf-8 в cp866(dos)
{
    string tmp = "";
    for(const char *i = str; *i; ++i)
    {
        unsigned tm = static_cast<unsigned>(static_cast<unsigned char>(*i));
        if(tm >= 32 && tm < 127)
            tm = static_cast<char>(tm);
        else if(tm == 208)
        {
            ++i;
            tm = static_cast<unsigned>(static_cast<unsigned char>(*i));
            if(tm >= 144 && tm <= 191)
                tm -= 16;
            else if(tm == 129)
                tm = 240; //ё
        }
        else if(tm == 209)
        {
            ++i;
            tm = static_cast<unsigned>(static_cast<unsigned char>(*i));
            if(tm>= 128 && tm <= 143)
                tm += 96;
            else if(tm == 145)
                tm = 241;//Ё
        }
        else if(tm == 226) // символ № 3 байта
        {
            i += 2;
            tm = static_cast<unsigned>(static_cast<unsigned char>(*i));
            if(tm == 150)
                tm = 252;//№
        }
        tmp += tm;
    }
    return tmp;
}
string Cp866ToUtf8(const char *str) // перекодировка текста из cp866(dos) в utf-8
{
    string tmp = "";
    for(const char *i = str; *i; ++i)
    {
        unsigned tm = static_cast<unsigned>(static_cast<unsigned char>(*i));
        if(tm >= 32 && tm < 127)
            tm = static_cast<char>(tm);
        else if(tm >= 128 && tm <= 175)
        {
            tmp += static_cast<char>(208);
            tm += 16;
        }
        else if(tm>= 224 && tm <= 239)
        {
            tmp += static_cast<char>(209);
            tm -= 96;
        }
        else if(tm == 240)//Ё
        {
            tmp += static_cast<char>(208);
            tm = 129;
        }
        else if(tm == 241) //ё
        {
            tmp += static_cast<char>(209);
            tm = 145;
        }
        else if(tm == 252) // №
        {
            tmp += static_cast<char>(226);
            tmp += static_cast<char>(132);
            tm = 150;
        }
        tmp += tm;
    }
    return tmp;
}

string utf8ToWin1251(const char *str)
{
    string tmp = "";
    for(const char *i = str; *i; ++i)
    {
        unsigned tm = static_cast<unsigned>(static_cast<unsigned char>(*i));
        if(tm >= 32 && tm < 127)
            tm = static_cast<char>(tm);
        else if(tm == 208)
        {
            ++i;
            tm = static_cast<unsigned>(static_cast<unsigned char>(*i));
            if(tm >= 144 && tm <= 191)
                tm += 48;
            else if(tm == 129)
                tm = 168; //Ё
        }
        else if(tm == 209)
        {
            ++i;
            tm = static_cast<unsigned>(static_cast<unsigned char>(*i));
            if(tm>= 128 && tm <= 143)
                tm += 112;
            else if(tm == 145)
                tm = 184;//ё
        }
        else if(tm == 226) // символ № 3 байта
        {
            i += 2;
            tm = static_cast<unsigned>(static_cast<unsigned char>(*i));
            if(tm == 150)
                tm = 185;//№
        }
        tmp += tm;
    }
    return tmp;
}

string win1251ToUtf8(const char *str)
{
    string tmp = "";
    for(const char *i = str; *i; ++i)
    {
        unsigned tm = static_cast<unsigned>(static_cast<unsigned char>(*i));
        if(tm >= 32 && tm < 127)
            tm = static_cast<char>(tm);
        else if(tm >= 192 && tm <= 239)
        {
            tmp += static_cast<char>(208);
            tm -= 48;
        }
        else if(tm >= 240 && tm <= 255)
        {
            tmp += static_cast<char>(209);
            tm -= 112;
        }
        else if(tm == 168)//Ё
        {
            tmp += static_cast<char>(208);
            tm = 129;
        }
        else if(tm == 184) //ё
        {
            tmp += static_cast<char>(209);
            tm = 145;
        }
        else if(tm == 185) // №
        {
            tmp += static_cast<char>(226);
            tmp += static_cast<char>(132);
            tm = 150;
        }
        tmp += tm;
    }
    return tmp;
}

string uppercaseText(const char *str)
{
    string tmp = "";
    for(const char *i = str; *i; ++i)
    {
        unsigned tm = static_cast<unsigned>(static_cast<unsigned char>(*i));
        if(tm >= 97 && tm <= 122)
            tm -= 32;
        tmp += tm;
    }
    return tmp;
}
