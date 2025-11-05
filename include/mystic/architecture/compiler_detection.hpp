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
 * @path [ROOT]/include/mystic/architecture/compiler_detection.hpp
 * @file compiler_detection.hpp
 * @brief Defines compiler detection macros & runtime logic.
 *
 * @details
 * This header provides compiler detection macros and runtime detection,
 * for cross compiler portable code. There are many compiler out
 * of which 3 are major usage share holders, i.e., ΜSVC, GCC, and Clang.
 * Two major GPU compilers are either based on LLVM/Clang (HIPCC) or
 * GCC (NVCC).
 * 
 * This header file provides,   
 * 1. Compiler detection macros.
 *
 * @code {.cpp}
 * // Example
 * #include "mystic/architecture/compiler_detection.hpp"
 * 
 * // For MSVC
 * #if (MYSTIC_ARCH_COMPILER == MYSTIC_ARCH_COMPILER_MSVC)
 * #define SOME_FORCEINLINE_MACRO __forceinline
 *
 * // For Clang/GCC
 * #elif (MYSTIC_ARCH_COMPILER == MYSTIC_ARCH_COMPILER_GCC)
 *       || (MYSTIC_ARCH_COMPILER == MYSTIC_ARCH_COMPILER_CLANG)
 * #define SOME_FORCEINLINE_MACRO __attribute__((always_inline))
 * 
 * // For other compilers
 * #else
 * #define SOME_FORCEINLINE_MACRO inline
  * #endif
 * @endcode
 *
 * @author TheDevMystic (Surya)
 * @copyright 2025 Suryansh Singh Apache-2.0 License
 *
 * SPDX-FileCopyrightText: 2025 Suryansh Singh
 * SPDX-License-Identifier: Apache-2.0
 */
#pragma once

#include <string>

/* =============================================
    Compiler Tags
   --------------------------------------------- */

/**
 * @macro MYSTIC_COMPILER_HIPCC
 * @brief Tag for HIP C++ Compiler.
 */
#define MYSTIC_COMPILER_HIPCC 0

/**
 * @macro MYSTIC_COMPILER_NVCC
 * @brief Tag for Nvidia C++ Compiler.
 */
#define MYSTIC_COMPILER_NVCC 1

/**
 * @macro MYSTIC_COMPILER_ICC
 * @brief Tag for Intel C++ Compiler.
 */
#define MYSTIC_COMPILER_ICC 2

/**
 * @macro MYSTIC_COMPILER_MSVC
 * @brief Tag for Microsoft/Visual C++ Compiler.
 */
#define MYSTIC_COMPILER_MSVC 3

/**
 * @macro MYSTIC_COMPILER_CLANG
 * @brief Tag for LLVM/Clang C++ Compiler.
 */
#define MYSTIC_COMPILER_CLANG 4

/**
 * @macro MYSTIC_COMPILER_GCC
 * @brief Tag for GNU C++ Compiler.
 */
#define MYSTIC_COMPILER_GCC 5

/**
 * @macro MYSTIC_COMPILER_UNKNOWN
 * @brief Tag for Unknown C++ Compiler.
 */
#define MYSTIC_COMPILER_UNKNOWN 6

/* =============================================
    Detection Logic
   --------------------------------------------- */

/**
 * @macro MYSTIC_COMPILER
 * @brief Tag for C++ compiler identification.
 */
#if defined(__HIP__) || defined(__HIPCC__) /* using HIP C++ compiler */
/**
 * @brief Set compiler tag to HIPCC.
 */
# define MYSTIC_COMPILER MYSTIC_COMPILER_HIPCC

#elif defined(__NVCC__) || defined(__CUDACC__) /* using Nvidia C++ compiler */
/**
 * @brief Set compiler tag to NVCC.
 */
# define MYSTIC_COMPILER MYSTIC_COMPILER_NVCC

#elif defined(__INTEL_COMPILER) || defined(__ICC) || defined(__INTEL_LLVM_COMPILER) /* using Intel C++ compiler */
/**
 * @brief Set compiler tag to ICC.
 */
# define MYSTIC_COMPILER MYSTIC_COMPILER_ICC

#elif defined(_MSVC_VER)  /* using Microsoft/Visual C++ compiler */
/**
 * @brief Set compiler tag MSVC.
 */
