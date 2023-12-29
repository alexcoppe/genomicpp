all: vcf_example get_pass_variants vcf_with_genotype_example

CC=g++

get_pass_variants: get_pass_variants.cpp
	$(CC) -std=c++11 get_pass_variants.cpp -o get_pass_variants
vcf_with_genotype_example: vcf_with_genotype_info.o vcf_with_genotype_example.o vcf.o
	$(CC) -std=c++11 vcf_with_genotype_info.o vcf_with_genotype_example.o vcf.o -o vcf_with_genotype_example
vcf_example: vcf.o vcf_example.o
	$(CC) -std=c++11  vcf_example.o vcf.o -o vcf_example
vcf.o: vcf.cpp
	$(CC) -std=c++11 -c vcf.cpp
vcf_example.o: vcf_example.cpp
	$(CC) -std=c++11 -c vcf_example.cpp
vcf_with_genotype_info.o: vcf_with_genotype_info.cpp
	$(CC) -std=c++11 -c vcf_with_genotype_info.cpp
vcf_with_genotype_example.o: vcf_with_genotype_example.cpp
	$(CC) -std=c++11 -c vcf_with_genotype_example.cpp
clean:
	rm -rf *.o vcf_example get_pass_variants vcf_with_genotype_example
