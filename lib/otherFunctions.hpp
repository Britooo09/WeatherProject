#pragma once
#include <cstdint>
#include <string>

void initialConfigRead();

std::string unixConversion(std::uint32_t timestamp, bool isFullDate);
std::string timezoneConversion(int offset);
