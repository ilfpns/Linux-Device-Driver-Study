savedcmd_/DriverStudy/day1/day1_module.mod := printf '%s\n'   day1_module.o | awk '!x[$$0]++ { print("/DriverStudy/day1/"$$0) }' > /DriverStudy/day1/day1_module.mod
