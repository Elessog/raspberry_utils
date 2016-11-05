#ifndef IO_MANAGEMENT_H
#define IO_MANAGEMENT_H

#include <string>
#include <regex>

int file_rename(const std::string&, const std::string&, const std::string&);

std::string get_folder();

std::string get_base_name();
std::string get_number();
std::string get_season();
std::regex get_regex_for_files();

#endif
