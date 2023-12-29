#include<iostream>
#include <fstream>
#include<getopt.h>
#include<list>
#include<algorithm>
#include "vcf.h"

class Vcf_with_genonotype: public Vcf{
    public:
        std::string format = "";
        std::string sample1 = "";
        std::string sample2 = "";

        Vcf_with_genonotype();
        Vcf_with_genonotype(std::string);
        void show();
};

