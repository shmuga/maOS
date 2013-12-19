export C_INCLUDE_PATH=$C_INCLUDE_PATH:source/headers
export LD_PRELOAD=/usr/lib/x86_64-linux-gnu/libXpm.so.4

gcc_flags="-pedantic -pipe -Werror -std=c99 -march=i386 -m32 -fno-asynchronous-unwind-tables -fno-stack-protector -nostdinc -ffreestanding"

nasm -f elf32 source/bootloader/loader.s -o build/bootloader/loader.o
gcc $gcc_flags -c source/kernel/*.c  -o build/kernel/kernel.o

ld -T link.ld -melf_i386 -Map logs/kernel.map build/bootloader/*.o build/kernel/*.o -o iso/boot/kernel.elf

cp grub/stage2_eltorito iso/boot/grub/
cp grub/menu.lst iso/boot/grub/

genisoimage -R                              \
            -b boot/grub/stage2_eltorito    \
            -no-emul-boot                   \
            -boot-load-size 400               \
            -A os                           \
            -input-charset utf8             \
            -quiet                          \
            -boot-info-table                \
            -o disk/os.iso                  \
            iso