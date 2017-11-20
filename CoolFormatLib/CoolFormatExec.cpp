#include "stdafx.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <iterator>

#define USE_LOCAL_CONFIG_FILE

#include "StrUseful.h"
#include "GlobalTidy.h"
#include "FormatterHelp.h"

const std::string _version = "1.0";

int main(int argc, char** argv)
{
    if (argc < 3)
    {
        std::cout << "CoolFormat " << _version << std::endl;
        return 0;
    }
    std::string arg = std::string(argv[1]);
    if (arg == "-v" || arg != "-f")
    {
        std::cout << "CoolFormat " << _version << std::endl;
        return 0;
    }

    std::vector<std::string> fileNameVector;
    for (int i = 2; i < argc; i++)
    {
        fileNameVector.push_back(arg);
    }

    for (size_t i = 0; i < fileNameVector.size(); i++)
    {
        std::string originalFileName = fileNameVector[i];
        std::string inFileName = originalFileName;

        std::ifstream in(inFileName.c_str());
        if (!in)
        {
            std::cout << "Could not open input file" << inFileName.c_str();
            exit(1);
        }
    }

	return 0;
}

