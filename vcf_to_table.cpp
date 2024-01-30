#include<iostream>
#include <fstream>
#include<getopt.h>
#include<list>
#include<algorithm>
#include "vcf_with_genotype_info.h"


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
    int number_of_snpeff_variants = 0;

    Vcf_with_genonotype v;

    if (file.is_open()) {
        while (getline(file, line)){


            if (line[0] != '#'){
                if (line[0] != '#'){
                    try{
                        std::string::difference_type n = std::count(line.begin(), line.end(), '\t');
                        if (n < 8)
                            throw (n);
                    }
                    catch (std::string::difference_type n){
                        std::cout << "Error in this line:\n" << line << "\nthere are only " << n << " fileds\n";
                        return -1;
                }
                    v = Vcf_with_genonotype(line);
                    //std::cout << v.snpeff_annotation.size() << "\n";
                    number_of_snpeff_variants = v.snpeff_annotation.size();
                    for (Ann_variant x: v.snpeff_annotation)
                        x.print_variant_annotation();
                    //for (int i = 0; i < number_of_snpeff_variants; i++){
                    //std::cout << v.snpeff_annotation[i];
                    //}
                    //std::cout << x << "\n";
                    //std::cout << "The ANN is: " <<  v.info_map["ANN"] << "\n";
                    //Ann_variant ann_var = Ann_variant();
                    //std::cout << ann_var.alternative_nucleotides << "\n";
                    //std::cout << "merda" << "\n";
                }
            }
        }
        file.close();
    }


    return 0;
}
