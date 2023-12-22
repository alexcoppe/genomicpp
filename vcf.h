#include<iostream>
#include <fstream>
#include<getopt.h>
#include<list>
#include<algorithm>


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

        Vcf();
        Vcf(std::string,
                int, std::string, std::string, std::string, float, std::string, std::string);
        void show();
        Vcf vcf_from_vcf_line(std::string);
};


Vcf vcf_from_vcf_line(std::string);
