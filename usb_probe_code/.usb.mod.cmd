savedcmd_/Project/usb_probe_code/usb.mod := printf '%s\n'   usb.o | awk '!x[$$0]++ { print("/Project/usb_probe_code/"$$0) }' > /Project/usb_probe_code/usb.mod
