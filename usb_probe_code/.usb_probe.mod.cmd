savedcmd_/Project/usb_probe_code/usb_probe.mod := printf '%s\n'   main.o usb.o | awk '!x[$$0]++ { print("/Project/usb_probe_code/"$$0) }' > /Project/usb_probe_code/usb_probe.mod
