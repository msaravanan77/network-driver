
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>


void snull_init()
{
	printk("snull init\n");
}

int snull_init(void)
{
	struct net_device *snull_devs[2];
	int i;
	for (i=0; i<2; i++) {	
		snull_devs[i] = alloc_netdev(0, "sn%d", snull_init);
		register_netdev(snull_devs[i]);
	}
	if ( snull_devs[0] == NULL || snull_devs[1] == NULL ) {
		printk("register_netdev error\n");
		return -1;
	}
	printk("snull init\n");
	return 0;
}

void snull_exit(void)
{
	printk("snull exit...\n");
}

module_init(snull_init);
module_exit(snull_exit);
MODULE_AUTHOR("Saravanan");
MODULE_LICENCE("GPL");

