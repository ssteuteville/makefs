#include "parameters.h"

#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <fuse.h>
#include <libgen.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/xattr.h>

int makefs_getattr(const char *path, struct stat *statbuf)
{
	int retval = 0;
	printf("Entered getattr\n");
	retval = lstat(path, statbuf);

	return retval;
}

int makefs_readlink(const char *path, char *link, size_t size)
{
	printf("Entered readlink");
	int retval = 0;
	retval = readlink(path, link, size -1);
	if(retval < 0)
		return EXIT_FAILURE;
	else
	{
		link[retval] = "\0";
		retval = 0;
	}
	return retval;
}

int makefs_mknod(const char *path, mode_t mode, dev_t dev)
{
	printf("Entered mknod");
	int retval = 0;
	retval = mknod(path, mode, dev);
	return retval;	
}

int makefs_mkdir(const char *path, mode_t mode)
{
	printf("Entered mkdir");
	int retval = 0;
	retval = mkdir(path, mode);
	return retval;
	
}

int makefs_unlink(const char *path)
{
	printf("Entered unlink");
	int retval = 0;
	retval = unlink(path);
	return retval;
}

int makefs_rmdir(const char *path)
{
	printf("Entered rmdir");
	int retval = 0;
	retval = rmdir(path);
	return retval;
}

int makefs_symlink(const char *path, const char *link)
{
	printf("Entered symlink");
	int retval = 0;
	retval = symlink(path, link);
	return retval;
}

int makefs_rename(const char *path, const char *newpath)
{
	printf("Entered rename");
	int retval = 0;
	retval = rename(path, newpath);
	return retval;
}

int makefs_link(const char *path, const char *newpath)
{
	printf("Entered link");
	int retval = 0;
	retval = link(path, newpath);
	return retval;
}

int makefs_chmod(const char *path, mode_t mode)
{
	printf("Entered chmod");
	int retval = 0;
	retval = chmod(path, mode);
	return retval;
}

int makefs_chown(const char *path, uid_t uid, gid_t gid)
{
	printf("Entered chown");
	int retval = 0;
	retval = chown(path, uid, gid);
	return retval;
}

int makefs_truncate(const char *path, off_t newsize)
{
	printf("Entered truncate");
	int retval = 0;
	retval = truncate(path, newsize);
	return retval;
}

int makefs_utime(const char *path, struct utimbuf *ubuf)
{
	printf("Entered utime");
	int retval = 0;
	retval = utime(path, ubuf);
	return retval;
}

int makefs_open(const char *path, struct fuse_file_info *fi)
{
	printf("Entered open");
	int retval = 0;
	int fd;
	fd = open(path, fi->flags);
	fi->fh = fd;
	if(fd < -1)
		retval = fd;
	return retval;
}

int makefs_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi)
{
	printf("Entered read");
	int retval = 0;
	retval = pread(fi->fh, buf, size, offset);
	return retval;
}

int makefs_write(const char *path, const char *buf, size_t size, off_t offset,
	     struct fuse_file_info *fi)
{
	printf("Entered write");
	int retval = 0;
	retval = pwrite(fi->fh, buf, size, offset);
	return retval;
	
}

int makefs_statfs(const char *path, struct statvfs *statv)
{
	printf("Entered statfs");
	int retval = 0;
	retval = statvfs(path, statv);
	return retval;
}

int makefs_flush(const char *path, struct fuse_file_info *fi)
{	
	printf("Entered flush");
	return 0; //Didn't see any reason to implement this right now.
}

int makefs_release(const char *path, struct fuse_file_info *fi)
{
	printf("Entered release");
	int retval = 0;
	retval = close(fi->fh);
	return retval;
}

int makefs_fsync(const char *path, int datasync, struct fuse_file_info *fi)
{
	printf("Entered fsync");
	int retval = 0;
	if(datasync)
		retval = fdatasync(fi->fh);
	else
		retval = fsync(fi->fh);
	return retval;
}

int makefs_setxattr(const char *path, const char *name, const char *value, size_t size, int flags)
{
	printf("Entered setxattr");
	int retval = 0;
	retval = lsetxattr(path, name, value, size, flags);
	return retval;
}

int makefs_getxattr(const char *path, const char *name, char *value, size_t size)
{
	printf("Entered getxattr");
	int retval = 0;
	retval = lgetxattr(path, name, value, size);
	return retval;
}

int makefs_listxattr(const char *path, char *list, size_t size)
{
	printf("Entered listxattr");
	int retval = 0;
	retval = llistxattr(path, list, size);
	return retval;
}

int makefs_removexattr(const char *path, const char *name)
{
	printf("Entered removexattr");
	int retval = 0;
	retval = lremovexattr(path, name);
	return retval;
}

