#include <arpa/inet.h>

#include "Environment.hpp"

int EnvironmentChecks::dummyVariable = runtimeMethod();

bool EnvironmentChecks::isBigEndian = false;

bool EnvironmentChecks::getIsBigEndian()
{
    return isBigEndian;
}

int EnvironmentChecks::runtimeMethod()
{
    /**
     *  This makes me sad :(
     *  Its a shame that we have to do stuff like this in "modern" programming languages.
     */
    if(htonl(47) == 47)
    {
        EnvironmentChecks::isBigEndian = true;
    }
    else
    {
        EnvironmentChecks::isBigEndian = false;
    }

    return 0;
}
