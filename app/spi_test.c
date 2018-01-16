/*
* Sample application that makes use of the SPIDEV interface
* to access an SPI slave device. Specifically, this sample
* reads a Device ID of a JEDEC-compliant SPI Flash device.
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv)
{
/*
* This assumes that a 'mdev -s' has been run to create
* /dev/spidev* devices after the kernel bootstrap.
* First number is the "bus" (SPI contoller id), second number
* is the "chip select" of the specific SPI slave
* ...
* char *name = "/dev/spidev1.1";
*/
	char *name;
	int fd;
	struct spi_ioc_transfer xfer[2];
	unsigned char buf[32], *bp;
	int len, status;

	name = argv[1];
	fd = open(name, O_RDWR);
	if (fd < 0) {
		perror("open");
		return 1;
	}

	memset(xfer, 0, sizeof xfer);
	memset(buf, 0, sizeof buf);
	len = sizeof buf;

	/*
	* Send a GetID command
	*/
	buf[0] = 0x8f;
	len = 1;
	xfer[0].tx_buf = (unsigned long)buf;
	xfer[0].len = 1;
	
	xfer[1].rx_buf = (unsigned long) buf;
	xfer[1].len = 1;
	
	status = ioctl(fd, SPI_IOC_MESSAGE(2), xfer);
	if (status < 0) {
		perror("SPI_IOC_MESSAGE");
		return;
	}
	printf("response(%d): ", status);
	for (bp = buf; len; len--)
		printf("%02x ", *bp++);
	printf("\n");
}
