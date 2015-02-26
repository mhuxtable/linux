#ifndef RASCALOS_H_
#define RASCALOS_H_

#include <linux/module.h>

/* Callback functions */
struct rascalos_callbacks {
	void (*consensus)(void);
};

void rascalos_register_tcp_port_callback(void (*)(void));
void rascalos_call_consensus(void);

#endif
