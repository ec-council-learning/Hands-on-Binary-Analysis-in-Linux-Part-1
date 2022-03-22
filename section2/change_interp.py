import os
import stat
import lief

input = "./ls.modified"
output = "{}.interpreter".format(os.path.basename(input))
target = lief.parse(input)
new_interpreter = "/tmp/ld.so"
target.interpreter = new_interpreter
target.write(output)
st = os.stat(output)
os.chmod(output, st.st_mode | stat.S_IEXEC)