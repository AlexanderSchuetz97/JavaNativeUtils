#include <sys/utsname.h>
#include "../common/jni/eu_aschuetz_nativeutils_impl_JNIPosixNativeUtil.h"
#include "../common/common.h"
#include "string.h"

/*
 * Class:     eu_aschuetz_nativeutils_impl_JNILinuxNativeUtil
 * Method:    uname
 * Signature: ()Leu/aschuetz/nativeutils/api/structs/Utsname;
 */
JNIEXPORT jobject JNICALL Java_eu_aschuetz_nativeutils_impl_JNIPosixNativeUtil_uname
        (JNIEnv * env, jobject inst) {

    struct utsname uts;
    memset(&uts, 0, sizeof(struct utsname));
    uname(&uts);
    uts.machine[sizeof(uts.machine)-1] = 0;
    uts.nodename[sizeof(uts.nodename)-1] = 0;
    uts.release[sizeof(uts.release)-1] = 0;
    uts.sysname[sizeof(uts.sysname)-1] = 0;
    uts.version[sizeof(uts.version)-1] = 0;

    jobject utsname = jnew_Utsname(env);
    if (utsname == NULL) {
        return NULL;
    }

    if (!jsetC_Utsname_sysname(env, utsname, (char*) &uts.sysname)) {
        return NULL;
    }

    if (!jsetC_Utsname_machine(env, utsname, (char*) &uts.machine)) {
        return NULL;
    }

    if (!jsetC_Utsname_nodename(env, utsname, (char*) &uts.nodename)) {
        return NULL;
    }

    if (!jsetC_Utsname_release(env, utsname, (char*) &uts.release)) {
        return NULL;
    }

    if (!jsetC_Utsname_version(env, utsname, (char*) &uts.version)) {
        return NULL;
    }

    return utsname;
}