int makefs_opendir(const char *path, struct fuse_file_info *fi)
{
	printf("Entered opendir");
	DIR *dp;
	int retval = 0;
	dp = opendir(path);//use open dir to get file handle
	fi->fh = dp; //set fi's file handler to dp
	return retval;
}

int makefs_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset,
	       struct fuse_file_info *fi)
{
	printf("Entered readdir");
	DIR *dp;
	int retval = 0;
	struct dirent *de;

	dp = (DIR *) (uintptr_t) fi->fh; //type cast the file handler to a directory
	de = readdir(dp);//set de to readdir's return value. 0 == error.
	if( de == 0)//error checking
	{
		retval = -1;
		return retval;
	}
	do{
		if(filler(buf, de->d_name, NULL, 0) != 0)//if filler returns zero buf is full
		{
			return -ENOMEM;
		}


	} while((de = readdir(dp)) != NULL); //keep looping while there is nothing left for readdir to read.
		
	return retval;
}

int makefs_releasedir(const char *path, struct fuse_file_info *fi)
{
	printf("Entered releasedir");
	int retval = 0;
	closedir((DIR *)(uintptr_t) fi->fh);
	return retval;
}

int makefs_fsyncdir(const char *path, int datasync, struct fuse_file_info *fi)
{
	printf("Entered fsyncdir");
	return 0;// didn't seem necessarry yet.
}

void* makefs_init(struct fuse_conn_info *conn)
{
	printf("Entered init");
	return MAKE_DATA;	
}

void makefs_destroy(void *userdata)
{
	printf("Entered destroy");
}

int makefs_access(const char *path, int mask)
{
	printf("Entered access");
	int retval = 0;
	retval = access(path, mask);
	return retval;
}

int makefs_create(const char *path, mode_t mode, struct fuse_file_info *fi)
{
	printf("Entered create");
	int retval = 0;
	int fd;
	fd = create(path, mode);
	if(fd < 0)
		retval = -1;
	fi->fh = fd;
	return retval;
}

int makefs_ftruncate(const char *path, off_t offset, struct fuse_file_info *fi)
{
	printf("Entered ftruncate");
	int retval = 0;
	retval = ftruncate(fi->fh, offset);
	return retval;	
}

int makefs_fgetattr(const char *path, struct stat *statbuf, struct fuse_file_info *fi)
{
	printf("Entered fgetattr");
	int retval = 0;
	retval = fstat(fi->fh, statbuf);
	return retval;
}

struct fuse_operations make_oper = {
  .getattr = make_getattr,
  .readlink = make_readlink,
  // no .getdir -- that's deprecated
  .getdir = NULL,
  .mknod = make_mknod,
  .mkdir = make_mkdir,
  .unlink = make_unlink,
  .rmdir = make_rmdir,
  .symlink = make_symlink,
  .rename = make_rename,
  .link = make_link,
  .chmod = make_chmod,
  .chown = make_chown,
  .truncate = make_truncate,
  .utime = make_utime,
  .open = make_open,
  .read = make_read,
  .write = make_write,
  .statfs = make_statfs,
  .flush = make_flush,
  .release = make_release,
  .fsync = make_fsync,
  .setxattr = make_setxattr,
  .getxattr = make_getxattr,
  .listxattr = make_listxattr,
  .removexattr = make_removexattr,
  .opendir = make_opendir,
  .readdir = make_readdir,
  .releasedir = make_releasedir,
  .fsyncdir = make_fsyncdir,
  .init = make_init,
  .destroy = make_destroy,
  .access = make_access,
  .create = make_create,
  .ftruncate = make_ftruncate,
  .fgetattr = make_fgetattr
};

void makefs_usage()
{
	fprintf(stderr, "Usage: makefs [FUSE and mount options] root_directory mount_point\n");
	abort();
}

int main(int argc, char* argv[])
{
	int fuse_stat;
	struct make_state *make_data;

	if((getuid() == 0) || (geteuid() == 0))
	{
		fprintf(stderr, "Running makefs as root opens up security holes within the system\n");
		return 1;
	}

	if((argc < 3) || (argv[argc - 2] == '-') || (argv[argc - 1] == '-'))
	{
	/* there should be at least 3 arguments. since all of the rulses start with '-' we can just
		make sure that the last two don't start with '-''s.*/
		makefs_usage();
	}

	make_data = malloc(sizeof(struct make_state));
	if(make_data == NULL)
	{
		perror("Problem allocating space for make_data");
		abort();
	}

	make_data->root_dir = argv[argc-2];
	argv[argc-2] = argv[argc - 1];
	argc--;

	fprintf(stderr, "About to call fuse main\n");
	fuse_stat = fuse_main(argc, argv, &make_oper, make_data);
	fprintf(stderr, "Returned from fuse main. Return value: %d\n", fuse_stat);
}