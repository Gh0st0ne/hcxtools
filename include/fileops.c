#define _GNU_SOURCE
#include <stdbool.h>
#include <stdint.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "fileops.h"

/*===========================================================================*/
int getmagicnumber(int fd)
{
int res;
magicnr_t mnr;

res = read(fd, &mnr, 4);
if(res != 4)
	{
	return 0;
	}
return mnr.magic_number;
}
/*===========================================================================*/
void fwritetimestamphigh(uint32_t tshigh, FILE *fhd)
{
time_t pkttime;
struct tm *pkttm;

char tmbuf[64];

if(tshigh != 0)
	{
	pkttime = tshigh;
	pkttm = localtime(&pkttime);
	strftime(tmbuf, sizeof tmbuf, "%d%m%Y", pkttm);
	fprintf(fhd, "%s:", tmbuf);
	}
else
	{
	fprintf(fhd, "00000000:");
	}
return;
}
/*===========================================================================*/
void fwriteaddr1addr2(uint8_t *mac1, uint8_t *mac2, FILE *fhd)
{
int p;

for(p = 0; p< 6; p++)
	{
	fprintf(fhd, "%02x", mac1[p]);
	}
fprintf(fhd, ":");
for(p = 0; p< 6; p++)
	{
	fprintf(fhd, "%02x", mac2[p]);
	}
fprintf(fhd, ":");
return;
}
/*===========================================================================*/
void fwriteessidstr(uint8_t len, unsigned char *essidstr, FILE *fhd)
{
int p;

if(isasciistring(len, essidstr) != false)
	{
	fprintf(fhd, "%s\n", essidstr);
	}
else
	{
	fprintf(fhd, "$HEX[");
	for(p = 0; p < len; p++)
		{
		fprintf(fhd, "%02x", essidstr[p]);
		}
	fprintf(fhd, "]\n");
	}
return;
}
/*===========================================================================*/
