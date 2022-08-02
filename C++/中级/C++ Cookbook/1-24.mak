# All the targets in this makefile are phony
.PHONY: all johnpaul georgeringo hellobeatles

# Default target
all: hellobeatles

# The targets johnpaul, georgeringo, and hellobeatles represent
# directories; the command script invokes make in each directory
johnpaul georgeringo hellobeatles:
	$(MAKE) --directory=$@ $(TARGET)

# This rule indicates that the default target of the makefile
# in directory hellobeatles depends on the default targets of
# the makefiles in the directories johnpaul and georgeringo
.PHONY: hellobeatles
hellobeatles: johnpaul georgeringo