# change B to the path to BareMetal-OS
B=../BareMetal-OS
CFLAGS=-g -fno-builtin -funsigned-char -fno-unwind-tables -Wno-parentheses -Wno-incompatible-pointer-types \
       -Wfatal-errors -nostdlib -mno-red-zone -mcmodel=large -fomit-frame-pointer -I$B/src/BareMetal/api
LDFLAGS=-z max-page-size=0x1000 -z noexecstack
img=$B/sys/baremetal_os.img
b=init
app=$B/sys/$b.app

all:$(img)
pf/pf.h:
	git clone https://github.com/kparc/pf.git
$b.o:pf/pf.h
$(img):$b.o
	$(LD) $(LDFLAGS) $b.o -o $b
	objcopy -O binary $b $(app)
	cp $b.c $b.o $B/sys
	cd $B && ./baremetal.sh $b.app $b.c $b.o # init with two other random files for BMFS
bochs:$(img)
	bochs -qf /dev/null -rc bochsrc boot:disk ata0-master:type=disk,path=$(img)
qemu:$(img)
	qemu-system-x86_64 -serial stdio -m 256 -drive file=$(img),format=raw
disasm:
	objdump -drwC -Mintel -S $b | less
clean:
	rm -rf $b *.o $(img) $(app)
