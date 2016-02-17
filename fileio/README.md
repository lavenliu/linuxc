Overview
========

All system calls for performing I/O refer to open files using a _file
descriptor_, a(usually small) nonegative integer. File descriptors are
used to refer to all types of open files, including pipes, FIFOs,
sockets, terminals, devices, and regular files. Each process has its
own set of file descriptors.

The following are the four key system calls for performing file I/O
(programming languages and software packages typically employ these
calls only indirectly, via I/O libraries):

* fd = open(pathname, flags, mode) opens the file identified by
  _pathname_, returning a file descriptor used to refer to the open
  file in subsequent calls. If the file doesn't exist, open() man
  create it, depending on the settings of the flags bitmask
  argument. The _flags_ argument also specifies whether the file is to
  be opened for reading, writing, or both. The _mode_ argument
  specifies the permissions to be placed on the file if it is created
  by this call. If the _open()_ call is not being used to create a
  file, this argument is ignored and can be omitted.  
* _numread = read(fd, buffer, count)_ reads at most _count_ bytes from
  the open file referred to by _fd_ and stores them in _buffer_. The
  _read()_ call returns the number of bytes actually read. If no
  futher bytes could be read (i.e., end-of-file was encountered),
  _read()_ returns 0.(小白的理解：读多少, 返多少; 读到末尾返回0)
* _numwritten = write(fd, buffer, count)_ writes up to _count_ bytes
  from _buffer_ to the open file referred to by _fd_. The _write()_
  call returns the nubmer of bytes actually written, which may be less
  than _count_.(小白的理解：写多少, 返多少)
* _status = close(fd)_ is called after all I/O has been completed, in
  order to release the file descriptor _fd_ and its associated kernel
  resources.

`
    char buffer[MAX_READ+1];  
    ssize_t numRead;  
    numRead = read(STDIN_FILENO, buffer, MAX_READ);  
    if (numRead == -1)  
       errExit("read");  
    buffer[numRead] = '\0';  
    printf("The input data was: %s\n", buffer);
`
`   char buffer[MAX_READ+1];
    ssize_t numRead; 
    numRead = read(STDIN_FILENO, buffer, MAX_READ); 
    if (numRead == -1) 
       errExit("read"); 
    buffer[numRead] = '\0'; 
    printf("The input data was: %s\n", buffer);` 
