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
  _read()_ returns 0.
