/**
 * Header-only CSV logging utility.
 *
 * Usage:
 * First, make sure you're including this header. Call
 * logging::clearLogFile() once before the main loop.
 * Then, to log a timestamped row to the CSV file, call
 * logging::log(...) with any number of values you want
 * to log. For example, given a pros::Motor called myMotor:
 *
 *     logging::log(myMotor.get_current_draw(), myMotor.get_position());
 *
 * Author: Quinn Tucker
 */

#ifndef _LOGGING_H_
#define _LOGGING_H_

#include "main.h"
#include <fstream>

namespace logging {

    /** The path to the CSV file to be logged to. */
    constexpr char LOG_FILE_PATH[] = "/usd/motor_log.csv";

    /**
     * Clear the log file (if it exists) or create a new,
     * empty log file (if it doesn't exist yet).
     *
     * Call this once before your main loop.
     */
    static void clearLogFile() {
        std::ofstream(LOG_FILE_PATH);
    }

    /**
     * Namespace containing implementation details.
     * Don't use these functions yourself.
     */
    namespace impl {
        /**
         * Recursion base case: no values left, so just return.
         */
        static void logHelper(std::ofstream& out) {}

        /**
         * Main recursive template: logs one value and recurses.
         */
        template<class T, class... Rest>
        void logHelper(std::ofstream& out, T&& value, Rest&&... rest) {
            out << ',' << std::forward<T>(value);
            logHelper(out, std::forward<Rest>(rest)...);
        }
    }

    /**
     * Append a row to the CSV file, containing a timestamp
     * followed by zero or more arbitrary values.
     *
     * NOTE: this does not escape any commas in the values themselves
     */
    template<class... Args>
    void log(Args&&... args) {
        std::ofstream out(LOG_FILE_PATH);
        out << pros::millis();
        impl::logHelper(out, std::forward<Args>(args)...);
        out << '\n';
    }
}

#endif
