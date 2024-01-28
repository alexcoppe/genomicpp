#include<iostream>
#include <fstream>
#include<getopt.h>
#include<list>
#include<algorithm>
#include<map>


class Vcf{
    public:
        std::string chromosome;
        int position;
        std::string id;
        std::string reference;
        std::string alternative;
        float quality;
        std::string filter;
        std::string info;
        std::map<std::string, std::string> info_map;

        Vcf();
        Vcf(std::string);
        Vcf(std::string,
                int, std::string, std::string, std::string, float, std::string, std::string);
        void show();
    private:
        void build_info_map();
        void build_ann();
};

