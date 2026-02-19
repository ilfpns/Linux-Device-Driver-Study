savedcmd_/DriverStudy/day2/dev_nr.mod := printf '%s\n'   dev_nr.o | awk '!x[$$0]++ { print("/DriverStudy/day2/"$$0) }' > /DriverStudy/day2/dev_nr.mod
