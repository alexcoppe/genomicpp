# genomiC++ :dna:
A bunch of C++ programs for working with bioinformatics files.

# Programs available :man_technologist:

## get_pass_variants

This program filters a VCF file annotated by [SnpEff](https://pcingola.github.io/SnpEff/), retaining only the variants marked as 'PASS' in the FILTER field.

Option | What does it do
------------ | -------------
-h | Show help

##### Example

```console
>>> get_pass_variants /path_to_vcf_file/variants.vcf
```
