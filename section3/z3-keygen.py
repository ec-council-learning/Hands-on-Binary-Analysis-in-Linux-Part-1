from z3 import *

input = [ BitVec('input%s' % i, 8) for i in range(14)]
password = [ BitVec('password%s' % i, 8) for i in range(14)]

s = Solver()

for index in range(14):
    s.add(
        Or(
            And(input[index] >= ord('0'), input[index] <= ord('9')),
            And(input[index] >= ord('a'), input[index] <= ord('z')),
            And(input[index] >= ord('A'), input[index] <= ord('Z'))
        )
    )
for index in range(14):
    s.add(password[index] == (input[index] ^ 0x44) - 5)


s.add(BVAddNoOverflow(password[0] , password[12], False))
s.add(BVAddNoOverflow(password[1] , password[2], False))
s.add(BVAddNoOverflow(password[3] , password[5], False))
s.add(BVAddNoOverflow((password[8] - password[10]) , (password[11] - password[9]), False))
s.add(BVAddNoOverflow((password[7] - password[6]) , (password[12] - password[13]), False))

s.add(BVSubNoUnderflow(password[7] , password[6], False))
s.add(BVSubNoUnderflow(password[12] , password[13], False))
s.add(BVSubNoUnderflow(password[8] , password[10], False))
s.add(BVSubNoUnderflow(password[11] , password[9], False))


s.add(password[0] + password[12] == 0x43)
s.add(password[1] + password[2] == 148)
s.add(password[5] + password[3] - password[4] == 126)
s.add((password[7] - password[6]) + (password[12] - password[13]) == 114)
s.add((password[8] - password[10]) + (password[11] - password[9]) == 65)


# print(s.check())

for index in range(10):
    if s.check() == sat:
        m = s.model()
        print(
            ''.join(
                chr(m[input[ind]].as_long()) for ind in range(14))
            )