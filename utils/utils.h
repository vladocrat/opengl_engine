#pragma once

#include "image.h"

#include <string_view>
#include <vector>

namespace Utils
{

//! Writes file contents to the passed string
[[nodiscard]] bool readFile(const std::string_view& path, std::string& shader);

//! Returns image data and writes dimensions info
[[nodiscard]] Image readImage(const std::string_view& path, int32_t desiredChannels = 0);

} //! Utils
