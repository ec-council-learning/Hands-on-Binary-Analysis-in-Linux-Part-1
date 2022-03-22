# x = int(argv[0])
# y = int(argv[1])
# int z = 3 + x ;
# int k = 5;
# if ( k < z ){
#     if ( z > y ){
#         foo(x, y, z, k);
#     } else {
#         bar(x, y, z);
#     }
# }

from z3 import *

x = Int("x")
y = Int("y")
z = 3+x
k = 5

s = Solver()

s.add(k < z)
s.push()
s.add( z > y)
print("z > Y status is " + str(s.check()))
print(s.model())
s.pop()
print("-----------------------")
s.add(z <= y)
print("z <= Y status is " + str(s.check()))
print(s.model())