#ifndef LIB_H
#define LIB_H

#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <typeinfo>
#include <vector>
#include <exception>
#include <list>
#include <map>

#define DEBUG 1

#ifdef DEBUG
# define DEBUG_PRINT(x) printf x
#else
# define DEBUG_PRINT(x) do {} while (0)
#endif

#endif

