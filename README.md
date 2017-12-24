Download
=========
wget -c http://busybox.net/downloads/busybox-1.22.0.tar.bz2

tar -jxf busybox-1.22.0.tar.bz2

ln -s busybox-1.22.0 busybox

Compiling
=========

cp config.robutest busybox/.config

cd busybox

* Don't forget override "SKIP_STRIP = y" in <Makefile.flags> file for overcoming "stripping error".

make menuconfig

make SKIP_STRIP=y install

* All compiled files have been seen <_install> directory in the busybox.

Creating RootFS
=========
* create folder "romfs" in filesys directory and put RootFS files in it

cd filesys

mkdir romfs

cp -af busybox/_install/* romfs

cp -af rootfs/* romfs

* (optional) Change console from ttyS2 to ttyS0
* Edit romfs/etc/inittab, 
* change ttyS2 to ttyS0 --> ttyS0::respawn:/bin/login -f root

* Then execute "genromfs -v -V "ROM Disk" -f romfs.bin -d <your_compiled_busybox_files> 2> romfs.map". It produces your romfs.bin file.

genromfs -v -V "ROM Disk" -f romfs.bin -x placeholder -d romfs 2> romfs.map

