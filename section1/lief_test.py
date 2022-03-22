import lief

target = lief.parse("/bin/ls")

# print(hex(target.entrypoint))
header = target.header
header.entrypoint = 0x123
header.machine_type = lief.ELF.ARCH.AARCH64

target.write("ls.modified")