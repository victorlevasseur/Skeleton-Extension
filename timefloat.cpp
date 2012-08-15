#include "timefloat.h"

#include <cstring>

namespace Sk
{

namespace Anim
{

std::string GetValueStr(ValueStr *val)
{
    return std::string(val->v);
}

void SetValueStr(ValueStr *val, std::string &str)
{
    DestroyValueStr(val);

    //val->s = str.size()+1;
    val->v = new char [str.size()+1];
    strcpy (val->v, str.c_str());
}

void DestroyValueStr(ValueStr *val)
{
    delete[] val->v;
    //val->s = 0;
}

}

}
