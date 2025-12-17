python do_git_tag_components() {

    import os
    import subprocess

    def runCommand(cmd_list, path):
        if not os.path.lexists(path):
            return None, RUNCOMMAND_BAD_PATH
        proc = subprocess.Popen(cmd_list,
                                stdout=subprocess.PIPE, cwd=path)
        out, err = proc.communicate()
        return_code = proc.returncode
        return out, return_code

    def check_git_dir(path):
        cmd = ["git", "rev-parse", "--is-inside-git-dir"]
        out, return_code = runCommand(cmd, path)
        return out

    def check_git_worktree(path):
        cmd = ["git", "rev-parse", "--is-inside-work-tree"]
        out, return_code = runCommand(cmd, path)
        return out

    def get_remotes(path):
        cmd = ["git", "remote", "-v"]
        out, return_code = runCommand(cmd, path)
        return out

    def create_tag(path, tag):
        cmd = ["git", "tag", tag]
        out, return_code = runCommand(cmd, path)
        return out

    def push_tag(path, tag):
        cmd = ["git", "push", "origin", tag]
        out, return_code = runCommand(cmd, path)
        return out

    def create_and_push_tags(path, name, tag, push):
        bb.plain("NOTE: Tagging component %s with %s" % (name, tag))
        bb.note("in source directory %s\n" % path)
        createdTag = create_tag(path, tag)
        bb.note("Created Tag %s\n" % createdTag)
        if push == "True":
            pushedTag = push_tag(path, tag)
            bb.note("Pushed Tag %s\n" % pushedTag)
        else:
            bb.plain("NOTE: DRYRUN, tag not pushed")

    name = d.getVar('PN', True)
    workdir = d.getVar('S', True)
    gitTag = d.getVar('GIT_TAG', True)
    pushTag = d.getVar('PUSH_TAG', True)

    # Check git tag has been specified and WORKDIR exists
    if gitTag and pushTag and os.path.isdir(workdir):

        # Try to find all the .git subdirectories recursively
        subdirs = [x[0] for x in os.walk(workdir)]
        found = False
        for subdir in subdirs:
            dirName = os.path.basename(subdir)
            if dirName == ".git":

                # Check that the component is a git component
                if check_git_dir(subdir):
                    create_and_push_tags(subdir, name, gitTag, pushTag)
                    found = True

        if found == False:
            # Check that the component is a git component
            if check_git_worktree(subdir):
                create_and_push_tags(subdir, name, gitTag, pushTag)
                found = True
    else:
        bb.warn("Git TAG not specified OR no WORKDIR")
}

addtask git_tag_components after do_unpack
