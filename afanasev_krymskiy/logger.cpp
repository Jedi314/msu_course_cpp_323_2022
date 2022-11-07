#include "logger.hpp"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "config.hpp"

namespace {
std::string get_current_date_time() {
  const auto date_time = std::chrono::system_clock::now();
  const auto date_time_t = std::chrono::system_clock::to_time_t(date_time);
  std::stringstream date_time_string;
  date_time_string << std::put_time(std::localtime(&date_time_t),
                                    "%Y.%m.%d %H:%M:%S");
  return date_time_string.str();
}
}  // namespace

void Logger::log(const std::string& string) {
  const auto& current_date_time = get_current_date_time();
  std::cout << current_date_time + string << std::endl;
  log_ << current_date_time + string << std::endl;
}

Logger& Logger::get_logger() {
  static Logger logger;
  return logger;
}

Logger::Logger() : log_(std::ofstream(config::kLogFilePath, std::ios::app)) {}
