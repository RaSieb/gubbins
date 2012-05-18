
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <check.h>
#include "check_branch_sequences.h"
#include "helper_methods.h"

#include "branch_sequences.h"

//merge_adjacent_blocks(int ** block_coordinates, int number_of_blocks)
START_TEST (check_merge_adjacent_blocks_not_adjacent)
{
	int * blocks_not_adjacent[2]; 
	blocks_not_adjacent[0]   = (int *)  malloc((3)*sizeof(int)); 
	blocks_not_adjacent[1]   = (int *)  malloc((3)*sizeof(int)); 
	blocks_not_adjacent[0][0] = 10; 
	blocks_not_adjacent[1][0] = 20; 
	blocks_not_adjacent[0][1] = 1000; 
	blocks_not_adjacent[1][1] = 1200; 
	
	char *branch_sequence = "A";
	int snp_site_coords[9] = {10};
	int number_of_bases = 1;
	
	fail_unless(merge_adjacent_blocks(blocks_not_adjacent,2, branch_sequence,number_of_bases,snp_site_coords) == 2);
	fail_unless(blocks_not_adjacent[0][0] == 10  );
	fail_unless(blocks_not_adjacent[1][0] == 20  );
	fail_unless(blocks_not_adjacent[0][1] == 1000); 
	fail_unless(blocks_not_adjacent[1][1] == 1200);
}
END_TEST

START_TEST (check_merge_adjacent_blocks_beside_each_other)
{

	int * blocks_beside_each_other[2]; 
	blocks_beside_each_other[0]   = (int *)  malloc((3)*sizeof(int)); 
	blocks_beside_each_other[1]   = (int *)  malloc((3)*sizeof(int)); 
	blocks_beside_each_other[0][0] = 10; 
	blocks_beside_each_other[1][0] = 20; 
	blocks_beside_each_other[0][1] = 20; 
	blocks_beside_each_other[1][1] = 30;
	
	char *branch_sequence = "A";
	int snp_site_coords[9] = {10};
	int number_of_bases = 1;
	
	fail_unless(merge_adjacent_blocks(blocks_beside_each_other,2, branch_sequence,number_of_bases,snp_site_coords) == 1);
	fail_unless(blocks_beside_each_other[0][0] == 10  );
	fail_unless(blocks_beside_each_other[1][0] == 30  );
	fail_unless(blocks_beside_each_other[0][1] == 0); 
	fail_unless(blocks_beside_each_other[1][1] == 0);
}
END_TEST

START_TEST (check_merge_adjacent_blocks_near_each_other)
{	
	int * blocks_near_each_other[2]; 
	blocks_near_each_other[0]   = (int *)  malloc((3)*sizeof(int)); 
	blocks_near_each_other[1]   = (int *)  malloc((3)*sizeof(int)); 
	blocks_near_each_other[0][0] = 10; 
	blocks_near_each_other[1][0] = 20; 
	blocks_near_each_other[0][1] = 21; 
	blocks_near_each_other[1][1] = 30;
	
	char *branch_sequence = "A";
	int snp_site_coords[9] = {10};
	int number_of_bases = 1;
	
	fail_unless(merge_adjacent_blocks(blocks_near_each_other,2, branch_sequence,number_of_bases,snp_site_coords) == 1);
	fail_unless(blocks_near_each_other[0][0] == 10  );
	fail_unless(blocks_near_each_other[1][0] == 30  );
	fail_unless(blocks_near_each_other[0][1] == 0); 
	fail_unless(blocks_near_each_other[1][1] == 0);
}
END_TEST

START_TEST (check_merge_adjacent_blocks_overlapping)
{
	int * blocks_overlapping[2]; 
	blocks_overlapping[0]   = (int *)  malloc((3)*sizeof(int)); 
	blocks_overlapping[1]   = (int *)  malloc((3)*sizeof(int)); 
	blocks_overlapping[0][0] = 10; 
	blocks_overlapping[1][0] = 20; 
	blocks_overlapping[0][1] = 19; 
	blocks_overlapping[1][1] = 30;
	
	char *branch_sequence = "A";
	int snp_site_coords[9] = {10};
	int number_of_bases = 1;
	
	fail_unless(merge_adjacent_blocks(blocks_overlapping,2, branch_sequence,number_of_bases,snp_site_coords) == 1);
	fail_unless(blocks_overlapping[0][0] == 10  );
	fail_unless(blocks_overlapping[1][0] == 30  );
	fail_unless(blocks_overlapping[0][1] == 0); 
	fail_unless(blocks_overlapping[1][1] == 0);

}
END_TEST


