savedcmd_/DriverStudy/day3/read_write.mod := printf '%s\n'   read_write.o | awk '!x[$$0]++ { print("/DriverStudy/day3/"$$0) }' > /DriverStudy/day3/read_write.mod
