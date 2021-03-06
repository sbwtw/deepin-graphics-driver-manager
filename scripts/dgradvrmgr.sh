#!/bin/bash

/bin/dmesg --console-off 
/bin/plymouth quit 

dialog --title "Deepin Graphics Driver Manager - Installer" --yesno "\nSure to start install driver?" 6 50

if [ $? != 0 ]; then
	exit 0
fi

bash -x /usr/bin/deepin-graphics-driver-installer.sh
rm -f /usr/bin/deepin-graphics-driver-installer.sh
/usr/bin/xinit /usr/bin/gltest