START_TEST (check_merge_block_straddling_gap)
{
	int * blocks_overlapping[2]; 
	blocks_overlapping[0]   = (int *)  malloc((3)*sizeof(int)); 
	blocks_overlapping[1]   = (int *)  malloc((3)*sizeof(int)); 
	blocks_overlapping[0][0] = 10; 
	blocks_overlapping[1][0] = 40; 
	blocks_overlapping[0][1] = 44; 
	blocks_overlapping[1][1] = 70;
	
	char *branch_sequence = "AAA---CCC";
	int snp_site_coords[9] = {10,30,40,41,42,43,44,60,70};
	int number_of_bases = 9;

	fail_unless(merge_adjacent_blocks(blocks_overlapping,2, branch_sequence,number_of_bases,snp_site_coords) == 1);
	
	fail_unless(blocks_overlapping[0][0] == 10);
	fail_unless(blocks_overlapping[1][0] == 70);
	fail_unless(blocks_overlapping[0][1] == 0); 
	fail_unless(blocks_overlapping[1][1] == 0);

}
END_TEST


START_TEST (check_extend_end_of_block_right_over_gap)
{
	char *branch_sequence = "AA---CC";
	int snp_site_coords[7] = {30,40,41,42,43,44,60};
	int number_of_bases = 7;
	
  // Dont extend if there is no gap
	fail_unless(extend_end_of_block_right_over_gap(30,branch_sequence,number_of_bases,snp_site_coords ) == 30);
	// Dont extend if you cant get the sequence
	fail_unless(extend_end_of_block_right_over_gap(31,branch_sequence,number_of_bases,snp_site_coords ) == 31);
	fail_unless(extend_end_of_block_right_over_gap(44,branch_sequence,number_of_bases,snp_site_coords ) == 44);
	fail_unless(extend_end_of_block_right_over_gap(999,branch_sequence,number_of_bases,snp_site_coords ) == 999);
	
	// Extend block coords
	fail_unless(extend_end_of_block_right_over_gap(40,branch_sequence,number_of_bases,snp_site_coords ) == 44);
	fail_unless(extend_end_of_block_right_over_gap(41,branch_sequence,number_of_bases,snp_site_coords ) == 44);
}
END_TEST

START_TEST (check_dont_extend_right_if_gap_non_contiguous)
{
	char *branch_sequence = "AA---CC";
	int snp_site_coords[7] = {30,40,41,42,43,50,60};
	int number_of_bases = 7;
	
	// dont extend block over gap if theres no contiguous snp at the end
	fail_unless(extend_end_of_block_right_over_gap(40,branch_sequence,number_of_bases,snp_site_coords ) == 40);
	fail_unless(extend_end_of_block_right_over_gap(43,branch_sequence,number_of_bases,snp_site_coords ) == 43);
}
END_TEST

START_TEST (check_extend_right_over_multiple_gaps)
{
	char *branch_sequence = "AA-T-CC";
	int snp_site_coords[7] = {30,40,41,42,43,44,60};
	int number_of_bases = 7;
	
	// dont extend block over gap if theres no contiguous snp at the end
	fail_unless(extend_end_of_block_right_over_gap(40,branch_sequence,number_of_bases,snp_site_coords ) == 44);
	fail_unless(extend_end_of_block_right_over_gap(41,branch_sequence,number_of_bases,snp_site_coords ) == 44);
}
END_TEST


START_TEST (check_extend_right_over_multiple_gaps_stopping_at_last_snp)
{
	char *branch_sequence = "AA-T-CC";
	int snp_site_coords[7] = {30,40,41,42,43,50,60};
	int number_of_bases = 7;
	
	// dont extend block over gap if theres no contiguous snp at the end
	fail_unless(extend_end_of_block_right_over_gap(40,branch_sequence,number_of_bases,snp_site_coords ) == 42);
	fail_unless(extend_end_of_block_right_over_gap(41,branch_sequence,number_of_bases,snp_site_coords ) == 42);
}
END_TEST



START_TEST (check_extend_end_of_block_left_over_gap)
{
	char *branch_sequence = "AA---CC";
	int snp_site_coords[7] = {30,40,41,42,43,44,60};
	int number_of_bases = 7;
	
  // Dont extend if there is no gap
	fail_unless(extend_end_of_block_left_over_gap(60,branch_sequence,number_of_bases,snp_site_coords ) == 60);
	// Dont extend if you cant get the sequence
	fail_unless(extend_end_of_block_left_over_gap(59,branch_sequence,number_of_bases,snp_site_coords ) == 59);
	fail_unless(extend_end_of_block_left_over_gap(40,branch_sequence,number_of_bases,snp_site_coords ) == 40);
	fail_unless(extend_end_of_block_left_over_gap(999,branch_sequence,number_of_bases,snp_site_coords ) == 999);
	
	// Extend block coords
	fail_unless(extend_end_of_block_left_over_gap(44,branch_sequence,number_of_bases,snp_site_coords ) == 40);
	fail_unless(extend_end_of_block_left_over_gap(41,branch_sequence,number_of_bases,snp_site_coords ) == 40);
}
END_TEST

