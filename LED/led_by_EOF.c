/*
code writer	: EOF
code date	: 2014.08.19.com
code file	: led_by_EOF.c
e-mail		: jasonleaster@gmail.com

code purpos:

	This code is a demo for beginner how to write a
character device to drive IO port.

	If you find there is something wrong with my code
and change it into a better version , please touch me 
by e-mail. Thank you.

*/
#include <linux/init.h>
#include <linux/slab.h>

#include <linux/fs.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <asm/uaccess.h> /* for 'copy_from_user' */
#include <linux/cdev.h>
#include <linux/kdev_t.h>
#include <linux/types.h>
#include <mach/gpio-bank-m.h>
#include <mach/regs-gpio.h>
#include <mach/map.h>
#include <linux/pci.h>
#include <linux/device.h>


#include <linux/delay.h> /* for 'msleep' */

MODULE_AUTHOR("EOF");
MODULE_LICENSE("Dual BSD/GPL");

#define DEVICE_NAME	"led_by_EOF"
#define DEVICE_MAJOR_NUMBER 0 

#define USE_IMMEDIATE

static dev_t dev_number = DEVICE_MAJOR_NUMBER;
static struct class* led_class;

static struct cdev my_led_cdev;

static int led_open(struct inode* node,struct file* file)
{
	printk(KERN_ALERT "Device Opened successful!\n");
	return 0;
}

static ssize_t led_write(struct file* file,const char __user* buf,size_t count,loff_t* ppos)
{
	int kbuf;
	int ret = 0;

	kbuf = readl(S3C64XX_GPMCON);
	kbuf &= (~0xFFFF);
	kbuf |= 0x1111;

	writel(kbuf,S3C64XX_GPMCON);

	printk(KERN_ALERT "before writing...  &kbuf:%p buf:%p\n",&kbuf,buf);
	ret = __copy_from_user(&kbuf,buf,count);
	if(ret != 0)
	{
		printk(KERN_ALERT "'__copy_from_user' failed! ret:%d\n",ret);
		
		return -1;
	}


	printk(KERN_ALERT "writing...   kbuf:%x \n",kbuf);

	writel(kbuf,S3C64XX_GPMDAT);

	return 0;
}

static int led_release(struct inode* inode,struct file*file)
{

	printk(KERN_ALERT "Device released\n");
	return 0;
}

static struct file_operations led_fops =
{
	.owner	=	THIS_MODULE,
	.open	=	led_open,
	.write	=	led_write,
	.release=	led_release,
};

int led_init(void)
{

	int kbuf;

	if(alloc_chrdev_region(&dev_number,0,1,DEVICE_NAME) < 0)
	{
		printk(KERN_ALERT "Error in function '%s' : can't register device\n",__FUNCTION__);

		return -1;
	}

	led_class = class_create(THIS_MODULE,DEVICE_NAME);

	if(IS_ERR(led_class))
	{
		printk(KERN_ALERT "Bad class create\n");

		return -1;
	}

	cdev_init(&my_led_cdev,&led_fops);

	/*
	** GPM0~GPM3 pull up
	*/
	kbuf = readl(S3C64XX_GPMPUD);

	kbuf &= (~0xFF);

	kbuf |= 0xaa;//1010 1010

	writel(kbuf,S3C64XX_GPMPUD);	

	/*
	** GPM0~3 output mode
	*/

	kbuf = readl(S3C64XX_GPMCON);
	kbuf &= (~0xFFFF);
	kbuf |= 0x1111;
	writel(kbuf,S3C64XX_GPMCON);

	/*
	**	GPM0~GPM3 output 0 and light up all LED
	*/

	kbuf  = __raw_readl(S3C64XX_GPMDAT);
	kbuf |= 0x10;
	writel(kbuf,S3C64XX_GPMDAT);


	if(cdev_add(&my_led_cdev,dev_number,1))
	{
		printk(KERN_ALERT "Bad cdev add\n");

		return 1;
	}

	device_create(led_class,NULL,dev_number,NULL,DEVICE_NAME);


	return 0;
}

void led_cleanup(void)
{
	device_destroy(led_class,MKDEV(MAJOR(dev_number),0));

	class_destroy(led_class);

	unregister_chrdev_region(MAJOR(dev_number),1);

	printk(KERN_ALERT "See you! My LED\n");
}

module_init(led_init);
module_exit(led_cleanup);
