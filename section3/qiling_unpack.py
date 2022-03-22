import sys
qiling_path = "/root/qiling"
sys.path.insert(0, qiling_path)

from qiling import Qiling
from qiling.const import QL_VERBOSE
import lief

def my_syscall_munmap(ql, addr, length):
    # ql.mem.show_mapinfo()
    start_addr = ql.mem.map_info[1][0]
    end_addr = ql.mem.map_info[1][1] - ql.mem.map_info[1][0]
    elf = lief.parse(ql.mem.read(start_addr, end_addr))
    # ql.log.info(str(hex(elf.entrypoint)))
    with open("./simple_keygenme.unpacked", "wb") as f:
        for segment in elf.segments:
            if segment.type != lief.ELF.SEGMENT_TYPES.LOAD:
                continue
            f.seek(segment.file_offset)
            f.write(ql.mem.read(
                segment.virtual_address, segment.physical_size
            ))
    ql.emu_stop()

def my_sandbox(path, rootfs):
    ql = Qiling(path, rootfs)
    ql.add_fs_mapper("/proc/self/exe", path[0])
    ql.set_syscall("munmap", my_syscall_munmap)
    ql.run()

if __name__ == "__main__":
    my_sandbox(
        ["./simple_keygenme.upx"],
        qiling_path+"/examples/rootfs/x8664_linux"
    )