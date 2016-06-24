#include <stdio.h>
#include <pcap.h>
#include <WinSock2.h>
#include <IPHlpApi.h>
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "wpcap.lib")

void ListAdapters()
{
	pcap_if_t *alldevs;
	pcap_if_t *d;
	int i = 0;
	char errbuf[PCAP_ERRBUF_SIZE];
	char szGateIPAddr[16];
	char *p;
	char szIPAddr[16];
	unsigned char ucPhysicalAddr[6];
	
	if (pcap_findalldevs(&alldevs, errbuf) == -1)
	{
		fprintf(stderr, "Error in pcap_findalldevs: %s\n", errbuf);
		return;
	}
	for (d = alldevs; d; d = d->next)
	{
		if (d->addresses != NULL && (p = strchr(d->name, '{')) != NULL && getada)
		{
			for (int j = strlen(d->description) - 1; j > 0; j--)
			{
				if (d->description[j] == 0x20)
					d->description[j] = ' ';
			}
			printf("\n  %d. %s\n\tIP Address. . . . . : %s\n", i, d->description, szIPAddr);
			printf("\tPhysical Address. . : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X\n",
				ucPhysicalAddr[0], ucPhysicalAddr[1], ucPhysicalAddr[2],
				ucPhysicalAddr[3], ucPhysicalAddr[4], ucPhysicalAddr[5]);
			printf("\tDefault Gateway . . : %s\n", szGateIPAddr);
			i++;
		}
	}

	if (i == 0)
	{
		printf("\nNo interfaces found! Make sure WinPcap is installed.\n");
		return;
	}

	pcap_freealldevs(alldevs);// Õ∑≈Õ¯ø®¡¥±Ì
}
