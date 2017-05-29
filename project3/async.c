#include<stdio.h>
#include<stdlib.h>
#include<aio.h>
#include<errno.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>

ssize_t read_wrap(int fd, void * buf, size_t count) {
      // your code here!
   struct aiocb* tmp = malloc(sizeof(struct aiocb));
   tmp->aio_fildes = fd;
   tmp->aio_buf = buf;
   tmp->aio_nbytes = count;
   tmp->aio_sigevent.sigev_notify = SIGEV_NONE;
   off_t offset = lseek(fd, 0, SEEK_CUR);
   tmp->aio_offset  =  offset;
   int s = aio_read(tmp);
   while (aio_error(tmp) == EINPROGRESS) {
      yield();
   }
   lseek(fd, offset+count, SEEK_SET);
   return aio_return(tmp);
}
   
