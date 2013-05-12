#include "parameters.h"
#include "make_generator.h"

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

static void makefs_realpath(char rpath[PATH_MAX], const char* path)
{
	strcpy(rpath, MAKE_DATA->root_dir);
	strncat(rpath, path, PATH_MAX);


}
static int makefs_error()
{
	int retval = -errno;
	return retval;
}

int makefs_getattr(const char *path, struct stat *statbuf)
{
	int retval = 0;
	char rpath[PATH_MAX];
	printf("Entered getattr\n");
	makefs_realpath(rpath, path);
	retval = lstat(rpath, statbuf);
	if(retval == -1)
		retval = -errno;
	return retval;
}
int makefs_readlink(const char *path, char *link, size_t size)
{
	printf("Entered readlink\n");
	int retval = 0;
	char rpath[PATH_MAX];
	makefs_realpath(rpath, path);
	retval = readlink(rpath, link, size -1);
	if(retval < 0)
		return -EXIT_FAILURE;
	else
	{
		link[retval] = "\0";
		retval = 0;
	}
	return retval;
}

int makefs_mknod(const char *path, mode_t mode, dev_t dev)
{
	printf("Entered mknod\n");
	int retval = 0;
	char rpath[PATH_MAX];
	makefs_realpath(rpath, path);
	retval = mknod(rpath, mode, dev);
	return retval;	
}

int makefs_mkdir(const char *path, mode_t mode)
{
	printf("Entered mkdir");
	int retval = 0;
	char rpath[PATH_MAX] = {NULL};
	makefs_realpath(rpath, path);
	retval = mkdir(rpath, mode);
	//Add the meta-data to directory
	char* file_path = "/.files.txt";
	strncat(rpath, file_path, PATH_MAX); 
	FILE* meta = fopen(rpath, "w");
	fprintf(meta, path);
	fprintf(meta, "\n");
	fclose(meta);
	return retval;
	
}

int makefs_unlink(const char *path)
{
	printf("Entered unlink\n");
	int retval = 0;
	char rpath[PATH_MAX];
	makefs_realpath(rpath, path);
	retval = unlink(rpath);
	return retval;
}

int makefs_rmdir(const char *path)
{
	printf("Entered rmdir");
	int retval = 0;
	char rpath[PATH_MAX];
	makefs_realpath(rpath, path);
	retval = rmdir(rpath);
	return retval;
}

int makefs_symlink(const char *path, const char *link)
{
	printf("Entered symlink\n");
	int retval = 0;
	char rpath[PATH_MAX];
	makefs_realpath(rpath, path);
	retval = symlink(rpath, link);
	return retval;
}

int makefs_rename(const char *path, const char *newpath)
{
	printf("Entered rename\n");
	int retval = 0;
	char rpath[PATH_MAX];
	char rnewpath[PATH_MAX];
	makefs_realpath(rpath, path);
	makefs_realpath(rnewpath, newpath);
	retval = rename(rpath, rnewpath);
	return retval;
}

int makefs_link(const char *path, const char *newpath)
{
	printf("Entered link\n");
	int retval = 0;
	char rpath[PATH_MAX];
	char rnewpath[PATH_MAX];
	makefs_realpath(rpath, path);
	makefs_realpath(rnewpath, newpath);
	retval = link(rpath, rnewpath);
	return retval;
}

int makefs_chmod(const char *path, mode_t mode)
{
	printf("Entered chmod\n");
	int retval = 0;
	char rpath[PATH_MAX];
	makefs_realpath(rpath, path);
	retval = chmod(rpath, mode);
	return retval;
}

int makefs_chown(const char *path, uid_t uid, gid_t gid)
{
	printf("Entered chown\n");
	int retval = 0;
	char rpath[PATH_MAX];
	makefs_realpath(rpath, path);
	retval = chown(rpath, uid, gid);
	return retval;
}

int makefs_truncate(const char *path, off_t newsize)
{
	printf("Entered truncate\n");
	int retval = 0;
	char rpath[PATH_MAX];
	makefs_realpath(rpath, path);
	retval = truncate(rpath, newsize);
	return retval;
}

