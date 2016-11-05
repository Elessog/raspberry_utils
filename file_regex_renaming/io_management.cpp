#include <string>
#include <iostream>
#include <stdio.h>
#include <sys/stat.h>
#include <regex>

#include <readline/readline.h>
#include <readline/history.h>

int file_rename(const std::string& folder_path,const std::string& oldname,const std::string& new_name)
{
    int result;
    result = rename((folder_path+oldname).c_str(),(folder_path+new_name).c_str());

    if ( result != 0 )
        perror( "Error renaming file" );

    return 1;
}

std::string get_folder()
{
    std::string folder_string;
    struct stat sb;
    char *inpt;


    std::cout<< "Enter folder name default is current"<<std::endl;
    inpt = readline("Folder: ");
    add_history(inpt);
    folder_string= inpt;

    if (!folder_string.size())
        folder_string = "./";
    else
    {
        if (*(--folder_string.end())!='/')
        {
            folder_string+="/";
        }
    }
    if (stat(folder_string.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode))
    {
        std::cout<<"Entering "<<folder_string<<" ..."<<std::endl;
        return folder_string;
    }
    else
    {
        std::cerr<<"Folder does not exist !"<<std::endl;
        return get_folder();
    }
    return folder_string;
}

std::string get_base_name()
{
    std::regex base_name_r("^[ ]*([^ ].*[^ ])[ ]*");
    std::smatch sm;
    std::string base_name;

    std::cout<<"Enter base name : "<<std::endl;
    std::getline(std::cin,base_name);

    if(std::regex_match( base_name, sm,base_name_r ))
    {
        std::cout<<"Base name is "<< sm[1].str()<<std::endl;
        return sm[1].str();
    }
    else
    {
        std::cerr<<"Error it is not a name"<<std::endl;
        return get_base_name();
    }
}


std::string get_number()
{
    std::regex base_name_r("^[ ]*([0-9]*|)[ ]*");
    std::smatch sm;
    std::string base_name;

    std::cout<<"Enter Number (can be let blank): "<<std::endl;
    std::getline(std::cin,base_name);

    if(std::regex_match( base_name, sm,base_name_r ))
    {
        std::cout<<"Number is "<< sm[1].str()<<std::endl;
        if (sm[1].str().size()==1)
            return "0"+sm[1].str();
        else
            return sm[1].str();
    }
    else
    {
        std::cerr<<"Error it is not a number"<<std::endl;
        return get_number();
    }
}

std::string get_season()
{
    std::cout << "Enter season number\n";
    return get_number();
}


std::regex get_regex_for_files()
{
    std::string regex_string;
    std::cout<<"Possible regex phrases :\n";
    std::cout<<"for clss1e3.hd72_300mbfilms.com.mkv it would be : \n";
    std::cout<<"\t[.*]([0-9]{1,2})e?([0-9]{1,2})[.*]\n";
    std::cout<<"Parenthesis allow getting the number ";
    std::cout<<"Enter regex String: "<<std::endl;
    std::getline(std::cin,regex_string);

    std::regex source;
    try
    {
        source= std::regex(regex_string.c_str());
    }
    catch ( std::regex_error & e )
    {
        ///////////////
        std::cerr<<"Error in regex"<<std::endl;
        return get_regex_for_files();
    }
    catch ( std::out_of_range & e )
    {
        ///////////////
        std::cerr<<"Error in regex"<<std::endl;
        return get_regex_for_files();
    }
    catch ( std::runtime_error & e )
    {
        ///////////////
        std::cerr<<"Error in regex"<<std::endl;
        return get_regex_for_files();
    }
    return source;
}

