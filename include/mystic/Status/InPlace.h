/**
 * @path [ROOT]/Include/MysticCore/Status/InPlace.h
 * @file InPlace.h
 * @brief in_place struct and tag for inplace status construction.
 */

/**
 * As framework don't use exceptions, it relies on status code and status error handling.
 * This file defines inplace struct and tag.
 *
 * This file provides in_place struct and tag,
 *  - Mystic::Status::in_place_t  - In place struct.
 *  - Mystic::Status::in_place    - In place tag.
 */
#pragma once

// For framework api
#include "MysticCore/Architecture/FrameworkAPI.h"

namespace Mystic::Status {

/**
 * @struct in_place_t
 * @brief Struct for in place construction.
 */
MYSTIC_INTERNAL_ARCH_FRAMEWORK_API
struct in_place_t {};

/**
 * @brief In place construction tag.
 */
inline constexpr in_place_t in_place{};

} // namespace Mystic::Status

