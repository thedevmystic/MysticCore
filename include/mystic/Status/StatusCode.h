/**
 * @path [ROOT]/Include/MysticCore/Status/StatusCode.h
 * @file StatusCode.h
 * @brief Status code for different types of error.
 */

/**
 * As framework don't use exceptions, it relies on status code and status error handling.
 * This file defines various status codes.
 *
 * This file provides StatusCode enum class,
 *  - Mystic::Status::StatusCode  - Status codes.
 */
#pragma once

// For framework api
#include "MysticCore/Architecture/FrameworkAPI.h"

// For uint32_t
#include "MysticCore/Types/StandardInts.h"

namespace Mystic::Status {

/**
 * @enum StatusCode
 * @brief Enum class containing status codes.
 */
MYSTIC_INTERNAL_ARCH_FRAMEWORK_API
enum class StatusCode : ::Mystic::Types::uint32_t {
    // --- Success ---
    OK = 0,               // Not an error; returned on success.

    // --- Client Errors (Codes 1 - 7) ---
    CANCELLED = 1,        // Operation was cancelled.
    INVALID_ARGUMENT = 2, // The client specified an invalid argument.
    NOT_FOUND = 3,        // Some requested entity (e.g., file, record) was not found.
    ALREADY_EXISTS = 4,   // The entity that a client attempted to create already exists.
    PERMISSION_DENIED = 5, // The caller does not have permission to execute the specified operation.
    UNAUTHENTICATED = 6,  // The request does not have valid authentication credentials.
    OUT_OF_RANGE = 7,     // The operation was attempted past the valid range (e.g., seeking past end-of-file).

    // --- System/Server Errors (Codes 8 - 14) ---
    DEADLINE_EXCEEDED = 8, // The deadline expired before the operation could complete.
    RESOURCE_EXHAUSTED = 9,  // Some resource has been exhausted (e.g., memory, disk space, quota).
    FAILED_PRECONDITION = 10, // Operation was rejected because the system is not in a state required for the execution (e.g., directory to delete is non-empty).
    ABORTED = 11,         // The operation was aborted, typically due to a concurrency issue like a transaction abort.
    UNIMPLEMENTED = 12,   // The operation is not implemented or not supported/enabled.
    INTERNAL = 13,        // Internal errors. Some invariants expected by the underlying system have been broken.
    UNAVAILABLE = 14,     // The service is currently unavailable.
    DATA_LOSS = 15,       // Unrecoverable data loss or corruption.
}; // enum class StatusCode

/**
 * @brief Function to convert StatusCode to string.
 *
 * @param code The StatusCode object.
 */
MYSTIC_INTERNAL_ARCH_FRAMEWORK_API
const std::string& StatusCodeToString(StatusCode code) {
    switch(code) {
        case StatusCode::OK:
            return "Ok";
            break;

        case StatusCode::CANCELLED:
            return "Cancelled";
            break;

        case StatusCode::INVALID_ARGUMENT:
            return "Invalid Argument";
            break;

        case StatusCode::NOT_FOUND:
            return "Not Found";
            break;

        case StatusCode::ALREADY_EXISTS:
            return "Already Exists";
            break;

        case StatusCode::PERMISSION_DENIED:
            return "Permission Denied";
            break;

        case StatusCode::UNAUTHENTICATED:
            return "Unauthenticated";
            break;

        case StatusCode::OUT_OF_RANGE:
            return "Out of Range";
            break;

        case StatusCode::DEADLINE_EXCEEDED:
            return "Deadline Exceeded";
            break;

        case StatusCode::RESOURCE_EXHAUSTED:
            return "Resource Exhausted";
            break;

        case StatusCode::FAILED_PRECONDITION:
            return "Failed Precondition";
            break;

        case StatusCode::ABORTED:
            return "Aborted";
            break;

        case StatusCode::UNIMPLEMENTED:
            return "Unimplemented";
            break;

        case StatusCode::INTERNAL:
            return "Internal";
            break;

        case StatusCode::UNAVAILABLE:
            return "Unavailable";
            break;

        case StatusCode::DATA_LOSS:
            return "Data Loss";
            break;

        default:
            return "Unknown";
            break;
    }
}

} // namespace Mystic::Status

