//THIS FILE IS MACHINE GENERATED, DO NOT EDIT
#include "posix_const_provider.h"
#include "../common/jnigenerator.h"
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pthread.h>
#include <net/if.h>

void jfetchconst_DefaultPosixConstProvider(JNIEnv * env, jobject instance) {
   jset_DefaultPosixConstProvider_O_ACCMODE(env, instance, (jint) O_ACCMODE);
   jset_DefaultPosixConstProvider_O_RDONLY(env, instance, (jint) O_RDONLY);
   jset_DefaultPosixConstProvider_O_WRONLY(env, instance, (jint) O_WRONLY);
   jset_DefaultPosixConstProvider_O_RDWR(env, instance, (jint) O_RDWR);
   jset_DefaultPosixConstProvider_O_CREAT(env, instance, (jint) O_CREAT);
   jset_DefaultPosixConstProvider_O_EXCL(env, instance, (jint) O_EXCL);
   jset_DefaultPosixConstProvider_O_NOCTTY(env, instance, (jint) O_NOCTTY);
   jset_DefaultPosixConstProvider_O_TRUNC(env, instance, (jint) O_TRUNC);
   jset_DefaultPosixConstProvider_O_APPEND(env, instance, (jint) O_APPEND);
   jset_DefaultPosixConstProvider_O_NONBLOCK(env, instance, (jint) O_NONBLOCK);
   jset_DefaultPosixConstProvider_O_NDELAY(env, instance, (jint) O_NDELAY);
   jset_DefaultPosixConstProvider_O_SYNC(env, instance, (jint) O_SYNC);
   jset_DefaultPosixConstProvider_O_ASYNC(env, instance, (jint) O_ASYNC);
   jset_DefaultPosixConstProvider_O_DIRECTORY(env, instance, (jint) O_DIRECTORY);
   jset_DefaultPosixConstProvider_O_NOFOLLOW(env, instance, (jint) O_NOFOLLOW);
   jset_DefaultPosixConstProvider_O_CLOEXEC(env, instance, (jint) O_CLOEXEC);
   jset_DefaultPosixConstProvider_O_DSYNC(env, instance, (jint) O_DSYNC);
   jset_DefaultPosixConstProvider_S_IRUSR(env, instance, (jint) S_IRUSR);
   jset_DefaultPosixConstProvider_S_IWUSR(env, instance, (jint) S_IWUSR);
   jset_DefaultPosixConstProvider_S_IXUSR(env, instance, (jint) S_IXUSR);
   jset_DefaultPosixConstProvider_S_IRGRP(env, instance, (jint) S_IRGRP);
   jset_DefaultPosixConstProvider_S_IWGRP(env, instance, (jint) S_IWGRP);
   jset_DefaultPosixConstProvider_S_IXGRP(env, instance, (jint) S_IXGRP);
   jset_DefaultPosixConstProvider_S_IROTH(env, instance, (jint) S_IROTH);
   jset_DefaultPosixConstProvider_S_IWOTH(env, instance, (jint) S_IWOTH);
   jset_DefaultPosixConstProvider_S_IXOTH(env, instance, (jint) S_IXOTH);
   jset_DefaultPosixConstProvider_S_IRWXU(env, instance, (jint) S_IRWXU);
   jset_DefaultPosixConstProvider_S_IRWXG(env, instance, (jint) S_IRWXG);
   jset_DefaultPosixConstProvider_S_IRWXO(env, instance, (jint) S_IRWXO);
   jset_DefaultPosixConstProvider_MAP_SHARED(env, instance, (jint) MAP_SHARED);
   jset_DefaultPosixConstProvider_MAP_PRIVATE(env, instance, (jint) MAP_PRIVATE);
}
