/*
 *  Wellcome Trust Sanger Institute
 *  Copyright (C) 2011  Wellcome Trust Sanger Institute
 *  
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version 2
 *  of the License, or (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef _PARSE_PHYLIP_H_
#define _PARSE_PHYLIP_H_

 typedef struct sample_statistics
 {
   char * sample_name;
   int number_of_recombinations;
   int number_of_snps;
   int genome_length_without_gaps;
   int number_of_blocks;
   int bases_in_recombinations_including_gaps;
   int branch_bases_in_recombinations_including_gaps;
   int bases_in_recombinations;
   int branch_bases_in_recombinations;
   int genome_length_excluding_blocks_and_gaps;
 } sample_statistics;

void get_sequence_for_sample_name(char * sequence_bases, char * sample_name);
void get_sequence_for_sample_index(char * sequence_bases, int sequence_index);
int find_sequence_index_from_sample_name( char * sample_name);
int update_sequence_base(char new_sequence_base, int sequence_index, int base_index);
int does_column_contain_snps(int snp_column, char reference_base);
int number_of_samples_from_parse_phylip(void);
void get_sample_names_from_parse_phylip(char ** sample_names);
char convert_reference_to_real_base_in_column(int snp_column, char reference_base);
void set_genome_length_without_gaps_for_sample(int sample_index, int genome_length_without_gaps);
void set_number_of_snps_for_sample(int sample_index, int number_of_snps);
void set_number_of_recombinations_for_sample(int sample_index, int number_of_recombinations);
void set_number_of_blocks_for_sample(char * sample_name,int num_blocks);
sample_statistics ** get_sample_statistics(void);
int number_of_snps_in_phylip(void);
void load_sequences_from_multifasta_file(char filename[]);
void set_internal_node(int internal_node_value,int sequence_index);
void initialise_internal_node(void);
void initialise_statistics(void);
int get_internal_node(int sequence_index);
void fill_in_unambiguous_bases_in_parent_from_children_where_parent_has_a_gap(int parent_sequence_index, int * child_sequence_indices, int num_children);
void fill_in_unambiguous_gaps_in_parent_from_children(int parent_sequence_index, int * child_sequence_indices, int num_children);
void freeup_memory(void);
void set_number_of_branch_bases_in_recombinations(int sample_index, int bases_in_recombinations, int include_gaps);
void set_number_of_bases_in_recombinations(int sample_index, int bases_in_recombinations, int include_gaps);
void filter_sequence_bases_and_rotate(char * reference_bases, char ** filtered_bases_for_snps, int number_of_filtered_snps);
void set_genome_length_excluding_blocks_and_gaps_for_sample(int sample_index, int genome_length_excluding_blocks_and_gaps);

#define MAX_READ_BUFFER 65536
#define MAX_SAMPLE_NAME_SIZE 1024


#endif




