/***********************************************************
code writer	: EOF
code date	: 2014.09.01
code file	: proc_demo.c
e-mail		: jasonleaster@gmail.com

code purpose:
	
	This code is programmed for how to create a proc-entry
in procfs.

	If there is something wrong with my code, please touch
me by e-mail. Thank you.

************************************************************/
#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>

#include <linux/fs.h>
#include <linux/proc_fs.h> /* for procfs */
#include <linux/seq_file.h>
#include <linux/types.h>

#define PROC_NAME "proc_demo"

MODULE_AUTHOR("Jason Leaster");
MODULE_LICENSE("Dual BSD/GPL");

static int proc_demo_seq_show(struct seq_file* sfile,void* v)
{
	int tmp = 0;

	for(tmp = 0; tmp < 10;tmp++)
	{
		seq_printf(sfile,"Hello world!\n");
	}

	return 0;
}

static void* proc_demo_seq_start(struct seq_file* sfile,loff_t *pos)
{
	return NULL;
}

static void proc_demo_seq_stop(struct seq_file* sfile,void* v)
{
	/* Nothing to be done. */
}

static void* proc_demo_seq_next(struct seq_file* sfile,void* v,loff_t* pos)
{
	return NULL;
}

static struct seq_operations proc_demo_ops = 
{
	.start	=	proc_demo_seq_start,
	.next	=	proc_demo_seq_next,
	.stop	=	proc_demo_seq_stop,
	.show	=	proc_demo_seq_show,
};

static int proc_demo_open(struct inode* inode, struct file* filp)
{
	return single_open(filp,&proc_demo_seq_show,NULL);
}

struct file_operations proc_demo_fops = 
{
	.owner	=	THIS_MODULE,
	.open	=	proc_demo_open,
	.read	=	seq_read,
	.release=	seq_release,
};

int proc_demo_init(void)
{
	struct proc_dir_entry * entry = NULL;
	
	entry =	proc_create(PROC_NAME,0,NULL,&proc_demo_fops);
	if(!entry)
	{
		printk(KERN_ALERT "line:%d proc_create failed!",__LINE__);
	}

	return 0;
}

void proc_demo_exit(void)
{
	/*
	**       The second parameter of 'remove_proc_entry()' is 
	** a pointer which point to parent directory.We create our
	** proc-entry-point in /proc/, so we pass NULL into it.
	*/
	remove_proc_entry(PROC_NAME,NULL);
}

module_init(proc_demo_init);
module_exit(proc_demo_exit);
