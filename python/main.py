# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# The problem:
#
# Write an alroithm that checks if a string is balanced.
#
# We say that the string is balanced if it has an equal
# amount of opening and closing brackets.
#
# Each opening bracket must have a corresponding closing bracket.
# Opening bracket must preceed the closing bracket.
#
# The accepted opening brackets are: "[", "(", "{".
# The accepted closing brackets are: "]", "(", "}"
#
# State the problem formally, determine loop invariants and write a pseudo code.
# Analyze the runtime and space complexity of the algorithm.
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Formally state the problem:
#
# The string is balanced if each right bracket purges each pairing opening
# bracket.
# If the closing bracket exists but corresponding opening bracket doesn't exist
# the string is not balanced.
#
# We can achieve the solution by storing the number of opened brackets.
#
# The each character must be correct value.
#
# Initializing the store gives us the ability to know valid characters
# and terminate if received character is incorrect.
#
# The parameter must must be a string of allowed characters.
#
# An empty argument means the following:
# We do not iterate and execute the logic.
# It is not balanced because it never contained allowed character.
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Loop invariants:
#   - Opened has the opening brackets and current amount.
#   - The c must be either opening or closing bracket.
#   - The opening bracket increases the opened brackets count.
#   - The closing bracket decreases the pairing opened bracket count.
#   - Opened brackets value below 0 terminates the loop by returning False.
#   - C is the current character of the string.
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


def isBalanced(exp):
    if not type(exp) is str:
        raise Exception("Expected a string, but received {}".format(exp))

    if exp == "":
        return False

    opened = {"[": 0, "(": 0, "{": 0}
    for c in exp:
        if c == "[" or c == "(" or c == "{":
            opened[c] += 1
        elif c == "]":
            opened["["] -= 1
        elif c == ")":
            opened["("] -= 1
        elif c == "}":
            opened["{"] -= 1
        else:
            return False
        if opened["["] < 0 or opened["("] < 0 or opened["{"] < 0:
            return False

    return opened["("] == 0 and opened["["] == 0 and opened["{"] == 0


# The isBalanced fails for incorrect input type
try:
    isBalanced(1)
except Exception as e:
    print(e)

try:
    isBalanced({})
except Exception as e:
    print(e)

try:
    isBalanced([])
except Exception as e:
    print(e)


TESTS = [
    {"sample": "[({})]", "toBe": True},
    {"sample": "[(])", "toBe": True},
    {"sample": "[{(})]", "toBe": True},
    {"sample": "[[()]", "toBe": False},
    {"sample": "[]a", "toBe": False},
    {"sample": "[]aa", "toBe": False},
    {"sample": '""', "toBe": False},
    {"sample": "]][[", "toBe": False},
    {"sample": "{}{})(", "toBe": False},
    {"sample": "}{}", "toBe": False},
    {"sample": "()", "toBe": True},
]


def expect(sample, toBe):
    print("Input: {} - Expected {}, received:".format(sample, toBe), isBalanced(sample))


for test in TESTS:
    expect(test["sample"], test["toBe"])
