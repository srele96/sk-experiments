class Solution:
    def findWords(self, board, words):
        root = {}
        for word in words:
            node = root
            for c in word:
                node = node.setdefault(c, {})
            node[None] = True
        board = {
            i + 1j * j: c for i, row in enumerate(board) for j, c in enumerate(row)
        }

        found = []

        def search(node, z, word):
            if node.pop(None, None):
                found.append(word)
            c = board.get(z)
            if c in node:
                board[z] = None
                for k in range(4):
                    search(node[c], z + 1j**k, word + c)
                board[z] = c

        for z in board:
            search(root, z, "")

        return found


s = Solution()
grid = [["a", "b", "c"], ["e", "d", "g"], ["b", "h", "i"]]
a = 1 + 2j
words = ["aeb", "abc"]
for p in s.findWords(grid, words):
    print(p)

# ------------------------------------------------------------------------------
# Analysis of the solution proposed by:
# https://leetcode.com/problems/word-search-ii/discuss/59804/27-lines-uses-complex-numbers

# Assemble a tree to observe it below.
root = {}


def f(c, l, node=root, cl=0):
    if cl < l:
        child = {}
        # current node's complex number points to a map of children
        node[c] = child
        # collect all children to the map current node points to
        for k in range(4):
            child[1j**k] = {}
            # Do the same steps above for each child
            f(c + 1j**k, l, child[1j**k], cl + 1)


f(0 + 0j, 2)  # create tree
print(root)  # print the tree


# The summation recurrence
# Current complex number is a sum of previous complex numbers
# F(C) = F(C + 1j**0) + F(C + 1j**1) + F(C + 1j**2) + F(C + 1j**3)
# C + 1j**0
# C + 1j**1
# C + 1j**2
# C + 1j**3
# Such recursive function should always return 0.
# No matter the amount of combinations, the results of powering
# imaginary part has four possible results:
# Where the power is non negative number.
# 1, i, -1, -i
# Because:
# i**0 = 1
# i**1 = i
# i**2 = -1
# i**3 = -i
# (i**2)*(i) = -1 * i = -i
def g(c, m, l=0):
    if l < m:
        return sum(g(c + 1j**k, m, l + 1) for k in range(4))
    return 0


# No matter the level, the sum is always 0.
for j in range(3):
    for k in range(4):
        print(g(1j**k, j))

# Observe the following
# 1j**0 = 1
# 1j**1 = j
# 1j**2 = -1
# 1j**3 = -j
# therefore, the sum is 0
# therefore, no matter the level the recurrence goes, the sum remains 0
# no matter the combination, interesting.

print("\n----\n")
for k in range(3):
    print(1j**k)
