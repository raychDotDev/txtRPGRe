#include "Logger.hpp"
#include <iostream>
#include <string>

void Logger::Trace(LogLevel level, std::string text) {
  std::string lvl = "";
  switch (level) {
  case INFO: {
    lvl = "[INFO]";
  } break;

  case DEBUG: {
    lvl = "[DEBUG]";
  } break;

  case ERROR: {
    lvl = "[ERROR]";
  } break;
  }
  std::cout << lvl << "\t" << text << "\n";
}
