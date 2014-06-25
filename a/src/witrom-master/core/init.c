/*
 *  comment here
 */

#include <stdio.h>
#include <delay.h>
#include <loader.h>
#include <uart/uart.h>

extern struct loader_opt g_loader_begin[], g_loader_end[];

static int load_bl2(char key);

int main(void)
{
	int i;

	read_cpu_id();

#if 0
// #ifdef CONFIG_SDRAM_TESTING
	volatile __u32 *p = VA(SDRAM_BASE);

	while (p < (__u32 *)(SDRAM_BASE + SDRAM_SIZE)) {
		__u32 val1 = *p, val2;

		val2 = ~val1;
		*p = val2;
		val1 = *p;

		if (val1 != val2)
			printf("bad memory @ 0x%x\n", p);

		p++;
	}
#endif

	for (i = 0; i < 0x100; i++) {
		char key;

		if (uart_rxbuf_count() > 0) {
			key = uart_recv_byte();

#ifdef CONFIG_LOADER_MENU
			do {
				char nkey;
				struct loader_opt *loader;
#endif

				load_bl2(key);

#ifdef CONFIG_LOADER_MENU
				printf("\nBoot Menu:\n");

				for (loader = g_loader_begin; loader < g_loader_end; loader++)
					printf("  [%c] %s\n", loader->ckey[0], loader->prompt);
				printf("  [q] Default\nEnter Your Choice\n");

				while (key == (nkey = uart_recv_byte()));

				key = nkey;
			} while ('q' != key);

			break;
#endif
		}

		udelay(0x1000);
	}

	load_bl2(CONFIG_DEFAULT_LOADER);

	return 'm';
}

static inline void boot()
{
	printf("\n");
	((void (*)())CONFIG_BL2_START_MEM)();
}

int load_bl2(char key)
{
	int ret;
	struct loader_opt *loader;

	// case ignore
	if ('A' <= key && key <= 'Z')
		key += 'a' - 'A';

	for (loader = g_loader_begin; loader < g_loader_end; loader++) {
#ifdef CONFIG_DEBUG
		printf("%c: 0x%x\n", loader->ckey[0], loader->main);
#endif

		if (loader->ckey[0] == key) {
#ifdef CONFIG_LOADER_MENU
			// fixme: prompt for RAM/ROM
			printf("Loading from %s ...\n", loader->prompt);
#endif

			loader->load_addr = (void *)CONFIG_BL2_START_MEM;

			ret = loader->main(loader);
			if (ret < 0)
				return ret;

			boot();
		}
	}

	return 0;
}

#ifdef CONFIG_RAM_LOADER
static int ram_loader(struct loader_opt *loader)
{
	boot();
	return -1;
}

REGISTER_LOADER(m, ram_loader, "RAM/ROM");
#endif
