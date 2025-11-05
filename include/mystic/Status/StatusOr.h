/**
 * @path [ROOT]/Include/MysticCore/Status/StatusOr.h
 * @file StatusOr.h
 * @brief Class to hold a specific status or data type.
 */

/**
 * As framework don't use exceptions, it relies on status code and status error handling.
 * This file defines various main StatusOr class for status holding or data type.
 *
 * This file provide StatusOr class as,
 *  - Mystic::Status::StatusOr - The status or data type holding class.
 */
#pragma once

// For placement new
#include <new>

// Fir std::move & std::forward
#include <utility>

// For framework api
#include "MysticCore/Architecture/FrameworkAPI.h"

// For check & dcheck
#include "MysticCore/Assert/Assert.h"

// For Status
#include "MysticCore/Status/Status.h"

// For status's in_place struct
#include "MysticCore/Status/InPlace.h"

namespace Mystic::Status {

/**
 * @class StatusOr
 * @brief Class to hold either data type of status, but not both.
 *
 * @tparam T Data type.
 */
MYSTIC_INTERNAL_ARCH_FRAMEWORK_API
template <typename T>
class StatusOr {
public:
    /**
     * @brief Value constructor.
     * @details Constructor to construct StatusOr with the data type.
     *
     * @tparam value Value of specific data type.
     */
    StatusOr(T value) : m_IsValue(true), m_Status(Status::OK()) {
        new (m_Storage) T(std::move(value));
    }

    /**
     * @brief Error constructor
     * @details Constructor to construct a StatusOr object with status.
     *
     * @param status The Status object.
     */
    StatusOr(Status status) : m_IsValue(false), m_Status(std::move(status)) {
        MYSTIC_DCKECK(!status.ok()) // Should only construct error status
    }

    /**
     * @brief In-place constructor.
     * @details Constructs the data type T directly in the internal storage
     * using the provided arguments.
     *
     * @tparam Args Argument types to forward to T's constructor.
     * @param tag The in_place tag to select this overload.
     * @param args Arguments forwarded to T's constructor.
     */
    template <typename... Args>
    explicit StatusOr(in_place_t tag, Args&&... args)
        : m_IsValue(true), m_Status(Status::OK()) {
        // Use placement new with perfect forwarding
        new (m_Storage) T(std::forward<Args>(args)...);
    }
    
    /**
     * @brief Destructor to call T's destructor.
     * @details on destruction of StatusOr if the data type is not
     * moved or copied then call 's destructor.
     */
    ~StatusOr() { 
        if (m_IsValue) {
            reinterpret_cast<T*>(m_Storage)->~T();
            m_IsValue = false;
        }
    }
    
    /**
     * @brief Copy constructor.
     * @details This copies a StatusOr object.
     */
    StatusOr(const StatusOr& other) 
        : m_IsValue(other.m_IsValue), m_Status(other.m_Status) {
        if (m_IsValue) {
            new (m_Storage) T(*reinterpret_cast<const T*>(other.m_Storage));
        }
    }
    
    /**
     * @brief Move constructor.
     * @details This moves a StatusOr object.
     */
    StatusOr(StatusOr&& other) 
        : m_IsValue(other.m_IsValue), m_Status(other.m_Status) {
        if (m_IsValue) {
            new (m_Storage) T(std::move(*reinterpret_cast<const T*>(other.m_Storage)));
            // Set other StatusOr object's m_IsValue to false.
            // This prevent other's destructor to call ~T() later.
            other.m_IsValue = false;
        }
    }

    /**
     * @brief Copy assignment operator.
     * @details Copies an StatusOr object to another object via assignment.
     */
    StatusOr& operator=(const StatusOr& other) {
        if (this == &other) {
            return *this;
        }

        if (other.m_IsValue) {
            if (m_IsValue) {
                // Case 1: Both hold a value. Use T's copy assignment.
                *reinterpret_cast<T*>(m_Storage) = *reinterpret_cast<const T*>(other.m_Storage);
            } else {
                // Case 2: Source holds a value, destination holds a status.
                // Destroy old status, construct T via placement new (copy).
                m_Status = other.m_Status; // Status will be OK()
                new (m_Storage) T(*reinterpret_cast<const T*>(other.m_Storage));
                m_IsValue = true;
            }
        } else { // other holds a Status
            if (m_IsValue) {
                // Case 3: Source holds status, destination holds a value.
                // Destroy old value, copy new status.
                reinterpret_cast<T*>(m_Storage)->~T();
                m_IsValue = false;
                m_Status = other.m_Status;
            } else {
                // Case 4: Both hold a Status. Copy new status.
                m_Status = other.m_Status;
            }
        }
        return *this;
    }

