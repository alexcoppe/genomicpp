#include<iostream>
#include <fstream>
#include<list>
#include<array>
#include<getopt.h>


int main(int argc, char *argv[]){
    char c;
    int hflag = 0;
    char help[] = "Usage: get_pass_variants [OPTION]... VCF_file\n  "
                "-h\tshow help options";

    while ((c = getopt (argc, argv, "h")) != -1){
        switch (c) {
            case 'h':
                hflag = 1;
                puts(help);
                return 1;
            case '?':
                if (isprint(optopt))
                    fprintf(stderr, "Unknown option `-%c'.\n", optopt);
                else
                    fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
                return 1;
            default:
                abort();
        }
    }

    argc -= optind;
    argv += optind;

    /* Check if there is a VCF file argument */
    if (argc < 1) {
        std::cout << "VCF file path not specified\n";
        return -1;
    }

    std::ifstream file(argv[0]);
    std::string line;

    if (file.is_open()) {
        while (getline(file, line)){
            if (line[0] != '#'){
            size_t found = line.find("\tPASS\t");
            if (found != std::string::npos)
                std::cout << line << "\n";
            } else {
                std::cout << line << "\n";
            }
        }
        file.close();
    }

    return 0;
}