int makefs_utime(const char *path, struct utimbuf *ubuf)
{
	printf("Entered utime\n");
	int retval = 0;
	char rpath[PATH_MAX];
	makefs_realpath(rpath, path);	
	retval = utime(rpath, ubuf);
	return retval;
}

int makefs_open(const char *path, struct fuse_file_info *fi)
{
	printf("Entered open\n");
	int retval = 0;
	int fd;
	char rpath[PATH_MAX];
	makefs_realpath(rpath, path);
	fd = open(rpath, fi->flags);
	fi->fh = fd;
	if(fd < -1)
		retval = makefs_error();
	return retval;
}

int makefs_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi)
{
	printf("Entered read\n");
	int retval = 0;
	retval = pread(fi->fh, buf, size, offset);
	return retval;
}

int makefs_write(const char *path, const char *buf, size_t size, off_t offset,
	     struct fuse_file_info *fi)
{
	printf("Entered write\n");
	int retval = 0;
	retval = pwrite(fi->fh, buf, size, offset);
	return retval;
	
}

int makefs_statfs(const char *path, struct statvfs *statv)
{
	printf("Entered statfs\n");
	int retval = 0;
	char rpath[PATH_MAX];
	makefs_realpath(rpath, path);
	retval = statvfs(rpath, statv);
	return retval;
}

int makefs_flush(const char *path, struct fuse_file_info *fi)
{	
	printf("Entered flush\n");
	return 0; //Didn't see any reason to implement this right now.
}

int makefs_release(const char *path, struct fuse_file_info *fi)
{
	printf("Entered release\n");
	int retval = 0;
	retval = close(fi->fh);
	return retval;
}

int makefs_fsync(const char *path, int datasync, struct fuse_file_info *fi)
{
	printf("Entered fsync\n");
	int retval = 0;
	if(datasync)
		retval = fdatasync(fi->fh);
	else
		retval = fsync(fi->fh);
	return retval;
}

int makefs_setxattr(const char *path, const char *name, const char *value, size_t size, int flags)
{
	printf("Entered setxattr\n");
	int retval = 0;
	char rpath[PATH_MAX];
	makefs_realpath(rpath, path);
	retval = lsetxattr(rpath, name, value, size, flags);
	return retval;
}

int makefs_getxattr(const char *path, const char *name, char *value, size_t size)
{
	printf("Entered getxattr\n");
	int retval = 0;
	char rpath[PATH_MAX];
	makefs_realpath(rpath, path);
	retval = lgetxattr(rpath, name, value, size);
	return retval;
}

int makefs_listxattr(const char *path, char *list, size_t size)
{
	printf("Entered listxattr\n");
	int retval = 0;
	char rpath[PATH_MAX];
	makefs_realpath(rpath, path);
	retval = llistxattr(rpath, list, size);
	return retval;
}

int makefs_removexattr(const char *path, const char *name)
{
	printf("Entered removexattr\n");
	int retval = 0;
	char rpath[PATH_MAX];
	makefs_realpath(rpath, path);
	retval = lremovexattr(rpath, name);
	return retval;
}

int makefs_opendir(const char *path, struct fuse_file_info *fi)
{
	printf("Entered opendir\n");
	DIR *dp;
	int retval = 0;
	char rpath[PATH_MAX];
	makefs_realpath(rpath, path);
	dp = opendir(rpath);//use open dir to get file handle
	fi->fh = dp; //set fi's file handler to dp
	return retval;
}

int makefs_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset,
	       struct fuse_file_info *fi)
{
	printf("Entered readdir\n");
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
	printf("Entered releasedir\n");
	int retval = 0;
	closedir((DIR *)(uintptr_t) fi->fh);
	return retval;
}

int makefs_fsyncdir(const char *path, int datasync, struct fuse_file_info *fi)
{
	printf("Entered fsyncdir\n");
	return 0;// didn't seem necessarry yet.
}

void* makefs_init(struct fuse_conn_info *conn)
{
	printf("Entered init\n");
	return MAKE_DATA;	
}

void makefs_destroy(void *userdata)
{
	printf("Entered destroy\n");
}

