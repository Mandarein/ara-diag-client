/* Diagnostic Client library
 * Copyright (C) 2022  Avijit Dey
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#ifndef DIAGNOSTIC_CLIENT_LIB_LIB_LIBUTILITY_UTILITY_LOGGER_H
#define DIAGNOSTIC_CLIENT_LIB_LIB_LIBUTILITY_UTILITY_LOGGER_H

#ifdef USE_DLT
#include <dlt/dlt.h>
#endif

#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <string_view>
#include <utility>

namespace libUtility {
namespace logger {
class Logger {
public:
  template<typename Func>
  auto LogFatal(const std::string &file_name, int line_no, const std::string &func_name, Func func) noexcept -> void {
#ifdef USE_DLT
    LogDltMessage(DLT_LOG_FATAL, file_name, func_name, line_no, func);
#else
    std::cout << "[FATAL]:   " << CreateLoggingMessage(file_name, func_name, line_no, func).str() << std::endl;
#endif
  }

  template<typename Func>
  auto LogError(const std::string &file_name, int line_no, const std::string &func_name, Func func) noexcept -> void {
#ifdef USE_DLT
    LogDltMessage(DLT_LOG_VERBOSE, file_name, func_name, line_no, func);
#else
    std::cout << "[ERROR]:   " << CreateLoggingMessage(file_name, func_name, line_no, func).str() << std::endl;
#endif
  }

  template<typename Func>
  auto LogWarn(const std::string &file_name, int line_no, const std::string &func_name, Func func) noexcept -> void {
#ifdef USE_DLT
    LogDltMessage(DLT_LOG_VERBOSE, file_name, func_name, line_no, func);
#else
    std::cout << "[WARN]:    " << CreateLoggingMessage(file_name, func_name, line_no, func).str() << std::endl;
#endif
  }

  template<typename Func>
  auto LogInfo(const std::string &file_name, int line_no, const std::string &func_name, Func func) noexcept -> void {
#ifdef USE_DLT
    LogDltMessage(DLT_LOG_VERBOSE, file_name, func_name, line_no, func);
#else
    std::cout << "[INFO]:    " << CreateLoggingMessage(file_name, func_name, line_no, func).str() << std::endl;
#endif
  }

  template<typename Func>
  auto LogDebug(const std::string &file_name, int line_no, const std::string &func_name, Func func) noexcept -> void {
#ifdef USE_DLT
    LogDltMessage(DLT_LOG_VERBOSE, file_name, func_name, line_no, func);
#else
    std::cout << "[DEBUG]:   " << CreateLoggingMessage(file_name, func_name, line_no, func).str() << std::endl;
#endif
  }

  template<typename Func>
  auto LogVerbose(const std::string &file_name, int line_no, const std::string &func_name, Func func) noexcept -> void {
#ifdef USE_DLT
    LogDltMessage(DLT_LOG_VERBOSE, file_name, func_name, line_no, func);
#else
    std::cout << "[VERBOSE]: " << CreateLoggingMessage(file_name, func_name, line_no, func).str() << std::endl;
#endif
  }

public:
  // ctor
  explicit Logger(const std::string &context_id);

  // ctor
  Logger(const std::string &app_id, const std::string &context_id);

  // dtor
  ~Logger();

private:
  template<typename Func>
  auto CreateLoggingMessage(const std::string &file_name, const std::string & /* func_name */, int line_no,
                            Func func) noexcept -> std::stringstream {
    std::stringstream msg;
    func(msg);
    msg << " [" << file_name << ":" << line_no << "]";
    return msg;
  }

#ifdef USE_DLT
  template<typename Func>
  void LogDltMessage(int log_level, const std::string &func_name, const std::string &file_name, int line_no,
                     Func func) {
    if (DLT_IS_LOG_LEVEL_ENABLED(contxt_, log_level)) {
      DLT_LOG(contxt_, log_level, DLT_CSTRING(CreateLoggingMessage(file_name, func_name, line_no, func).str().c_str()));
    }
  }
#endif

#ifdef USE_DLT
  // Declare the context
  DLT_DECLARE_CONTEXT(contxt_);
#endif
};
}  // namespace logger
}  // namespace libUtility
#endif  // DIAGNOSTIC_CLIENT_LIB_LIB_LIBUTILITY_UTILITY_LOGGER_H