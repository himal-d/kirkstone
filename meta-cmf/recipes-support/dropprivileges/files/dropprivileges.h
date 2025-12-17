/*
* If not stated otherwise in this file or this component's LICENSE file the
* following copyright and licenses apply:
*
* Copyright 2017 Liberty Global B.V.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
* Author: Stefan Verkoyen <stefan.verkoyen@androme.be>
*/

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/capability.h>
#include <sys/prctl.h>
#include <grp.h>
#include <pwd.h>

/*
 * drop_root_privileges()
 *  username   - user to drop to
 *  caps, naps - any capabilities that should be set
 *               for example: { CAP_CHOWN, CAP_SYS_ADMIN }
 */

static int drop_root_privileges(const char* username, cap_value_t* caps, unsigned int ncaps)
{
    uid_t real, eff, saved;
    gid_t *groups, *effgroups;
    int ngroups=20, neffgroups=20, nmatchedgroups;
    int i,j;
    struct passwd *pw;
    cap_t capabilities, capabilities_eff;

    groups = (gid_t*)malloc(ngroups * sizeof (gid_t));
    effgroups = (gid_t*)malloc(neffgroups * sizeof (gid_t));

    //fprintf(stderr, "[DEBUG] %s at %d Dropping to user %s with %d caps\n",__FUNCTION__, __LINE__, username, ncaps);

    pw = getpwnam(username);
    if (pw == NULL)
    {
        fprintf(stderr, "[ERROR] %s at %d getpwnam() failed\n",__FUNCTION__, __LINE__);
        return -1;
    }

    if (getgrouplist(pw->pw_name, pw->pw_gid, groups, &ngroups) == -1)
    {
        fprintf(stderr, "[ERROR] %s at %d getgrouplist failed GID (%d)\n",__FUNCTION__, __LINE__, pw->pw_gid);
        return -1;
    }

    if (prctl(PR_SET_KEEPCAPS, 1L) != 0)
    {
        fprintf(stderr, "[ERROR] %s at %d prctl() failed\n",__FUNCTION__, __LINE__);
        return -1;
    }

    if (setgroups(ngroups, groups) != 0)
    {
        fprintf(stderr, "[ERROR] %s at %d setgroups() failed\n",__FUNCTION__, __LINE__);
        return -1;
    }

    if (setresgid(pw->pw_gid, pw->pw_gid, pw->pw_gid) != 0)
    {
        fprintf(stderr, "[ERROR] %s at %d Failed changing GID\n",__FUNCTION__, __LINE__);
        return -1;
    }

    if (setresuid(pw->pw_uid, pw->pw_uid, pw->pw_uid) != 0)
    {
        fprintf(stderr, "[ERROR] %s at %d Failed changing UID\n",__FUNCTION__, __LINE__);
        return -1;
    }

    if (getresuid(&real, &eff, &saved) != 0)
    {
        fprintf(stderr, "[ERROR] %s at %d Failed reading UID\n",__FUNCTION__, __LINE__);
        return -1;
    }

    if (real != pw->pw_uid || eff != pw->pw_uid || saved != pw->pw_uid)
    {
        fprintf(stderr, "[ERROR] %s at %d UID sanity check failed\n",__FUNCTION__, __LINE__);
        return -1;
    }

    if (getresgid(&real, &eff, &saved) != 0)
    {
        fprintf(stderr, "[ERROR] %s at %d Failed reading gid\n",__FUNCTION__, __LINE__);
        return -1;
    }

    if (real != pw->pw_gid || eff != pw->pw_gid || saved != pw->pw_gid)
    {
        fprintf(stderr, "[ERROR] %s at %d GID sanity check failed\n",__FUNCTION__, __LINE__);
        return -1;
    }

    neffgroups = getgroups(neffgroups, effgroups);
    if (neffgroups == -1)
    {
        fprintf(stderr, "[ERROR] %s at %d getgroups() returned -1\n",__FUNCTION__, __LINE__);
        return -1;
    }
    else if (neffgroups != ngroups)
    {
        fprintf(stderr, "[ERROR] %s at %d User groups sanity check failed: mismatch in number of groups. Expected %d but got %d groups.\n",__FUNCTION__, __LINE__, ngroups, neffgroups);
        return -1;
    }

    nmatchedgroups = 0;
    for(i=0;i<neffgroups;i++)
    {
        for(j=0;j<ngroups;j++)
        {
            if (effgroups[i] == groups[j])
            {
                nmatchedgroups++;
                break;
            }
        }
    }
    if (neffgroups != nmatchedgroups)
    {
        fprintf(stderr, "[ERROR] %s at %d User groups sanity check failed: mismatch in groups. Only %d groups matched of %d\n",__FUNCTION__, __LINE__, nmatchedgroups, neffgroups);
        return -1;
    }

    free(groups);
    free(effgroups);

    if ((capabilities = cap_get_proc()) == NULL)
    {
        fprintf(stderr, "[ERROR] %s at %d cap_get_proc() failed\n",__FUNCTION__, __LINE__);
        return -1;
    }

    if (cap_clear(capabilities) != 0)
    {
        fprintf(stderr, "[ERROR] %s at %d cap_clear() failed\n",__FUNCTION__, __LINE__);
        cap_free(capabilities);
        return -1;
    }

    if (ncaps > 0 && caps != NULL) 
    {
        if (cap_set_flag(capabilities, CAP_EFFECTIVE, ncaps, caps, CAP_SET) != 0)
        {
            fprintf(stderr, "[ERROR] %s at %d cap_set_flag() failed\n",__FUNCTION__, __LINE__);
            cap_free(capabilities);
            return -1;
        }

        if (cap_set_flag(capabilities, CAP_PERMITTED, ncaps, caps, CAP_SET) != 0)
        {
            fprintf(stderr, "[ERROR] %s at %d cap_set_flag() failed\n",__FUNCTION__, __LINE__);
            cap_free(capabilities);
            return -1;
        }

        if (cap_set_flag(capabilities, CAP_INHERITABLE, ncaps, caps, CAP_SET) != 0)
        {
            fprintf(stderr, "[ERROR] %s at %d cap_set_flag() failed\n",__FUNCTION__, __LINE__);
            cap_free(capabilities);
            return -1;
        }
    }

    if (cap_set_proc(capabilities) != 0)
    {
        fprintf(stderr, "[ERROR] %s at %d cap_set_proc() failed\n",__FUNCTION__, __LINE__);
        cap_free(capabilities);
        return -1;
    }

    if ((capabilities_eff = cap_get_proc()) == NULL)
    {
        fprintf(stderr, "[ERROR] %s at %d cap_get_proc() failed\n",__FUNCTION__, __LINE__);
        cap_free(capabilities);
        return -1;
    }

    if (cap_compare(capabilities, capabilities_eff) != 0)
    {
        fprintf(stderr, "[ERROR] %s at %d Capabilities sanity check failed!\n",__FUNCTION__, __LINE__);
        cap_free(capabilities);
        cap_free(capabilities_eff);
        return -1;
    }

    if (cap_free(capabilities) != 0)
    {
        fprintf(stderr, "[ERROR] %s at %d cap_free() failed\n",__FUNCTION__, __LINE__);
        cap_free(capabilities_eff);
        return -1;
    }

    if (cap_free(capabilities_eff) != 0)
    {
        fprintf(stderr, "[ERROR] %s at %d cap_free() failed\n",__FUNCTION__, __LINE__);
        return -1;
    }

    if (prctl(PR_SET_KEEPCAPS, 0L) != 0)
    {
        fprintf(stderr, "[ERROR] %s at %d prctl() failed\n",__FUNCTION__, __LINE__);
        return -1;
    }

    //fprintf(stderr, "[DEBUG] %s at %d DONE Dropping to user %s with %d caps\n",__FUNCTION__, __LINE__, username, ncaps);

    return 0;
}
