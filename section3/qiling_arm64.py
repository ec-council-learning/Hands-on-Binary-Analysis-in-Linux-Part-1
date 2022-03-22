import sys
qiling_path = "/root/qiling"
sys.path.insert(0, qiling_path)

from qiling import Qiling
from qiling.const import QL_VERBOSE

def my_sandbox(path, rootfs):
    # ql = Qiling(path, rootfs, verbose=QL_VERBOSE.OFF)
    ql = Qiling(path, rootfs)
    ql.filter = "^open"
    ql.run()

if __name__ == "__main__":
    my_sandbox(
        [qiling_path+"/examples/rootfs/arm64_linux/bin/arm64_hello"],
        qiling_path+"/examples/rootfs/arm64_linux"
    )