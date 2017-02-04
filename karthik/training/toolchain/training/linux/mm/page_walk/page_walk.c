/** System Includes **/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/sched.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#include <linux/device.h>
#include <linux/slab.h>
#include <linux/mmzone.h>
#include <linux/highmem.h>
MODULE_LICENSE("Dual BSD/GPL");

/** Constants **/
#define FIRST_MINOR 0	
#define NR_DEVS 1		//Number of device numbers
#define LOWMEM_END 0x38000000

//Function Declarations for syscall definitions
int myOpen(struct inode *inode, struct file *filep);
int myRelease(struct inode *in, struct file *fp);
long myIoctl(struct file* fp1, unsigned int pid, unsigned long addr);
//Initialization routines
static int myInit(void);
static void myExit(void);

struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = myOpen,
	.release = myRelease,
	.unlocked_ioctl = myIoctl
};

/* GLobal variables */
char *devname;	//contains device name
int majNo;	
static dev_t mydev;	//encodses major number and minor number 
struct cdev *my_cdev;//holds character device driver discriptor

/* TO accept input from the command line */
module_param(devname, charp, 0000);

//class and device structure
static struct class *mychar_class;
static struct device *mychar_device;

/*
 * myOpen: open function of the pseudo driver
 */

int myOpen(struct inode *inode, struct file *filep)
{

	printk(KERN_INFO "Open successful\n");
	return 0;
}

/*
 * myRelease: close function of the pseudo driver
 */
int myRelease(struct inode *in, struct file *fp)
{
	printk(KERN_INFO "File released\n");
	return 0;
}

/*
 * myInit: init function of the kernel module\
 */

static int __init myInit(void)
{
	int ret = -ENODEV;
	int status;

	printk(KERN_INFO "Initializing character device\n");

	// Allocation Device Numbers
	status = alloc_chrdev_region(&mydev, FIRST_MINOR, NR_DEVS, devname);
	if(status < 0) {
		printk(KERN_INFO "Device number allocation failed: %d\n", status);
		goto err;
	}

	printk(KERN_INFO "Major number allocated = %d\n", MAJOR(mydev));
	my_cdev = cdev_alloc();	//Allocate memory for my_cdev
	if(my_cdev == NULL) {
		printk(KERN_INFO "cdev_alloc failed \n");
		goto err_cdev_alloc;
	}

	cdev_init(my_cdev, &fops);	//Initialize my_cdev with fops
	my_cdev -> owner = THIS_MODULE;

	status = cdev_add (my_cdev, mydev, NR_DEVS);	//Add my_cdev to the list
	if(status) {
		printk(KERN_ERR "cdev_add failed \n");
		goto err_cdev_add;
	}

	//Create a class and an entry in sysfs
	mychar_class = class_create(THIS_MODULE, devname);
	if(IS_ERR(mychar_device)) {
		printk(KERN_ERR "class_create() failed \n");
		goto err_class_create;
	}

	//create mychar_device in sysfs and an
	//device entry will be made in /dev directory
	mychar_device = device_create(mychar_class, NULL, mydev, NULL, devname);
	if(IS_ERR(mychar_device)) {
		printk(KERN_ERR "device_create() failed \n");
		goto err_device_create;
	}

	return 0;

err_device_create:
	class_destroy(mychar_class);

err_class_create:
	cdev_del(my_cdev);

err_cdev_add:
	kfree(my_cdev);

err_cdev_alloc:
	unregister_chrdev_region(mydev, NR_DEVS);

err:
	return ret;
}

/*
 * myExit: cleanup function of the kernel module
 */

static void myExit(void)
{
	printk(KERN_INFO "Exiting the character driver \n");

	device_destroy(mychar_class, mydev);
	class_destroy(mychar_class);
	cdev_del(my_cdev);
	unregister_chrdev_region(mydev, NR_DEVS);

	return;
}

long myIoctl(struct file* fp1, unsigned int pid, unsigned long uv_addr)
{
	unsigned long pgd_index;//used for holding index into pgd table
	unsigned long pt_index;	//used for holding index into pt table
	unsigned long pgf_index;// used for holding index into actual page frame
	unsigned long pt_base;//used for holding the base address of the pt table
	unsigned long pg_entry;//used for holding the actual page frame address
	unsigned long* vir_addr;// used for holding virtual address 
	
	struct task_struct* my_task = current;
	pgd_t *pgd_ptr = my_task -> mm -> pgd;

	pgd_index = ((unsigned long)uv_addr) >> 22;

	pt_index = (((unsigned long)uv_addr) << 10) >> 22;

	pgf_index = (((unsigned long)uv_addr) << 20) >> 20;

	printk("pgd_index : %lx \n", pgd_index);
	printk("pgd base address : %lx \n", (unsigned long)pgd_ptr);
	printk("pgd base + index : %lx \n", (unsigned long)(pgd_ptr + pgd_index));

	//finding the base address of the page table

	pt_base = (pgd_ptr[pgd_index].pgd >> 12) << 12;

	printk ("PGD : %lx\n", pt_base);

	//converting the physical address of page table present in the pgd table to virtual address inorder to dereference the data 

	if (pt_base < LOWMEM_END) {
		vir_addr = (unsigned long*) (pt_base + PAGE_OFFSET);
	} else {
		vir_addr = (unsigned long*) kmap (&mem_map[pt_base >> 12]);
	}

	//finding the base physical address of page frame where the actual data present

	pg_entry = (vir_addr[pt_index] >> 12) << 12;

	printk ("pt : %lx\n", pg_entry);

	//converting the physical address of page frame to virtual address inorder to derefernece the data

	if (pg_entry < LOWMEM_END) {
		vir_addr = (unsigned long*) (pg_entry + PAGE_OFFSET);
	} else {
		vir_addr = (unsigned long*) kmap (mem_map + (pg_entry >> 12));
	}
	
	//printing the data present in that address

	printk (KERN_INFO "value of global variable :  %d \n", *(((char *)vir_addr) + pgf_index));

	//modifying the global variable data 

	*(((char *)vir_addr) + pgf_index) = 100;
	
	return 0;
}
module_init(myInit);
module_exit(myExit);

