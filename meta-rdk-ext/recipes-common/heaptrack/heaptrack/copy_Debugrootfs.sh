#!/bin/bash

:' #commenting as of now
for device in /dev/sd*; do
    if ! grep -qs $device /proc/mounts ; then
        echo "Mount the Device"
        mount $device /mnt/usb
    else
        echo "Already Mounted the Device"
    fi
done
'
if [ -b /dev/sda2 ]; then
    echo "Mouting the device"
    mount /dev/sda2 /mnt/usb
fi
cd /tmp/data
if [ ! -d /tmp/data/dbg_rootfs ]; then
    mkdir dbg_rootfs
else
    rm -rf dbg_rootfs
    mkdir dbg_rootfs
fi

cd  dbg_rootfs
rm -rf *

echo "Copying dbg rootfs to /tmp/data/dbg_rootfs"
cp /mnt/usb/*.gz /tmp/data/dbg_rootfs

echo "Done Copying the rootfs.Extracting!!"
tar -xvf *.gz

echo "Extraction Done."

target_directory1="/usr/lib"
target_directory2="/lib"

search_copy_symlinks() {
echo "dir:$1"
if [ -d "$1" ]; then
    echo "Finding symbolic links in '$1':"

    for entry in "$1"/*; do
        if [ -L $entry ]; then
            echo "Symbolic link: $entry"
if [ "$1" == "/usr/lib" ]; then
cp -P $entry /tmp/data/dbg_rootfs/usr/lib/.debug
else
cp -P $entry /tmp/data/dbg_rootfs/lib/.debug
fi
        fi
    done

    echo "Symlink search in '$1' completed."
else
    echo "Error: Directory '$1' not found."
fi

}

search_copy_symlinks "$target_directory1"

search_copy_symlinks "$target_directory2"
