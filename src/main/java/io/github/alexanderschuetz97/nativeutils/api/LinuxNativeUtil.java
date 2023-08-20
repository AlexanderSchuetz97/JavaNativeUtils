import java.io.*;
    @Deprecated
    /**
     * Returns a input stream that will read bytes from the filedescriptor by calling the read method.
     * This method exists for convinience.
     * Closing the returned InputStream will only call the close() method if the close flag is set to true.
     * Otherwise, closeing the stream is a noop.
     */
    InputStream inputStreamFromFD(int fd, boolean close);

    /**
     * Returns a output stream that will write bytes to the filedescriptor by calling the write method.
     * This method exists for convinience.
     * Closing the returned OutputStream will only call the close() method if the close flag is set to true.
     * Otherwise, closeing the stream is a noop.
     */
    OutputStream outputStreamFromFD(int fd, boolean close);


    void fsync(int fd) throws InvalidFileDescriptorException, IOException, ReadOnlyFileSystemException;

    @Deprecated
    @Deprecated
    @Deprecated
    Statvfs statvfs(String path) throws AccessDeniedException, IOException, FileSystemLoopException, FileNotFoundException, UnknownNativeErrorException;
    void fchmod(int fd, int mode);

    void chown(String path, int uid, int gid);

    void fchown(int fd, int uid, int gid);

    void lchown(String path, int uid, int gid);

    long sem_open(String name, int oflags) throws AccessDeniedException, QuotaExceededException, FileNotFoundException, FileAlreadyExistsException, UnknownNativeErrorException;

    long sem_open(String name, int oflags, int mode, int value) throws AccessDeniedException, QuotaExceededException, FileNotFoundException, FileAlreadyExistsException, UnknownNativeErrorException;

    void sem_close(long sem) throws UnknownNativeErrorException;

    void sem_unlink(String name) throws AccessDeniedException, FileNotFoundException, UnknownNativeErrorException;

    /**
     * Returns the size of sem_t in bytes.
     * This value changes depending on CPU and JVM architecture.
     */
    int sem_t_size();

    /**
     * Initializes an unnamed semaphore.
     *
     * @param sem ptr to allocated memory. This memory must be able to hold sem_t_size bytes.
     * @param interprocess should the semaphore be interprocess? (ptr must reside in shared memory)
     * @param value initial value of the semaphore.
     */
    void sem_init(long sem, boolean interprocess, int value) throws UnknownNativeErrorException;

    void sem_destroy(long sem) throws UnknownNativeErrorException;

    void sem_post(long sem) throws UnknownNativeErrorException;

    void sem_wait(long sem) throws UnknownNativeErrorException;

    int sem_getvalue(long sem) throws UnknownNativeErrorException;

    boolean sem_trywait(long sem) throws UnknownNativeErrorException;

    boolean sem_timedwait(long sem, long timeoutInMillis) throws UnknownNativeErrorException;

    int shm_open(String name, int oflag, int mode) throws FileAlreadyExistsException, FileNotFoundException, UnknownNativeErrorException, AccessDeniedException, QuotaExceededException;

    void shm_unlink(String name) throws FileNotFoundException, AccessDeniedException, UnknownNativeErrorException;

    void ftruncate(int fd, long len);

    void truncate(String name, long len);

    void mkfifo(String name, int mode) throws AccessDeniedException, QuotaExceededException, FileAlreadyExistsException, FileNotFoundException, NotDirectoryException, ReadOnlyFileSystemException;







