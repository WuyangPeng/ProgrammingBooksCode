
# Updated: 7th November 2003

import os
import re
import string
import sys


# functions

def arithmetic_compare(lhs, rhs):
	if int(lhs) < int(rhs):
		return -1
	elif int(lhs) == int(rhs):
		return 0
	else:
		return +1

# data structures

# Contains a hash of the concat results for a given scenario
class ScenarioResults:
	def __init__(self):
		self.entries = {} # Hash of #concats => result

	def __setitem__(self, key, value):
		self.entries[key] = value;

	def __getitem__(self, key):
		return self.entries[key];


class Scenario:
	def __init__(self, name):
		self.results	=	ScenarioResults()
		self.name		=	name;

class Compiler:
	def __init__(self, name):
		self.name		=	name
		self.scenarios	=	{} # Hash of scenario name => ScenarioResults

	def AddScenario(self, scen_name):
		self.scenarios[scen_name] = ScenarioResults()
	

compilers = {}	# Hash of compiler names => Compiler

# scenario detector

scenario_detector = re.compile(r'fast_string_concatenator_test\:\s+(.*?)\;\s+(.*?)$')

scenario		=	''
compiler		=	''

for line in open(sys.argv[1], 'r').readlines():
	cols	= string.split(line)
	if len(cols) > 0:
		if cols[0] == 'MAKE':
			# The "MAKE" line
			cols[0] = ''
		else:
			m = scenario_detector.match(line)
			if m:
				# The scenario line
				scenario, compiler = m.group(1, 2)
				scenario_row = ()
				if not compilers.has_key(compiler):
					compilers[compiler] = Compiler(compiler)
				compilers[compiler].AddScenario(scenario)
#				print compiler + '  "' + scenario +'"'
			else:
				# The data line
				if len(compiler) == 0:
					print 'Data file is bad: <compiler> unknown'
					sys.exit(1)
				if len(scenario) == 0:
					print 'Data file is bad: <scenario> unknown'
					sys.exit(1)
				concat_num	=	cols[0]
				time		=	cols[1]
#				print '#Concat: ' + concat_num + '; Time: ' + time
				compilers[compiler].scenarios[scenario][concat_num] = time

#scen_keys = ('C', 'C++', 'C#', 'D', 'Java')

for compiler in compilers.values():
	print compiler.name,
	scenario_names = compiler.scenarios.keys()
	scenario_names.sort()
	for scenario in scenario_names:
		print '\t' + scenario,
	print
	# Now need to amass the total entries in the #concats, in a hash
	num_concats_names = {}
	for scenario in compiler.scenarios.values():
		for entry in scenario.entries.keys():
			num_concats_names[entry] = entry
	# transform the keys in the hash into a list
	num_concats_names = num_concats_names.keys()
	# sort them
	num_concats_names.sort(arithmetic_compare)
	for num_concat_name in num_concats_names:
		print num_concat_name, 
		for scenario in scenario_names:
			print '\t' + compiler.scenarios[scenario].entries[num_concat_name],
		print
