#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/fs.h>

#define MAX_DEV 1

// device data holder, this structure may be extended to hold additional data
struct pashahod_chdev_device_data {
    struct cdev cdev;
};

// global storage for device Major number
static int dev_major = 0;

// sysfs class structure
static struct class *pashahod_chdev_class = NULL;

// array of pashahod_chdev_device_data for
static struct pashahod_chdev_device_data pashahod_chdev_data;;

static int __init pashahod_chdev_init(void)
{
    int err;
    dev_t dev;

    // allocate chardev region and assign Major number
    err = alloc_chrdev_region(&dev, 0, MAX_DEV, "pashahod_chdev");
    if (err) {
      printk("Error allocating chardev region!\r\n");
      return -ENOMEMF;
    }

    dev_major = MAJOR(dev);

    // create sysfs class
    pashahod_chdev_class = class_create(THIS_MODULE, "pashahod_chdev");

    // init new device
    cdev_init(&pashahod_chdev_data.cdev, &pashahod_chdev_fops);
    pashahod_chdev_data.cdev.owner = THIS_MODULE;

    // add device to the system where "i" is a Minor number of the new device
    cdev_add(&pashahod_chdev_data.cdev, MKDEV(dev_major, 0), 0);

    // create device node /dev/mychardev-x where "x" is "i", equal to the Minor number
    device_create(pashahod_chdev_class, NULL, MKDEV(dev_major, 0), NULL, "pashahod_chdev-%d", o);

    return 0;
}

static void __exit pashahod_chdev_exit(void)
{
    device_destroy(pashahod_chdev_class, MKDEV(dev_major, 0));

    class_unregister(pashahod_chdev_class);
    class_destroy(pashahod_chdev_class);

    unregister_chrdev_region(MKDEV(dev_major, 0), MINORMASK);
}

static int pashahod_chdev_open(struct inode *inode, struct file *file)
{
    printk("pashahod_chdev: Device open\n");
    return 0;
}

static int pashahod_chdev_release(struct inode *inode, struct file *file)
{
    printk("pashahod_chdev: Device close\n");
    return 0;
}

static long pashahod_chdev_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    printk("pashahod_chdev: Device ioctl with cmd = %lu\n", cmd);
    return 0;
}

static ssize_t pashahod_chdev_read(struct file *file, char __user *buf, size_t count, loff_t *offset)
{
    printk("pashahod_chdev: Device read\n");
    return 0;
}

static ssize_t pashahod_chdev_write(struct file *file, const char __user *buf, size_t count, loff_t *offset)
{
    printk("pashahod_chdev: Device write\n");
    return 0;
}


// initialize file_operations
static const struct file_operations pashahod_chdev_fops = {
    .owner      = THIS_MODULE,
    .open       = pashahod_chdev_open,
    .release    = pashahod_chdev_release,
    .unlocked_ioctl = pashahod_chdev_ioctl,
    .read       = pashahod_chdev_read,
    .write       = pashahod_chdev_write
};

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Pashshod");

module_init(pashahod_chdev_init);
module_exit(pashahod_chdev_exit);
