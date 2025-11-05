/**
 * @path [ROOT]/Include/MysticCore/Status/StatusMacros.h
 * @file StatusMacros.h
 * @brief Macros for Status, reducing boilerplate.
 */

/**
 * As framework don't use exceptions, it relies on status code and status error handling.
 * This file defines various macros to reduce boilerplate introduced by Status mechanism.
 *
 * Macros are named with the following convention,
 * 1. Each public macro is prefixed with "MYSTIC".
 * 2. Each private macro is prefixed with "MYSTIC_INTERNAL".
 *
 * This file provides these Status macros,
 * 1. Helpers
 *  - MYSTIC_INTERNAL_RETURN_IF_ERROR(operation)                - Returns if operation is a error (impl).
 *  - MYSTIC_INTERNAL_APPEND_STATUS_IF_ERROR(status, operation) - Appends the status if it was error (impl).
 *  - MYSTIC_INTERNAL_ASSIGN_OR_RETURN(value, operation)        - Assigns value if operation status is ok (impl).
 
 * 2. Public
 *  - MYSTIC_RETURN_IF_ERROR(operation)                - Returns if operation is a error (public).
 *  - MYSTIC_APPEND_STATUS_IF_ERROR(status, operation) - Appends the status if it was error (public).
 *  - MYSTIC_ASSIGN_OR_RETURN(value, operation)        - Assigns value if operation status is ok (public).
 */
#pragma once

#include "MysticCore/Utility/Concat.h"

#define MYSTIC_INTERNAL_RETURN_IF_ERROR(operation) \
    ::Mystic::Status::Status MYSTIC_CONCAT(status_, __LINE__) = (operation); \
    if (MYSTIC_CONCAT(
