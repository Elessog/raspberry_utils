#include <dirent.h>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "file_management.h"
#include "io_management.h"

FileManager::FileManager():extension_file(".*[.](avi|AVI|mkv|MKV|flv|FLV|mp4|MP4|srt|SRT)$")
{}

int FileManager::get_files()
{
    struct dirent* fichierLu = NULL;
    DIR* dossier = opendir(folder_path.c_str());

    if (dossier == NULL)
    {
       perror("Folder : ");
       return -1;
    }

    while ((fichierLu = readdir(dossier)) != NULL){
        if (std::regex_match(fichierLu->d_name,extension_file)) {
            list_files.push_back(std::string(fichierLu->d_name));
        }
    }
    closedir(dossier);
    return 1;
}


int FileManager::set_folder_path(std::string path_to_folder)
{
    list_files.clear();
    folder_path = path_to_folder;
    return 1;
}


void FileManager::print_files()
{
    for(const auto& it : list_files)
        std::cout<<it<<"\n";
    std::cout<<std::endl;
}

bool ask_forcing()
{
    std::cout<<"Force renaming ?(y/n): ";
    std::string answer;
    std::getline(std::cin,answer);
    std::size_t found = answer.find_first_of("yYnN");
    if (found!=std::string::npos)
    {
         return (answer[found]=='y'||answer[found]=='Y');
    }
    return false;
}

void FileManager::automated_renaming()
{
    std::smatch sm;
    std::string extension;
    std::string season_number;
    std::string episode_number;
    std::string new_string;

    forced = ask_forcing();

    base_name = get_base_name();

    std::regex full_regex = get_regex_for_files();
    for(const auto& it : list_files)
    {
        std::regex_match(it,sm,extension_file);
        extension = sm[1].str();

        std::regex compliant_regex(base_name+" S[0-9]{2}E[0-9]{2}[.]"+extension);
        if (std::regex_match(it,compliant_regex))
        {
            std::cout<<it<<" already compliant skipping..."<<std::endl;
            continue;
        }
        if (std::regex_match(it,sm,full_regex))
        {
            season_number = sm[1].str();
            episode_number = sm[2].str();
            if (season_number.size()==1)
                season_number="0"+season_number;
            if (episode_number.size()==1)
                episode_number="0"+episode_number;

            new_string=base_name+" S"+season_number+"E"+episode_number+"."+extension;

            std::cout<<it<<" will be replaced by ";
            std::cout<<new_string<<std::endl;

            if (!forced)
            {
                std::size_t found = std::string::npos;

                while(found==std::string::npos)
                {
                    std::cout<<"Validate this string ?(y/n): ";
                    std::string answer;
                    std::getline(std::cin,answer);
                    found = answer.find_first_of("yYnN");
                    if (found!=std::string::npos)
                    {
                        if(answer[found]=='y'||answer[found]=='Y')
                            file_rename(folder_path,it,new_string);
                        else
                        {
                            std::cout<<"Enter your replacement"<<std::endl;
                            std::getline(std::cin,answer);
                            file_rename(folder_path,it,answer);
                        }
                    }
                    else
                        std::cerr<<"Answer not valid"<<std::endl;
                }
            }
            else
                file_rename(folder_path,it,new_string);
        }
        else
        {
            std::string answer;
            std::cerr<<it<<"  does not match regex expression\n";
            std::cerr<<"Enter your replacement"<<std::endl;
            std::getline(std::cin,answer);
            file_rename(folder_path,it,answer);
        }
    }
}

void FileManager::show_renaming()
{
    std::smatch sm;
    std::string extension;
    std::string season_number;
    std::string episode_number;
    std::string new_string;

    forced = ask_forcing();

    base_name = get_base_name();
    season_number = get_season();

    for(const auto& it : list_files)
    {
        std::cout<<it<<std::endl;
        std::regex_match(it,sm,extension_file);
        extension = sm[1].str();
        episode_number = get_number();

        new_string=base_name+" S"+season_number+"E"+episode_number+"."+extension;

        std::cout<<it<<" wll be replaced by ";
        std::cout<<new_string<<std::endl;

        if (!forced)
        {
            std::size_t found = std::string::npos;

            while(found==std::string::npos)
            {
                std::cout<<"Validate this string ?(y/n) :";
                std::string answer;
                std::getline(std::cin,answer);
                found = answer.find_first_of("yYnN");
                if (found!=std::string::npos)
                {
                    if(answer[found]=='y'||answer[found]=='Y')
                        file_rename(folder_path,it,new_string);
                    else
                    {
                        std::cout<<"Enter your replacement"<<std::endl;
                        std::getline(std::cin,answer);
                        file_rename(folder_path,it,answer);
                    }
                }
                else
                    std::cerr<<"Answer not valid"<<std::endl;
            }
        }
        else
            file_rename(folder_path,it,new_string);
    }
}


void FileManager::manual_show_renaming()
{
    std::smatch sm;
    std::string extension;
    std::string season_number;
    std::string episode_number;
    std::string new_string;

    forced = ask_forcing();

    base_name = get_base_name();
    for(const auto& it : list_files)
    {
        std::cout<<it<<std::endl;
        std::regex_match(it,sm,extension_file);
        extension = sm[1].str();
        season_number = get_season();
        std::cout<<"Enter Episode Number : "<<std::endl;
        episode_number = get_number();

        new_string=base_name+" S"+season_number+"E"+episode_number+"."+extension;

        std::cout<<it<<" will be replaced by ";
        std::cout<<new_string<<std::endl;

        if (!forced)
        {
            std::size_t found = std::string::npos;

            while(found==std::string::npos)
            {
                std::cout<<"Validate this string ?(y/n): ";
                std::string answer;
                std::getline(std::cin,answer);
                found = answer.find_first_of("yYnN");
                if (found!=std::string::npos)
                {
                    if(answer[found]=='y'||answer[found]=='Y')
                        file_rename(folder_path,it,new_string);
                    else
                    {
                        std::cout<<"Enter your replacement"<<std::endl;
                        std::getline(std::cin,answer);
                        file_rename(folder_path,it,answer);
                    }
                }
                else
                    std::cerr<<"Answer not valid"<<std::endl;
            }
        }
        else
            file_rename(folder_path,it,new_string);
    }
}



void FileManager::manual_renaming()
{
    std::string answer;

    for(const auto& it : list_files)
    {
        std::cout<<"Enter your replacement"<<std::endl;
        std::getline(std::cin,answer);
        file_rename(folder_path,it,answer);
    }
}


void FileManager::set_forcing(bool forcing)
{
    forced=forcing;
}
