#! /usr/bin/env python
# encoding: utf-8

"""
Test manipulating and interogating trees using python modules with no external application dependancies.
"""

import unittest
import re
import shutil
import os
import difflib
import tempfile
import filecmp
from gubbins import common

class TestTreePythonMethods(unittest.TestCase):

  def test_robinson_foulds_distance(self):
    # two tree with different distances
    assert common.GubbinsCommon.robinson_foulds_distance('gubbins/tests/data/robinson_foulds_distance_tree1.tre','gubbins/tests/data/robinson_foulds_distance_tree2.tre') == 17.263494
    # two trees with same distance
    assert common.GubbinsCommon.robinson_foulds_distance('gubbins/tests/data/robinson_foulds_distance_tree1.tre','gubbins/tests/data/robinson_foulds_distance_tree1.tre') == 0
  
  def test_has_tree_been_seen_before(self):
    # same content so the tree has been seen before
    assert common.GubbinsCommon.has_tree_been_seen_before(['gubbins/tests/data/robinson_foulds_distance_tree1.tre','gubbins/tests/data/robinson_foulds_distance_tree1.tre','gubbins/tests/data/robinson_foulds_distance_tree1_dup.tre'],'weighted_robinson_foulds') == 1
    # different trees
    assert common.GubbinsCommon.has_tree_been_seen_before(['gubbins/tests/data/robinson_foulds_distance_tree1.tre','gubbins/tests/data/robinson_foulds_distance_tree1.tre','gubbins/tests/data/robinson_foulds_distance_tree2.tre'],'weighted_robinson_foulds') == 0

  def test_reroot_tree(self):
    shutil.copyfile('gubbins/tests/data/robinson_foulds_distance_tree1.tre','gubbins/tests/data/robinson_foulds_distance_tree1.tre.reroot_at_sequence_4_actual')
    common.GubbinsCommon.reroot_tree('gubbins/tests/data/robinson_foulds_distance_tree1.tre.reroot_at_sequence_4_actual', 'sequence_4')
    assert filecmp.cmp('gubbins/tests/data/robinson_foulds_distance_tree1.tre.reroot_at_sequence_4_actual','gubbins/tests/data/robinson_foulds_distance_tree1.tre.reroot_at_sequence_4')
    os.remove('gubbins/tests/data/robinson_foulds_distance_tree1.tre.reroot_at_sequence_4_actual')
    
    shutil.copyfile('gubbins/tests/data/robinson_foulds_distance_tree1.tre','gubbins/tests/data/robinson_foulds_distance_tree1.tre.reroot_tree_at_midpoint_actual')
    common.GubbinsCommon.reroot_tree('gubbins/tests/data/robinson_foulds_distance_tree1.tre.reroot_tree_at_midpoint_actual','')
    actual_file_content = open('gubbins/tests/data/robinson_foulds_distance_tree1.tre.reroot_tree_at_midpoint_actual',  encoding='utf-8').readlines()
    expected_file_content = open('gubbins/tests/data/robinson_foulds_distance_tree1.tre.reroot_tree_at_midpoint_expected',  encoding='utf-8').readlines()
    assert filecmp.cmp('gubbins/tests/data/robinson_foulds_distance_tree1.tre.reroot_tree_at_midpoint_actual', 'gubbins/tests/data/robinson_foulds_distance_tree1.tre.reroot_tree_at_midpoint_expected')
    os.remove('gubbins/tests/data/robinson_foulds_distance_tree1.tre.reroot_tree_at_midpoint_actual')
    
  def test_reroot_tree_with_outgroup(self):
    shutil.copyfile('gubbins/tests/data/robinson_foulds_distance_tree1.tre','gubbins/tests/data/robinson_foulds_distance_tree1.tre.reroot_at_sequence_4_actual')
    common.GubbinsCommon.reroot_tree_with_outgroup('gubbins/tests/data/robinson_foulds_distance_tree1.tre.reroot_at_sequence_4_actual', ['sequence_4'])
    assert filecmp.cmp('gubbins/tests/data/robinson_foulds_distance_tree1.tre.reroot_at_sequence_4_actual','gubbins/tests/data/robinson_foulds_distance_tree1.tre.reroot_at_sequence_4')
    os.remove('gubbins/tests/data/robinson_foulds_distance_tree1.tre.reroot_at_sequence_4_actual')
    
  def test_reroot_tree_with_outgroups(self):
    shutil.copyfile('gubbins/tests/data/robinson_foulds_distance_tree1.tre','gubbins/tests/data/robinson_foulds_distance_tree1.tre.reroot_at_sequence_4_actual')
    common.GubbinsCommon.reroot_tree_with_outgroup('gubbins/tests/data/robinson_foulds_distance_tree1.tre.reroot_at_sequence_4_actual', ['sequence_4','sequence_2'])
    actual_file_content = open('gubbins/tests/data/robinson_foulds_distance_tree1.tre.reroot_at_sequence_4_actual',  encoding='utf-8').readlines()
    expected_file_content = open('gubbins/tests/data/robinson_foulds_distance_tree1.tre.reroot_at_sequence_4_2',  encoding='utf-8').readlines()
    assert filecmp.cmp('gubbins/tests/data/robinson_foulds_distance_tree1.tre.reroot_at_sequence_4_actual','gubbins/tests/data/robinson_foulds_distance_tree1.tre.reroot_at_sequence_4_2')
    os.remove('gubbins/tests/data/robinson_foulds_distance_tree1.tre.reroot_at_sequence_4_actual')
    
  def test_reroot_tree_with_outgroups_all_in_one_clade(self):
    outgroups = ['A','B']
    expected_monophyletic_outgroup =  ['A','B']
    expected_output_file = 'gubbins/tests/data/expected_reroot_tree_with_outgroups_all_in_one_clade.tre'
    self.reroot_tree_check(outgroups,expected_output_file,expected_monophyletic_outgroup)
    
  def test_reroot_tree_with_outgroups_all_in_one_clade_large(self):
    outgroups = ['A','B','C']
    expected_monophyletic_outgroup =  ['A','B','C']
    expected_output_file = 'gubbins/tests/data/expected_test_reroot_tree_with_outgroups_all_in_one_clade_large.tre'
    self.reroot_tree_check(outgroups,expected_output_file,expected_monophyletic_outgroup)
    
  def test_reroot_tree_with_outgroups_all_in_different_clade(self):
    outgroups = ['A','D']
    expected_monophyletic_outgroup = ['A']
    expected_output_file = 'gubbins/tests/data/expected_reroot_tree_with_outgroups_all_in_different_clade.tre'
    self.reroot_tree_check(outgroups,expected_output_file,expected_monophyletic_outgroup)
    
  def test_reroot_tree_with_outgroups_with_two_mixed_clades(self):
    outgroups = ['A','B','C', 'D']
    expected_monophyletic_outgroup =  ['A']
    expected_output_file = 'gubbins/tests/data/expected_reroot_tree_with_outgroups_with_two_mixed_clades.tre'
    self.reroot_tree_check(outgroups,expected_output_file,expected_monophyletic_outgroup)
    
  def reroot_tree_check(self, outgroups,expected_output_file,expected_monophyletic_outgroup):
    shutil.copyfile('gubbins/tests/data/outgroups_input.tre','.tmp.outgroups_input.tre')
    
    assert expected_monophyletic_outgroup == common.GubbinsCommon.get_monophyletic_outgroup('.tmp.outgroups_input.tre', outgroups)
    common.GubbinsCommon.reroot_tree_with_outgroup('.tmp.outgroups_input.tre', outgroups)
    assert filecmp.cmp('.tmp.outgroups_input.tre',expected_output_file)
    os.remove('.tmp.outgroups_input.tre')
    
  def test_split_all_non_bi_nodes(self):
    # best way to access it is via reroot_tree_at_midpoint because it outputs to a file
    shutil.copyfile('gubbins/tests/data/non_bi_tree.tre','gubbins/tests/data/non_bi_tree.tre.actual')
    common.GubbinsCommon.reroot_tree_at_midpoint('gubbins/tests/data/non_bi_tree.tre.actual')
    assert filecmp.cmp('gubbins/tests/data/non_bi_tree.tre.actual','gubbins/tests/data/non_bi_tree.tre.expected')
    os.remove('gubbins/tests/data/non_bi_tree.tre.actual')
    
  def test_reroot_tree_at_midpoint(self):
    shutil.copyfile('gubbins/tests/data/robinson_foulds_distance_tree1.tre','gubbins/tests/data/robinson_foulds_distance_tree1.tre.reroot_tree_at_midpoint_actual')
    common.GubbinsCommon.reroot_tree_at_midpoint('gubbins/tests/data/robinson_foulds_distance_tree1.tre.reroot_tree_at_midpoint_actual')
    assert filecmp.cmp('gubbins/tests/data/robinson_foulds_distance_tree1.tre.reroot_tree_at_midpoint_actual','gubbins/tests/data/robinson_foulds_distance_tree1.tre.reroot_tree_at_midpoint_expected')
    os.remove('gubbins/tests/data/robinson_foulds_distance_tree1.tre.reroot_tree_at_midpoint_actual')

  def test_filter_out_removed_taxa_from_tree_and_return_new_file(self):
    temp_working_dir = tempfile.mkdtemp(dir=os.getcwd())
    common.GubbinsCommon.filter_out_removed_taxa_from_tree_and_return_new_file('gubbins/tests/data/robinson_foulds_distance_tree1.tre', temp_working_dir, ['sequence_1','sequence_2','sequence_3','sequence_4','sequence_5'])    
    assert filecmp.cmp(temp_working_dir + '/robinson_foulds_distance_tree1.tre', 'gubbins/tests/data/robinson_foulds_distance_tree1.tre.filter_out_removed_taxa_from_tree_expected')
    os.remove(temp_working_dir + '/robinson_foulds_distance_tree1.tre')
    os.removedirs(temp_working_dir)
    
  def test_internal_node_taxons_removed_when_used_as_starting_tree(self):
    temp_working_dir = tempfile.mkdtemp(dir=os.getcwd())
    common.GubbinsCommon.filter_out_removed_taxa_from_tree_and_return_new_file('gubbins/tests/data/tree_with_internal_nodes.tre', temp_working_dir, [])    
    assert filecmp.cmp(temp_working_dir + '/tree_with_internal_nodes.tre','gubbins/tests/data/tree_with_internal_nodes.tre_expected')
    os.remove(temp_working_dir + '/tree_with_internal_nodes.tre')
    os.removedirs(temp_working_dir)
    
  def test_create_pairwise_newick_tree(self):
    common.GubbinsCommon.create_pairwise_newick_tree(['sequence_2','sequence_3'], 'gubbins/tests/data/pairwise_newick_tree.actual')
    assert os.path.exists('gubbins/tests/data/pairwise_newick_tree.actual')
    os.remove('gubbins/tests/data/pairwise_newick_tree.actual')
    
  def test_remove_internal_node_labels(self):
    common.GubbinsCommon.remove_internal_node_labels_from_tree('gubbins/tests/data/final_tree_with_internal_labels.tre', 'final_tree_with_internal_labels.tre')
    assert os.path.exists('final_tree_with_internal_labels.tre')
    assert filecmp.cmp('final_tree_with_internal_labels.tre', 'gubbins/tests/data/expected_final_tree_without_internal_labels.tre')
    os.remove('final_tree_with_internal_labels.tre')
    
if __name__ == "__main__":
  unittest.main()