obj-m += cmpe283-1.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean: 
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

test:
	# We put a — in front of the rmmod command to tell make to ignore
	# an error in case the module isnt loaded
	-sudo rmmod cmpe283-1
	# Clear the kernel log without echo
	sudo dmesg -C
	# Insert the module
	sudo insmod ./cmpe283-1.ko
	# Display the kernel log
	sudo dmesg

unload:
	-sudo rmmod cmpe283-1
