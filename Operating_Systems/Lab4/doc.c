#include <sys/types.h>
#include <dirent.h>

DIR *opendir(const char *name);
struct dirent *readdir(DIR *dirp);

ino_t d_ino; // The inode of the file
char d_name; // The name of the file

// Basically dirent structure is defined as follows

struct dirent
{
	ino_t d_ino;
	off_t d_off; // offset to the next directory
	unsigned short d_reclen; /// length of this record
	unsigned char d_type; // type of file
	char d_name[256]; // filename
};

// Creating and removing directories
#include <sys/stat.h>
int mkdir(const char* path, mode_t mode);
int rmdir(const char* path);

int closedir(DIR* dirp);

// System calls related to processes

getpid()
#include <sys/types.h>
#include <unistd.h>
pid_t getpid(void); // gives process id
pid_t getppid(void); // gives parent process id

fork() // new process created by calling this


#include <sys/types.h>
#include <unistd.h>

pid_t fork(void);

// for parent the pid is of the child and for the child it is zero

wait() // causes the parent to sleep until the child has finished execution
wait(&status) // the exit status 

exit() // the exit system call is used to terminate the current running process
exec() // the exec function will execute a specified program passed as argument to it, in the same process


// IO System Calls
creat() // create a file
open()
close()
unlink() // delete a file
write() // write bytes to a file
read() // Read bytes from file

int fp = creat(<filename>,<protection bits>)
int fp = creat("students.dat", RD_WR);
O_RDONLY
O_WRONLY
O_RDWR


