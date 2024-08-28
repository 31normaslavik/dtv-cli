#pragma once
#include <string>

namespace dtv {

std::string getName();
std::string getVersion();
unsigned getVersionMajor();
unsigned getVersionMinor();
unsigned getVersionPatch();
unsigned getVersionTweak();

} // namespace dtv
