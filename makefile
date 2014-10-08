ANDROIDFLAG += -D DEV_ANDROID

nu10:
	make clean
	arm-none-linux-gnueabi-gcc nu10_lcdc_test.c -o u
	arm-none-linux-gnueabi-gcc -D SCENE_CHANGE nu10_lcdc_test.c -o s
	arm-none-linux-gnueabi-gcc -static nu10_lcdc_test.c -o a

nu7:
	make clean
	arm-none-linux-gnueabi-gcc test.c -o u
	arm-none-linux-gnueabi-gcc -static $(ANDROIDFLAG) test.c -o a
	arm-none-linux-gnueabi-gcc -static test.c -o b
	#sz u
	#scp u hangxie@192.168.22.185:/home/hangxie/nfs_fs/nfs_ubuntu/root/xx/

clean:
	-rm a u
