Folder Structure
=========
* workspace
- uclinux
- filesys
- toolchain

```
	cd home/$USER
	mkdir workspace
	cd workspace
```
Dependicies
=========
The builder requires that various tools and packages be available for use in
the build procedure:
```
	sudo apt-get install libncurses-dev libglib2.0-dev libfdt-dev libpixman-1-dev zlib1g-dev git
```
Setup Toolchain
=========
* Set ARM/uClinux Toolchain:
  - Download [arm-2010q1-189-arm-uclinuxeabi-i686-pc-linux-gnu.tar.bz2](https://sourcery.mentor.com/public/gnu_toolchain/arm-uclinuxeabi/arm-2010q1-189-arm-uclinuxeabi-i686-pc-linux-gnu.tar.bz2) from Mentor Graphics
  - only arm-2010q1 is known to work; don't use SourceryG++ arm-2011.03
```
	cd ~/workspace
	mkdir toolchain
	cd toolchain
	wget https://sourcery.mentor.com/public/gnu_toolchain/arm-uclinuxeabi/arm-2010q1-189-arm-uclinuxeabi-i686-pc-linux-gnu.tar.bz2
	tar jxvf arm-2010q1-189-arm-uclinuxeabi-i686-pc-linux-gnu.tar.bz2
```
* To set toolchain path permanently
```
	cd (goto home/$USER directory)
	gedit .bashrc
```
* add following lines to bashrc
```
	PATH=~/workspace/toolchain/arm-2010q1/bin:$PATH (beware of your PATH)
	export PATH
```
* Restart Ubuntu
* Check toolchain PATH
 
Download BusyBox
=========
```
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
	cd filesys
	mkdir romfs
	cp -af busybox/_install/* romfs
	cp -af rootfs/* romfs
```
* (optional) Change console from ttyS2 to ttyS0
* Edit romfs/etc/inittab, 
* change ttyS2 to ttyS0 --> ttyS0::respawn:/bin/login -f root

* Then execute "genromfs -v -V "ROM Disk" -f romfs.bin -d <your_compiled_busybox_files> 2> romfs.map". It produces your romfs.bin file.
* [genromfs](http://romfs.sourceforge.net/)
```
    sudo apt-get install genromfs
```
```
	genromfs -v -V "ROM Disk" -f romfs.bin -x placeholder -d romfs 2> romfs.map
```
