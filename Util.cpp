//
// Created by yiniao on 2015/5/6.
//

#include "Util.h"

namespace util{

string ChangeSuffix(string name, string suffix)
{
    name.erase(name.rfind('.') + 1);
    name += suffix;
    return name;
}

}