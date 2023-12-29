#include<iostream>
#include <fstream>
#include<getopt.h>
#include<list>
#include<algorithm>
#include "vcf_with_genotype_info.h"
#include<array>


Vcf_with_genonotype::Vcf_with_genonotype(): Vcf(){
}

Vcf_with_genonotype::Vcf_with_genonotype(std::string l) : Vcf(l){
    //Vcf_with_genonotype::Vcf_with_genonotype(std::string s){
    //
    size_t pos = 0;
    std::string token;
    //std::list<std::string> fields;
    int i = 0;

    while ((pos = l.find("\t")) != std::string::npos){
        token = l.substr(0, pos);

        if (i == 8){
            format = token;
        }
        if (i == 9){
            sample1 = token;
        }

        //fields.push_back(token);
        l = l.substr(pos + 1, l.length());
        i++;
    }

    token = l.substr(pos + 1, l.length());
    //fields.push_back(token);

    sample2 = token;
 
}

void Vcf_with_genonotype::show(){
    Vcf::show();
    std::cout << "Format: " << format << "\n";
    std::cout << "Sample 1: " << sample1 << "\n";
    std::cout << "Sample 2: " << sample2 << "\n";
}
