#include <cstdlib>
#include <string>
#include <iostream>

#include "file_management.h"
#include "io_management.h"

#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
        std::string answer;
        FileManager file_manager;

        read_history_range(NULL,0,-1);

        while(true)
        {
            answer = get_folder();
            if (answer=="quit")
                break;
            file_manager.set_folder_path(answer);
            file_manager.get_files();
            file_manager.print_files();
            std::cout<<"Enter choice of renaming :\n";
            std::cout<<"\t1)\tAutomated renaming\n";
            std::cout<<"\t2)\tShow renaming\n";
            std::cout<<"\t3)\tManual Show renaming\n";
            std::cout<<"\t4)\tManual renaming\n";
            std::getline(std::cin,answer);

            switch(std::stoi(answer))
            {
            case 1:
                file_manager.automated_renaming();
                break;
            case 2:
                file_manager.show_renaming();
                break;
            case 3:
                file_manager.manual_show_renaming();
                break;
            case 4 :
                file_manager.manual_renaming();
                break;
            default:
                std::cout<<"No real choice entered";
            }
        }


	return EXIT_SUCCESS;
}
