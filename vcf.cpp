#include<iostream>
#include <fstream>
#include<getopt.h>
#include<list>


class Vcf{
    public:
        std::string chromosome;
        int position;

        Vcf();
        Vcf(std::string,
                int);
        void show();
        void vcf_from_vcf_line(std::string);
};


Vcf::Vcf(){
    chromosome = "";
    position = 0;
}

Vcf::Vcf(std::string chr, int pos){
    chromosome = chr;
    position = pos;
}

void Vcf::show(){
    std::cout << "Chromosome: " << chromosome << "\n";
    std::cout << "Position: " << position << "\n";
}


void vcf_from_vcf_line(std::string l){
    //std::cout << "Running\n";
    size_t pos = 0;
    std::string token;
    std::list<std::string> fields;
    int i = 0;

    Vcf v;

    while ((pos = l.find("\t")) != std::string::npos){
        token = l.substr(0, pos);
        //std::cout << token << "\n";

        if (i == 0)
            v.chromosome = token;
        if (i == 1)
            v.position = stoi(token);

        fields.push_back(token);
        l = l.substr(pos + 1, l.length());
        i++;
    }

    v.show();

    token = l.substr(pos + 1, l.length());
    //std::cout << token << "\n";
    fields.push_back(token);
}

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

    Vcf v;

    if (file.is_open()) {
        while (getline(file, line)){
            if (line[0] != '#'){
                if (line[0] != '#'){
                    vcf_from_vcf_line(line);
                    //std::cout << line << "\n";
                }
            }
        }
        file.close();
    }

    //Vcf v("fdf", 22);
    //v.show();

    return 0;
}