int makefs_access(const char *path, int mask)
{
	printf("Entered access\n");
	int retval = 0;
	char rpath[PATH_MAX];
	makefs_realpath(rpath, path);
	retval = access(rpath, mask);
	return retval;
}

int makefs_create(const char *path, mode_t mode, struct fuse_file_info *fi)
{
	printf("Entered create, path was %s\n", path);
	int retval = 0;
	int fd;
	char rpath[PATH_MAX] = {NULL};
	makefs_realpath(rpath, path);//get the abosolute path that this file will be created at
	char* meta_path = get_meta_path(rpath);//get the path to this directories metafile
	printf("Meta path: %s\n", meta_path);
	
	printf("rpath before creation: %s\n", rpath);
	printf("about check if ""Makefile"" is a part of the path name\n");
	if (strstr(path, "/Makefile") != NULL)//if mMakefile is part of path name
	{
		//here we need to strip off all of the flags and call creat on make_path.
		printf("going to call make_gen\n");
		fd = creat(get_make_path(rpath), mode);
		if(make_gen(rpath, meta_path) == true); //fill the new file with makefile text
		printf("Makefile created.\n");
	}
	else if(correct_type(meta_path, rpath) == true)
	{
		fd = creat(rpath, mode);
		add_meta(meta_path, rpath);
	}
	else
		fd = creat(rpath, mode);
	if(fd < 0)
		retval = makefs_error();
	fi->fh = fd;
	return retval;
}

int makefs_ftruncate(const char *path, off_t offset, struct fuse_file_info *fi)
{
	printf("Entered ftruncate\n");
	int retval = 0;
	retval = ftruncate(fi->fh, offset);
	return retval;	
}

int makefs_fgetattr(const char *path, struct stat *statbuf, struct fuse_file_info *fi)
{
	printf("Entered fgetattr\n");
	int retval = 0;
	retval = fstat(fi->fh, statbuf);
	return retval;
}

struct fuse_operations make_oper = {
  .getattr = makefs_getattr,
  .readlink = makefs_readlink,
  // no .getdir -- that's deprecated
  .getdir = NULL,
  .mknod = makefs_mknod,
  .mkdir = makefs_mkdir,
  .unlink = makefs_unlink,
  .rmdir = makefs_rmdir,
  .symlink = makefs_symlink,
  .rename = makefs_rename,
  .link = makefs_link,
  .chmod = makefs_chmod,
  .chown = makefs_chown,
  .truncate = makefs_truncate,
  .utime = makefs_utime,
  .open = makefs_open,
  .read = makefs_read,
  .write = makefs_write,
  .statfs = makefs_statfs,
  .flush = makefs_flush,
  .release = makefs_release,
  .fsync = makefs_fsync,
  .setxattr = makefs_setxattr,
  .getxattr = makefs_getxattr,
  .listxattr = makefs_listxattr,
  .removexattr = makefs_removexattr,
  .opendir = makefs_opendir,
  .readdir = makefs_readdir,
  .releasedir = makefs_releasedir,
  .fsyncdir = makefs_fsyncdir,
  .init = makefs_init,
  .destroy = makefs_destroy,
  .access = makefs_access,
  .create = makefs_create,
  .ftruncate = makefs_ftruncate,
  .fgetattr = makefs_fgetattr
};

void makefs_usage()
{
	fprintf(stderr, "Usage: makefs [FUSE and mount options] root_directory mount_point\n");
	abort();
}

int main(int argc, char* argv[])
{
	int fuse_stat;
	struct make_state *make_data = malloc(sizeof(struct make_state));
	
	if(make_data == NULL)
	{
		perror("Problem allocating space for make_data");
		abort();
	}

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

	make_data->root_dir = realpath(argv[argc-2], NULL);

	argv[argc-2] = argv[argc - 1];
	argc--;//take root_dir out of arguments before passing to fuse_main

	fprintf(stderr, "About to call fuse main\n");

	fuse_stat = fuse_main(argc, argv, &make_oper, make_data);
	fprintf(stderr, "Returned from fuse main. Return value: %d\n", fuse_stat);
	return fuse_stat;
}