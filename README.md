# rtl88x2bu
rtl88x2bu driver


# How to install on linux.<br />
Unplug the Wireless device <br />
git clone https://github.com/shonber/rtl88x2bu.git<br />
cd rtl88x2bu<br /><br />
VER=$(sed -n 's/\PACKAGE_VERSION="\(.*\)"/\1/p' dkms.conf)<br />
sudo rsync -rvhP ./ /usr/src/rtl88x2bu-${VER}<br />
sudo dkms add -m rtl88x2bu -v ${VER}<br />
sudo dkms build -m rtl88x2bu -v ${VER}<br />
sudo dkms install -m rtl88x2bu -v ${VER}<br />
sudo modprobe 88x2bu<br /><br />
After you have done all of the steps plug the device back<br />
