#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/version.h>
#include<linux/string.h>
#include<linux/fs.h>
#include<linux/init.h>
#include<linux/slab.h>
#include<linux/uaccess.h>
#include<linux/ioctl.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Joel Cecil");
MODULE_DESCRIPTION("Cipher Device Driver");
MODULE_VERSION("0.1");

static ssize_t readcipher(struct file *,char *,size_t,loff_t *);
static ssize_t writecipher(struct file *,const char *,size_t,loff_t *);
static int open_dev(struct inode *,struct file *);
static int close_dev(struct inode *,struct file *);
static long ioctlcipher(struct file *,unsigned int,unsigned long);
int major;
char *b;

int atoi(const char *str) {
    int res=0,i=0;
    for(i=0;str[i]!='\0';i++)
        res=res*10+str[i]-'0';
    return res;
}

static struct file_operations fops={
    .open=open_dev,
    .release=close_dev,
    .read=readcipher,
    .write=writecipher,
    .unlocked_ioctl=ioctlcipher,
};

static ssize_t readcipher(struct file *filep,char *buff,size_t len,loff_t *f_ops) {
    copy_to_user(buff,b,strlen(b));
    printk("Reading cipher\n");
    return len;
}

ssize_t writecipher(struct file *filp,const char *buff,size_t len,loff_t *off) {
    copy_from_user(b,buff,len);
    printk("Writing cipher\n");
    return len;
}

static long ioctlcipher(struct file *file,unsigned int cmd,unsigned long arg) {
    int i;
	printk("%s\n", b);
    switch(cmd) {
        case 0: { //cipher
		  for(i=0; b[i] != '\0'; i++) {
			b[i] = 'A' + ((b[i]-'A' + 5) % 26);
		  }
		  break;
		}
	case 1: { //decipher
		  for(i=0; b[i] != '\0'; i++) {
			b[i] = 'A' + ((b[i]-'A' + 21) % 26);
		  }
		  break;
		}
    }
    return 0;
}

static int open_dev(struct inode *a,struct file *filep) {
    b=kmalloc(40*sizeof(char),GFP_KERNEL);
    printk(KERN_INFO "Cipher device opened\n");
    return 0;
}

static int close_dev(struct inode *a,struct file *filep) {
    printk(KERN_INFO "Cipher device closed\n");
    return 0;
}

static int __init cipher_start(void) {
    if((major=(register_chrdev(0,"cipher",&fops)))<0) {
        return -1;
    }
    printk(KERN_INFO "Cipher device loaded%d\n",major);
    return 0;
}

static void __exit cipher_end(void) {
    unregister_chrdev(major,"cipher");
    printk(KERN_INFO "Cipher device unloaded\n");
}

module_init(cipher_start);
module_exit(cipher_end);