# define MYSTIC_COMPILER MYSTIC_COMPILER_MSVC

#elif defined(__clang__) /* using LLVM/Clang C++ compiler */
/**
 * @brief Set compiler tag to Clang.
 */
# define MYSTIC_COMPILER MYSTIC_COMPILER_CLANG

#elif defined(__GNUC__) /* using GNU C++ compiler */
/**
 * @brief Set compiler tag to GCC.
 */
# define MYSTIC_COMPILER MYSTIC_COMPILER_GCC

#else /* if compiler is unknown */
/**
 * @brief Set compiler to unknown.
 */
# define MYSTIC_COMPILER MYSTIC_COMPILER_UNKMOWN

#endif // defined(__HIP__) || defined(__HIPCC__)

/**
 * @brief If compiler is unknown, then stop compilation.
 * Only way to restrict it is to define MYSTIC_ALLOW_UNKNOWN_COMPILER.
 */
#if (!defined(MYSTIC_ALLOW_UNKNOWN_COMPILER) && \
    (MYSTIC_COMPILER == MYSTIC_COMPILER_UNKNOWN))
/**
 * @brief Stop compilation.
 */
# error "[Mystic Framework] - Compiler - The compiler currently being used is not supported, consider using supported compilers."

#endif

/* =============================================
    Compiler Name Detection
   --------------------------------------------- */

/**
 * @macro MYSTIC_COMPILER_NAME
 * @brief Defines compiler name as string using tags.
 *
 * @macro MYSTIC_COMPILER_VERSION
 * @brief Defines compiler version as integer.
 *
 * @macro MYSTIC_COMPILER_VERSION_MAJOR
 * @brief Defines compiler major version as integer.
 *
 * @macro MYSTIC_COMPILER_VERSION_MINOR
 * @brief Defines compiler minor version as integer.
 *
 * @macro MYSTIC_COMPILER_VERSION_PATCH
 * @brief Defines compiler patch version as integer.
 *
 * @macro MYSTIC_COMPILER_VERSION_STR
 * @brief Defines compiler version as string.
 *
 * @macro MYSTIC_COMPILER_VERSION_MAJOR_STR
 * @brief Defines compiler major version as string.
 *
 * @macro MYSTIC_COMPILER_VERSION_MINOR_STR
 * @brief Defines compiler minor version as string.
 *
 * @macro MYSTIC_COMPILER_VERSION_PATCH_STR
 * @brief Defines compiler patch version as string.
 */
#if (MYSTIC_COMPILER == MYSTIC_COMPILER_HIPCC)
/**
 * @brief Set compiler name to HIPCC.
 */
# define MYSTIC_COMPILER_NAME "HIPCC"

#elif (MYSTIC_COMPILER == MYSTIC_COMPILER_NVCC)
/**
 * @brief Set compiler name to NVCC.
 */
# define MYSTIC_COMPILER_NAME "NVCC"

#elif (MYSTIC_COMPILER == MYSTIC_COMPILER_ICC)
/**
 * @brief Set compiler name to ICC.
 */
# define MYSTIC_COMPILER_NAME "ICC"

#elif (MYSTIC_COMPILER == MYSTIC_COMPILER_MSVC)
/**
 * @brief Set compiler name to MSVC.
 */
# define MYSTIC_COMPILER_NAME "MSVC"

#elif (MYSTIC_COMPILER == MYSTIC_COMPILER_CLANG)
/**
 * @brief Set compiler name to Clang.
 */
# define MYSTIC_COMPILER_NAME "CLANG"

#elif (MYSTIC_COMPILER == MYSTIC_COMPILER_GCC)
/**
 * @brief Set compiler name to GCC.
 */
# define MYSTIC_COMPILER_NAME "GCC"

#else /* if unknown */
/**
 * @brief Set compiler name to UNKNOWN.
 */
# define MYSTIC_COMPILER_NAME "UNKNOWN"

#endif // (MYSTIC_COMPILER == MYSTIC_COMPILER_HIPCC)

/**
 * @namespace mystic::architecture::compiler
 * @brief Runtime compiler detection logic.
 *
 * Contains runtime logic for compiler detection and checking.
 */
namespace mystic::architecture::compiler {

/**
 * @brief 
std::string GetCompilerName() {
    return std::string(MYSTIC_COMPILER_NAME);
}

} // namespace mystic::architecture::compiler
