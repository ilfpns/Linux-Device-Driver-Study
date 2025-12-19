savedcmd_/DriverStudy/day4_gpio/read_write.mod := printf '%s\n'   read_write.o | awk '!x[$$0]++ { print("/DriverStudy/day4_gpio/"$$0) }' > /DriverStudy/day4_gpio/read_write.mod
