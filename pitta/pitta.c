#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/version.h>

#include <linux/ip.h>
#include <linux/in.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Pitta module");
MODULE_AUTHOR("bedivere");

static struct nf_hook_ops nf_hook_pre_routing;
static struct nf_hook_ops nf_hook_local_in;
static struct nf_hook_ops nf_hook_forward;
static struct nf_hook_ops nf_hook_local_out;
static struct nf_hook_ops nf_hook_post_routing;

static void dump_iphdr(const char *fn, const struct iphdr *ip_header)
{
	printk(KERN_INFO "%s: saddr=%pI4, daddr=%pI4\n", fn,  &ip_header->saddr,
	  &ip_header->daddr);
}

static unsigned int nf_hookfn_pre_routing(unsigned int hooknum,
										  struct sk_buff *skb,
										  const struct net_device *in,
										  const struct net_device *out,
										  int (*okfn)(struct sk_buff *))
{
	const struct iphdr *ip_header = ip_hdr(skb);

	dump_iphdr(__func__, ip_header);

	if(ip_header->protocol == IPPROTO_TCP)
	{
		printk("TCP\n");
	}

	return NF_ACCEPT;
}
static unsigned int nf_hookfn_local_in(unsigned int hooknum,
									   struct sk_buff *skb,
									   const struct net_device *in,
									   const struct net_device *out,
									   int (*okfn)(struct sk_buff *))
{
	return NF_ACCEPT;
}
static unsigned int nf_hookfn_forward(unsigned int hooknum,
									  struct sk_buff *skb,
									  const struct net_device *in,
									  const struct net_device *out,
									  int (*okfn)(struct sk_buff *))
{
	return NF_ACCEPT;
}
static unsigned int nf_hookfn_local_out(unsigned int hooknum,
										struct sk_buff *skb,
										const struct net_device *in,
										const struct net_device *out,
										int (*okfn)(struct sk_buff *))
{
	return NF_ACCEPT;
}
static unsigned int nf_hookfn_post_routing(unsigned int hooknum,
										   struct sk_buff *skb,
									   	   const struct net_device *in,
										   const struct net_device *out,
										   int (*okfn)(struct sk_buff *))
{
	return NF_ACCEPT;
}

static void set_nf_hook_ops(struct nf_hook_ops *hook_ops, nf_hookfn *hook, int hooknum)
{
	hook_ops->hook = hook;
	hook_ops->hooknum  = hooknum;
	hook_ops->pf = PF_INET;
	hook_ops->priority = NF_IP_PRI_FIRST;
	hook_ops->owner = THIS_MODULE;
}

static int __init init_pitta(void)
{
	printk(KERN_INFO "initialize pitta module\n");

	set_nf_hook_ops(&nf_hook_pre_routing, nf_hookfn_pre_routing, NF_INET_PRE_ROUTING);
	set_nf_hook_ops(&nf_hook_local_in, nf_hookfn_local_in, NF_INET_LOCAL_IN);
	set_nf_hook_ops(&nf_hook_forward, nf_hookfn_forward, NF_INET_FORWARD);
	set_nf_hook_ops(&nf_hook_local_out, nf_hookfn_local_out, NF_INET_LOCAL_OUT);
	set_nf_hook_ops(&nf_hook_post_routing, nf_hookfn_post_routing, NF_INET_POST_ROUTING);

	nf_register_hook(&nf_hook_pre_routing);
	nf_register_hook(&nf_hook_local_in);
	nf_register_hook(&nf_hook_forward);
	nf_register_hook(&nf_hook_local_out);
	nf_register_hook(&nf_hook_post_routing);

	return 0;
}

static void __exit exit_pitta(void)
{
	printk(KERN_INFO "exit pitta module\n");

	nf_unregister_hook(&nf_hook_pre_routing);
	nf_unregister_hook(&nf_hook_local_in);
	nf_unregister_hook(&nf_hook_forward);
	nf_unregister_hook(&nf_hook_local_out);
	nf_unregister_hook(&nf_hook_post_routing);
}

module_init(init_pitta);
module_exit(exit_pitta);
