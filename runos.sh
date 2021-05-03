#!/usr/bin/bash
cd ~/edk2
source edksetup.sh
build
/home/nao/osbook/devenv/run_qemu.sh /home/nao/edk2/Build/MikanLoaderX64/DEBUG_CLANG38/X64/Loader.efi /home/nao/workspace/mikanos/kernel/kernel.elf
