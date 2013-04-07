ANDROIDFLAG += -D DEV_ANDROID

lcdc_test:
	make clean
	arm-none-linux-gnueabi-gcc test.c -o u
	arm-none-linux-gnueabi-gcc -static $(ANDROIDFLAG) test.c -o a
	sz u
	#scp u hangxie@192.168.22.185:/home/hangxie/nfs_fs/nfs_ubuntu/root/xx/

clean:
	-rm a u
