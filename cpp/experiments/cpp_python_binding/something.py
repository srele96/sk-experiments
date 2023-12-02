import os
import sys
import ctypes

sys.path.append(os.path.join(os.path.dirname(__file__), 'build'))

# debug the python dll module using dependency walker and if it's not
# responding do this:
#
# Reconfigure module search order. Try to disable all except KnownDLLs and
# application directory and then open file to check. Dependency walker builds
# very large list of subdependencies and GUI elements hangs on this operation

# https://stackoverflow.com/questions/40549702/dependency-walker-hangs

# This one is useful for debugging. Loading a dll instead of `import example`
# throws different errors which helps understand the problem.
ctypes.CDLL(os.path.join(os.path.dirname(__file__), 'build', 'example.pyd'))

import example

print(example.add(1, 2))
