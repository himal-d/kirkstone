inherit extrausers
#-------------------------------------------------------------------------------
# Common groups
#-------------------------------------------------------------------------------
EXTRA_USERS_PARAMS += "\
    groupadd -g 950 non-root      ; \
"
#-------------------------------------------------------------------------------
# Common users and groups for OENMW
# For each user also the group with the same name and id is created.
#-------------------------------------------------------------------------------
EXTRA_USERS_PARAMS += "\
    useradd -u 950 -g non-root -M -r -s /bin/sh  non-root ; \
" 
