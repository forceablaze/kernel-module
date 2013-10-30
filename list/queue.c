#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/init.h>
#include <linux/version.h>
#include <linux/list.h>
#include <linux/kthread.h>
#include <linux/mutex.h>

static unsigned int queue_max_size = 5;
static unsigned int queue_size;
static int count = 0;
static DEFINE_MUTEX(queue_mutex);

struct person
{
	int id;
	struct list_head list;
};

static LIST_HEAD(queue);
struct task_struct *thread;

static void qperson(void)
{
	struct person *p;
#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,38))
	struct list_head *queue_tmp;
#endif

	printk(KERN_INFO "%s\n", __func__);

	mutex_lock(&queue_mutex);

	if(queue_size >= queue_max_size)
	{
		p = list_first_entry(&queue, struct person, list);
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,38))
		__list_del_entry(&p->list);
#else
		queue_tmp = &p->list;
		__list_del(queue_tmp->prev, queue_tmp->next);
#endif
		kfree(p);
		queue_size--;
	}


	p = kmalloc(sizeof(struct person), GFP_KERNEL);
	INIT_LIST_HEAD(&p->list);
	p->id = count++;

	printk(KERN_INFO "queue person: id: %d\n", p->id);
	list_add_tail(&p->list, &queue);
	queue_size++;

	mutex_unlock(&queue_mutex);
}

static int thread_proc(void *arg)
{
	printk(KERN_INFO "%s\n", __func__);
	for(;;)
	{
		if(kthread_should_stop())
			break;
		set_current_state(TASK_INTERRUPTIBLE);
		schedule_timeout(HZ * 2);

		qperson();
	}

	__set_current_state(TASK_RUNNING);
	return 0;
}

static void queue_clean(void)
{
	struct person *p, *tmp;

	printk(KERN_INFO "%s\n", __func__);

	mutex_lock(&queue_mutex);
	list_for_each_entry_safe(p, tmp, &queue, list)
	{
        printk(KERN_INFO "clean person: id: %d\n", p->id);
		list_del(&p->list);
		kfree(p);
		queue_size--;
	}
	mutex_unlock(&queue_mutex);
}

static void queue_list(void)
{
	struct person *p;

	printk(KERN_INFO "%s\n", __func__);

	mutex_lock(&queue_mutex);

	list_for_each_entry(p, &queue, list) {
        printk(KERN_INFO "Person: id: %d\n", p->id);
    }

	mutex_unlock(&queue_mutex);
}

static int __init init_queue(void)
{
	queue_size = 0;
	thread = kthread_create(thread_proc, NULL, "queue_thread");
	if(IS_ERR(thread))
	{
		printk(KERN_ERR "create queue_therad fail\n");
		return 0;
	}
	wake_up_process(thread);

	return 0;
}

static void __exit exit_queue(void)
{
	kthread_stop(thread);
	queue_list();
	queue_clean();
}

module_init(init_queue);
module_exit(exit_queue);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("queue test");
MODULE_AUTHOR("bedivere");
module_param_named(size, queue_max_size, uint, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(size, "queue maximum size");
