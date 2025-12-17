#To build secure containers
def get_lxc_classes(d):
    if "lxcsecure" in d.getVar('MACHINEOVERRIDES', True):
        #Do not alter the order of items in the below string
        #These resolve to functions that are sequentially executed
        return "extrausers  image_container_generator add_container"
    else:
        return ""

inherit ${@get_lxc_classes(d)}

IMAGE_INSTALL_append_lxcsecure = " packagegroup-lxc-secure-containers "

