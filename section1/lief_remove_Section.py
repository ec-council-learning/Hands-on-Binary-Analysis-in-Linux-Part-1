import lief

target = lief.parse("/bin/ls")

header = target.header
header.section_header_offset = 0
header.numberof_sections = 0

target.write("ls.modified")