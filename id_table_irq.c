
#include <linux/module.h>
#include <linux/kernel.h>

#include <linux/interrupt.h>
#include <linux/pci.h>
#include <linux/etherdevice.h>


static DEFINE_PCI_DEVICE_TABLE(my_table) = {
	{PCI_DEVICE(0x8086, 0x100e)},	//Device Vendor and device ID
	{}		//Terminating Entry
};

MODULE_DEVICE_TABLE(pci, my_table);

//struct e1000_adapter;

static struct e1000_adapter {
	unsigned int total_tx_bytes;
	unsigned int total_tx_packets;
	unsigned int total_rx_bytes;
	unsigned int total_rx_packets;
	//struct e1000_tx_ring *tx_ring;
	//struct e1000_rx_ring *rx_ring;
};


int my_open (struct net_device *netdev)
{
	printk("my_open\n");
	//printk("irq :%d\n", netdev->dev->irq);
	int err;
	//register irq functionalities
	//err = request_irq(netdev->irq, );
	return 0;
}

int my_close(struct net_device *netdev)
{
	printk("my_close\n");
	return 0;
}

static netdev_tx_t my_xmit (struct sk_buff *skb, struct net_device *netdev)
{
	printk("start tranmit...\n");
	return NETDEV_TX_OK;
}

static const struct net_device_ops e1000_netdev_ops = {
	.ndo_open = my_open,
	.ndo_stop = my_close,
	//.ndo_start_xmit = my_xmit,
};

static int my_probe (struct pci_dev *pdev, const struct pci_device_id *id)
{
	int err;
	// allocate etherdev	alloc_etherdev
	struct net_device *netdev;
	netdev  = alloc_etherdev(sizeof(struct e1000_adapter));
	if (!netdev) {
		printk("error initializing....alloc_etherdev\n");
		return -1;
	}
	// Fill required structure members
	netdev->netdev_ops = &e1000_netdev_ops;
	
	// register with net_device subsystem
	err = register_netdev(netdev);
	if (err) {
		printk("error register_netdev...\n");
		return -1;
	}
	//printk("probe called irq :%d ", pdev->irq);
	//printk("mmio :%x\n", (unsigned int )pci_resource_start(pdev, 0));
	return 0;
}


static struct pci_driver my_driver = {
	.name = KBUILD_MODNAME,
	.probe = my_probe,
	.id_table = my_table,
};

int irq_init(void)
{
	int ret;
	printk("irq_init.\n");
	ret = pci_register_driver(&my_driver);
	printk("ret :%d\n", ret);

	return 0;
}

void irq_exit(void)
{
	pci_unregister_driver(&my_driver);
	printk("irq_exit.-----------------\n");
}

module_init(irq_init);
module_exit(irq_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("IRQSHARE Test");

