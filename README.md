Prerequisites
=========
Please read [Default Setup](https://github.com/mehmetalinbay/uclinux/blob/master/default_setup_README.md)

Download Filesystem Files
=========
```
	cd ~/workspace
	git clone https://github.com/vf-tech/filesys.git
```
 
Download BusyBox
=========
```
	cd ~/workspace/filesys
	wget -c http://busybox.net/downloads/busybox-1.22.0.tar.bz2
	tar -jxf busybox-1.22.0.tar.bz2
	ln -s busybox-1.22.0 busybox
```
Compiling
=========
```
	cp config.robutest busybox/.config
```
or
```
	cp busybox_config.malinbay busybox/.config
```
Note: in busybox_config.malinbay mdev command enabled

* Don't forget override "SKIP_STRIP = y" in <Makefile.flags> file for overcoming "stripping error".
```
	cd busybox
	make menuconfig
	make SKIP_STRIP=y install
```
* All compiled files have been seen <_install> directory in the busybox.

Creating RootFS
=========
* create folder "romfs" in filesys directory and put RootFS files in it
```
	cd ~/workspace/filesys
	mkdir romfs
	cp -af busybox/_install/* romfs
	cp -af rootfs/* romfs
```
* (optional) Change console from ttyS2 to ttyS0
* Edit romfs/etc/inittab, 
* change ttyS2 to ttyS0 --> ttyS0::respawn:/bin/login -f root


* Install [genromfs](http://romfs.sourceforge.net/)
```
	sudo apt-get install genromfs
```
* Then execute "genromfs -v -V "ROM Disk" -f romfs.bin -d <your_compiled_busybox_files> 2> romfs.map". It produces your romfs.bin file.
```
	genromfs -v -V "ROM Disk" -f romfs.bin -x placeholder -d romfs 2> romfs.map
```

Application Development
=========
```
	cd ~/workspace/filesys/app
	arm-uclinuxeabi-gcc -o spi_test spi_test.c -mcpu=cortex-m3 -mthumb
	cp spi_test /workspace/filesys/romfs/usr/
```

Then run genromfs, create new romfs.bin & download. 
In uClinux console

```
	/usr/spi_test spidev4.0
```

Console output

```
	response(2): d4 
```

0xD4 is the WHO_AM_I register of GYRO IC.
