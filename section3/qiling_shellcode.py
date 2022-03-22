import sys
qiling_path = "/root/qiling"
sys.path.insert(0, qiling_path)
from binascii import unhexlify

from qiling import Qiling
from qiling.const import QL_VERBOSE

def my_sandbox(shellcode):
    ql = Qiling(code=shellcode, archtype="x8664", ostype="linux" ,verbose=QL_VERBOSE.DEBUG)
    ql.run()

if __name__ == "__main__":
    shellcode = unhexlify("31c048bbd19d9691d08c97ff48f7db53545f995257545eb03b0f05")
    my_sandbox(shellcode)