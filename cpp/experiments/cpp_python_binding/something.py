import os
import sys
import ctypes

# Allow built modules to be imported
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
print(example.threaded_operation([1, 2, 3, 4, 5]))
example.each_async([1, 2, 3, 4, 5], lambda x: print(x))

try:
    # Doesn't support non integer values, should throw.
    example.each_async([1.25, 2.25, 3.35], lambda x: print(x))
except TypeError as e:
    print(e)