    /**
     * @brief Move assignment operator.
     * @details Moves an StatusOr object to another object via assignment.
     */
    StatusOr& operator=(StatusOr&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        if (other.m_IsValue) {
            if (m_IsValue) {
                // Case 1: Both hold a value. Use T's move assignment.
                *reinterpret_cast<T*>(m_Storage) = std::move(*reinterpret_cast<T*>(other.m_Storage));
            } else {
                // Case 2: Source holds a value, destination holds a status.
                // Destroy old status, construct T via placement new (move).
                m_Status = std::move(other.m_Status); // Status will be OK()
                new (m_Storage) T(std::move(*reinterpret_cast<T*>(other.m_Storage)));
                m_IsValue = true;
            }
            // In all cases where the source held a value, it has been moved from,
            // so we mark it as holding no value to prevent its destructor from running.
            other.m_IsValue = false;
        } else { // other holds a Status
            if (m_IsValue) {
                // Case 3: Source holds status, destination holds a value.
                // Destroy old value, move new status.
                reinterpret_cast<T*>(m_Storage)->~T();
                m_IsValue = false;
            }
            // Case 4: Both hold a Status (or case 3 cleanup). Move new status.
            m_Status = std::move(other.m_Status);
        }
        return *this;
    }

    /**
     * @brief Accessor ok()
     * @details This function checks if the status was success or not.
     * This acheives it by checking m_IsValue.
     *
     * @note While framework use PascalCase for functions, it is delibrate
     * inconsistency for natural accessor syntax like, some_value.ok().
     *
     * @returns bool Whether the StatusOr holds data type or error code.
     */
    bool ok() const { return m_IsValue; }

    /**
     * @brief Getter for status object.
     * @details This function returns the Status object stored in StatusOr.
     *
     * @returns Status The specific status stored in StatusOr object.
     */
    const Status& status() const { return m_Status; }

    /**
     * @brief Data type value accessor (const).
     * @details This function access the value stored in StatusOr.
     *
     * @returns T const or non-const value.
     */
    const T& value() const& {
        MYSTIC_CHECK(m_Status.ok()) // Ensure status is Ok.
        return *reinterpret_cast<const T*>(m_Storage);
    }

    /**
     * @brief Data type value accessor (non-const).
     * @details This function access the value stored in StatusOr.
     *
     * @returns T non-const reference to the value.
     */
    T& value() & {
        MYSTIC_CHECK(m_Status.ok()); // Ensure status is Ok.
        return *reinterpret_cast<T*>(m_Storage);
    }

    /**
     * @brief Data type value accessor (move-based).
     * @details This function extracts the value stored in StatusOr by moving it out.
     * After this call, the StatusOr is left in an empty state (no value).
     *
     * @returns T The value of the specific data type, moved out of the StatusOr.
     */
    T value() && {
        MYSTIC_CHECK(m_Status.ok()) // Ensure status is Ok.
        // Get the pointer to the stored value
        T* value_ptr = reinterpret_cast<T*>(m_Storage);

        // Mark the storage as empty before moving the value.
        // This prevents the StatusOr destructor from calling ~T() later.
        m_IsValue = false;

        // Use std::move to transfer ownership of the value out.
        return std::move(*value_ptr);
    }

    /**
     * @brief Reference access (const).
     */
    const T& operator*() const& {
        MYSTIC_CHECK(m_Status.ok()) // Ensure status is Ok.
        return *reinterpret_cast<const T*>(m_Storage);
    }

    /**
     * @brief Reference access (non-const).
     */
    T& operator*() & {
        MYSTIC_CHECK(m_Status.ok()) // Ensure status is Ok.
        return *reinterpret_cast<T*>(m_Storage);
    }

    /**
     * @brief Reference access (move-based).
     */
    T&& operator*() && {
        MYSTIC_CHECK(m_Status.ok()) // Ensure status is Ok.
        return std::move(value());
    }

    /**
     * @brief Pointer access (const).
     */
    const T& operator->() const& {
        MYSTIC_CHECK(m_Status.ok()) // Ensure status is Ok.
        return reinterpret_cast<const T*>(m_Storage);
    }

    /**
     * @brief Pointer access (non-const).
     */
    T& operator->() & {
        MYSTIC_CHECK(m_Status.ok()) // Ensure status is Ok.
        return reinterpret_cast<T*>(m_Storage);
    }

    /**
     * @brief Safe value accessor.
     * @details This function returns a object or default value like std::optional.
     */
    const T& value_or(T default_value) const& {
        return ok() ? value() : default_value;
    }
    
    /**
     * @brief Explicit bool operator.
     */
    explicit operator bool() const { return ok(); }
    
private:
    /**
     * @brief Status to store the current status of the object.
     */
    Status m_Status;

    /**
     * @brief Whether StatusOr is holding data or status.
     */
    bool m_IsValue;

    /**
     * @brief Memory for the data type to be holded.
     */
    alignas(T) unsigned char m_Storage[sizeof(T)];
}; // class StatusOr

} // namespace Mystic::Status

