/**
 * Copyright 2025 Suryansh Singh
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      https://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * ------------------------------------------------------------------------------------------------------
 *
 * @path [ROOT]/include/mystic/status/in_place.hpp
 * @file in_place.hpp
 * @brief In place constructor tag for status object.
 *
 * @details
 * This header provides a in_place tag to create object holded by
 * status object in place.
 *
 * @code{.cpp}
 * #include "mystic/status/status_or.hpp"
 * #include "mystic/status/in_place.hpp"
 *
 * // ... somewhere in code
 * mystic::status::StatusOr<SomeObject>
 *     result(mystic::status::in_place, param1, param2);
 *
 * // SomeObject is created directly in the storage of result, and
 * // param1, and param2 are passed to SomeObject's constructor.
 *
 * @endcode
 *
 * @author thedevmystic (Surya)
 * @copyright 2025 Suryansh Singh Apache-2.0 License
 *
 * SPDX-FileCopyrightText: 2025 Suryansh Singh
 * SPDX-License-Identifier: Apache-2.0
 */
#pragma once

#include "mystic/macros/framework_api.hpp"

/**
 * @namespace mystic
 * @brief Top-level namespace.
 */
namespace mystic {

/**
 * @namespace mystic::status
 * @brief Status-specific functions and classes.
 */
namespace status {

/**
 * @brief Struct for in_place tag.
 */
MYSTIC_FRAMEWORK_API
struct in_place_t {};

/**
 * @brief in_place tag.
 */
static constexpr in_place_t in_place{};

} // namespace status
} // namespace mystic

