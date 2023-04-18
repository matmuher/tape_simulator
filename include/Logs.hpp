#pragma once

#include <iostream>
#include <string>
#include <fstream>

namespace ts
{
    std::ostream& log(const std::string& msg = "", const std::string filename = "log.txt");
    std::ostream& err();
}