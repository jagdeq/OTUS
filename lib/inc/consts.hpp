#pragma once

#include <string>
#include <unordered_set>

namespace bayan {
const std::unordered_set<std::string> g_allowedHash{"md5, crc16, crc32, sha-1, sha-2, sha-256"};
}
