#ifndef NOON_UTILITIES_H
#define NOON_UTILITIES_H

#include <iostream>
#include "Settings.h"

#define debug(str) if (Settings::instance().verbose()) std::cout <<str<<std::endl;

#endif