START_TEST (check_dont_extend_left_if_gap_non_contiguous)
{
	char *branch_sequence = "AA---CC";
	int snp_site_coords[7] = {30,31,41,42,43,50,60};
	int number_of_bases = 7;
	
	// dont extend block over gap if theres no contiguous snp at the end
	fail_unless(extend_end_of_block_left_over_gap(41,branch_sequence,number_of_bases,snp_site_coords ) == 41);
	fail_unless(extend_end_of_block_left_over_gap(43,branch_sequence,number_of_bases,snp_site_coords ) == 43);
}
END_TEST

START_TEST (check_extend_left_over_multiple_gaps)
{
	char *branch_sequence = "AA-T-CC";
	int snp_site_coords[7] = {30,40,41,42,43,44,60};
	int number_of_bases = 7;
	
	fail_unless(extend_end_of_block_left_over_gap(44,branch_sequence,number_of_bases,snp_site_coords ) == 40);
	fail_unless(extend_end_of_block_left_over_gap(41,branch_sequence,number_of_bases,snp_site_coords ) == 40);
}
END_TEST


START_TEST (check_extend_left_over_multiple_gaps_stopping_at_last_snp)
{
	char *branch_sequence = "AA-T-CC";
	int snp_site_coords[7] = {30,31,41,42,43,44,60};
	int number_of_bases = 7;
	
	fail_unless(extend_end_of_block_left_over_gap(44,branch_sequence,number_of_bases,snp_site_coords ) == 42);
	fail_unless(extend_end_of_block_left_over_gap(43,branch_sequence,number_of_bases,snp_site_coords ) == 42);
}
END_TEST



START_TEST (check_exclude_snp_sites_in_block)
{
	int number_of_branch_snps = 8;
	int * snp_sites;  
	snp_sites    = (int *)  malloc((number_of_branch_snps+1)*sizeof(int)); 
	snp_sites[0] = 1;
	snp_sites[1] = 3;
	snp_sites[2] = 5;
	snp_sites[3] = 6;
	snp_sites[4] = 7;
	snp_sites[5] = 8;
	snp_sites[6] = 10;
	snp_sites[7] = 11;
	
	fail_unless(exclude_snp_sites_in_block(0,2,  snp_sites, number_of_branch_snps)   == 7);
	fail_unless(exclude_snp_sites_in_block(5,7,  snp_sites, number_of_branch_snps-1) == 4);
	fail_unless(exclude_snp_sites_in_block(8,11, snp_sites, number_of_branch_snps-4) == 1);
	fail_unless(exclude_snp_sites_in_block(3,3,  snp_sites, number_of_branch_snps-7) == 0);
}
END_TEST

Suite * check_branch_sequences_suite (void)
{
  Suite *s = suite_create ("checking branch sequences");

  TCase *tc_branch_sequences = tcase_create ("excluding_recombinations");
	tcase_add_test (tc_branch_sequences, check_merge_adjacent_blocks_not_adjacent);
	tcase_add_test (tc_branch_sequences, check_merge_adjacent_blocks_beside_each_other);
	tcase_add_test (tc_branch_sequences, check_merge_adjacent_blocks_near_each_other);
	tcase_add_test (tc_branch_sequences, check_merge_adjacent_blocks_overlapping);
	tcase_add_test (tc_branch_sequences, check_exclude_snp_sites_in_block);
	tcase_add_test (tc_branch_sequences, check_merge_block_straddling_gap);
	tcase_add_test (tc_branch_sequences, check_extend_end_of_block_right_over_gap);
	tcase_add_test (tc_branch_sequences, check_dont_extend_right_if_gap_non_contiguous);
	tcase_add_test (tc_branch_sequences, check_extend_right_over_multiple_gaps);
	tcase_add_test (tc_branch_sequences, check_extend_right_over_multiple_gaps_stopping_at_last_snp);
	tcase_add_test (tc_branch_sequences, check_extend_end_of_block_left_over_gap);
	tcase_add_test (tc_branch_sequences, check_dont_extend_left_if_gap_non_contiguous);
	tcase_add_test (tc_branch_sequences, check_extend_left_over_multiple_gaps);
	tcase_add_test (tc_branch_sequences, check_extend_left_over_multiple_gaps_stopping_at_last_snp);
  suite_add_tcase (s, tc_branch_sequences);

  return s;
}