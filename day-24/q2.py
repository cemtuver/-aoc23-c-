# Unfortunately, it wasn't possible to solve this problem using C++.
# The equations are too complex and the C++ solver is too slow.
# Instead, I use sympy to solve the equations.

import sympy

hails = []
lines = open("input.txt")

for line in lines:
    parts = line.split(" @ ")
    hail = tuple(map(int, parts[0].split(",") + parts[1].split(",")))
    hails.append(hail)

equations = []
rx, ry, rz, rvx, rvy, rvz = sympy.symbols("rx, ry, rz, rvx, rvy, rvz")

for x, y, z, vx, vy, vz in hails:
    equations.append((rx - x) * (vy - rvy) - (ry - y) * (vx - rvx))
    equations.append((ry - y) * (vz - rvz) - (rz - z) * (vy - rvy))

answer = sympy.solve(equations)[0]
result = answer[rx] + answer[ry] + answer[rz]

print(result)
