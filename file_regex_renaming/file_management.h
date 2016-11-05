#ifndef FILE_MANEGEMENT_H
#define FILE_MANAGEMENT_H

#include <string>
#include <vector>
#include <regex>

class FileManager
{
  public:
    FileManager();
    ~FileManager(){};

    int set_folder_path(std::string);
    int get_files();

    void print_files();
    void set_regex(std::string);
    void set_renaming_string(std::string);
    void automated_renaming();
    void show_renaming();
    void manual_show_renaming();
    void manual_renaming();
    void set_forcing(bool);

  private:

    std::string folder_path;
    std::vector<std::string> list_files;
    bool forced;
    std::regex file_config_regex;

    std::string renaming_string;
    std::string base_name;
    std::string season_number;

    std::regex extension_file;
};


#endif
