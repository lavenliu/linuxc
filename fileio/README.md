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

Reading from a file read()
--------------------------

`
char buffer[MAX_READ+1];  
ssize_t numRead;   
numRead = read(STDIN_FILENO, buffer, MAX_READ);   
if (numRead == -1)   
   errExit("read");   
buffer[numRead] = '\0';   
printf("The input data was: %s\n", buffer);
` 

Writing to a file: write()
--------------------------

The _write()_ system call writes data to an open file.

Closing a file: close()
-----------------------

When a process terminates, all of its open file descriptors are
automatically closed.

It is usually good practice to close unneeded file descriptors
explicitly, since this makes our code more readable and reliable in
the face of subsequent modifications.  Furthermore, file descriptors
are a consumable resource, so failure to close a file descriptor could
result in a process running out of descriptors. This is a particularly
important issue when writing long-lived programs that deal with
multiple files, such as shells or network servers.

Changing the file offset: lseek()
---------------------------------

For each open file, the kernel records a file offset, sometimes also
called the readwrite offset or pointer. This is the location in the
file at which the next read() or write() will commence. The file
offset is expressed as an ordinal byte position relative to the start
of the file. The first byte of the file is at offset 0.

The file offset is set to point to the start of the file when the file
is opened and is automatically adjusted by each subsequent call to
read() or write() so that it points to the next byte of the file after
the byte(s) just read or written. Thus, successive read() and write()
calls progress sequentially through a file.

The lseek() system call adjusts the file offset of the open file
referred to by the file descriptor fd, according to the values
specified in offset and whence.

