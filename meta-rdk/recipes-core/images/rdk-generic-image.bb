require rdk-oss-image.bb

SUMMARY = "Image with RDK components"

IMAGE_INSTALL += " \
    packagegroup-rdk-generic \
    "

# the next few lines let us create 'chroot' environment inside the main image
#  - we assume that there is a valid image called 'chroot-${CHROOTPKG}-image.bb
#  - we create a dependency on that image, to ensure it gets build
#  - what is in the image is defined in the image .bb file, it can be one or
#    more packages, and we rely on OE to pull in all the RDEPENDS
#  - when creating the rootFS we untar the 'chroot' image in /chroot/${CHROOTPKG}
# TODO: take a list of CHROOTS instead of assuming there is just one.
# TODO: create chrootadd.bbclass to factor all this code in a class.
# TODO: fail in the chroot destination folder already exits ?
## CHROOTPKG='smartmontools'
## CHROOTDIR='chroot'
## do_rootfs[depends] += "chroot-${CHROOTPKG}-image:do_rootfs"
## IMAGE_PREPROCESS_COMMAND += "add_chroot_image; "
##
## # simply create the chroot
## add_chroot_image() {
##     install -d ${IMAGE_ROOTFS}/${CHROOTDIR}/${CHROOTPKG}
##     tar -xzf ${DEPLOY_DIR_IMAGE}/chroot-${CHROOTPKG}-image-${MACHINE}.tar.gz \
##         -C ${IMAGE_ROOTFS}/${CHROOTDIR}/${CHROOTPKG}
## }
##
## EXPORT_FUNCTIONS add_chroot_image
