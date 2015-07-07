#!/usr/bin/env python3

from setuptools import setup
import multiprocessing
import os

version = 'x'
if os.path.exists('../VERSION'):
  version = open('../VERSION').read().strip()

setup(
    name='gubbins',
    version=version,
    description='Frontend to the Gubbins BioInformatics tool',
    author='Andrew J. Page',
    author_email='ap13@sanger.ac.uk',
    url='https://github.com/sanger-pathogens/gubbins/',
    scripts=['scripts/run_gubbins.py','scripts/gubbins_drawer.py'],
    packages=['gubbins'],
    test_suite='nose.collector',
    long_description="""\
      Gubbins is a tool for BioInformaticians that takes in a multi
      fasta alignment and detects recombination regions.  This package provides
      a simple front end to the Gubbins tool.
      """,
    classifiers=[
        "License :: OSI Approved :: GNU General Public License (GPL)",
        "Programming Language :: Python :: 3",
        "Development Status :: 4 - Beta",
        "Intended Audience :: Science/Research",
        "Topic :: Scientific/Engineering :: Bio-Informatics",
        ],
    install_requires=[
        'biopython >= 1.59',
        'dendropy  >= 4.0.2',
        'reportlab >= 3.0',
        'nose >= 1.3'
    ],
    license='GPL',
    )
