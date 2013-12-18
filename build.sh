nasm -f elf32 source/bootloader/loader.s -o bootloader/loader.o
ld -T link.ld -melf_i386 bootloader/loader.o -o iso/boot/kernel.elf

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