ANDROIDFLAG += -D DEV_ANDROID

lcdc_test:
	make clean
	arm-none-linux-gnueabi-gcc test.c -o u
	arm-none-linux-gnueabi-gcc -static $(ANDROIDFLAG) test.c -o a

clean:
	-rm a u
