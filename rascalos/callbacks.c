#include <rascalos.h>

static struct rascalos_callbacks local_rascal_callbacks;

void rascalos_register_tcp_port_callback(void (*consensus)(void))
{
	local_rascal_callbacks.consensus = consensus;
}
EXPORT_SYMBOL(rascalos_register_tcp_port_callback);

void rascalos_call_consensus(void)
{
	local_rascal_callbacks.consensus();
}
