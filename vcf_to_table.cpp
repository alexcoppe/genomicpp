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
    if (argc < 2) {
        std::cout << "VCF file path not specified\n";
        return -1;
    }

    std::ifstream file(argv[0]);
    std::string line;
    int number_of_snpeff_variants = 0;

    std::list<std::string> wanted_fields;

    std::ifstream wanted_fields_file(argv[1]);
    if (wanted_fields_file.is_open()){
        while (getline(wanted_fields_file, line)){
            //std::cout << line << "\n";
            wanted_fields.push_back(line);
        }
    }

    Vcf_with_genonotype v;
    std::string concatenated_line = "";

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

                    //std::string string_to_print = NULL;
                    for (std::string field: wanted_fields){
                        //std::cout << field << "\n";
                        if (line.find(":") != std::string::npos){
                            if (field == "chromosome"){
                                //std::cout << v.chromosome << "\t";
                                concatenated_line = concatenated_line + v.chromosome + "\t";
                            }
                            else if (field == "position") {
                                //std::cout << v.reference << "\n";
                                concatenated_line = concatenated_line +  std::to_string(v.position) + "\t";
                            }
                            else if (field == "id") {
                                //std::cout << v.reference << "\n";
                                concatenated_line = concatenated_line + v.id + "\t";
                            }
                            else if (field == "reference") {
                                concatenated_line = concatenated_line + v.reference + "\t";
                            }
                            else if (field == "alternative") {
                                concatenated_line = concatenated_line + v.alternative + "\t";
                            }
                            else if (field == "quality") {
                                concatenated_line = concatenated_line + std::to_string(v.quality) + "\t";
                            }
                            else if (field == "filter") {
                                concatenated_line = concatenated_line + v.filter + "\t";
                            }
                            else if (field == "info") {
                                concatenated_line = concatenated_line + v.info + "\t";
                            }
                        }
                        else {
                            //std::cout << "Found\n";
                        }
                    }
                    concatenated_line = concatenated_line + "\n";
                    std::cout << concatenated_line;

                    //std::cout << v.snpeff_annotation.size() << "\n";
                    //std::cout << v.info_map["dbNSFP_MetaLR_pred"] << "\n";
                    number_of_snpeff_variants = v.snpeff_annotation.size();
                    //for (Ann_variant x: v.snpeff_annotation)
                    //x.print_variant_annotation();
                }
            }
        }
        file.close();
    }


    return 0;
}
