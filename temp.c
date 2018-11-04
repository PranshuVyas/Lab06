#include <sys/types.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "ifttt.h"
#include <time.h>

int main(int argc, char *argv[])
{
double max, min, ctemp, ptemp;
FILE *fp;
int n,i,digit,first,math,check;
char buf[101],c;
double mul, sum;
double time1, time2;
char maxt[10],mint[10],curt[10];
first = 1;
time1 = time(NULL);
while(1)
{
time2 = time(NULL);

if((time2-time1)>=1.0){
time1 = time2;
if((fp = fopen("/sys/bus/w1/devices/28-021312ddbeaa/w1_slave", "r")) == (FILE *)NULL)
{
	perror("open of file failed");
	(void) exit(1);
}
n = fread(buf, 1, 100, fp);
if(n==0)
{
	perror("read fails");
	exit(1);
}

buf[n] = '\0';
i = 69;
sum = 0;
mul = 10;

while(i<(n-1)){

digit = buf[i] - '0';
sum = sum + (digit * mul);
mul = mul/10;
i++;
}
(void) fclose(fp);
printf("current temp = %f\n", sum);
if(first)
{
ctemp = sum;
ptemp = sum;
max = sum;
min = sum;
first = 0;
}
else
{
 ctemp = sum;
 if(ctemp > max){
	max = ctemp;
 }
 if(ctemp < min){
	min = ctemp;
 }
 if((ctemp > (ptemp+1)) || (ctemp < (ptemp-1))){
 
	sprintf(maxt,"%f",max);
	sprintf(mint,"%f",min);
	sprintf(curt,"%f",ctemp);
	printf("change previous = %f, current = %f , min = %f, max = %f \n", ptemp, ctemp, min, max); 
	ifttt("https://maker.ifttt.com/trigger/temp_change/with/key/nwcUZyfI71f61Zxa99rUvoAyMt7ch43R3hQRgkY1m5C","my1", "my 2", "my 33333");
	ptemp = ctemp; 
 }
 
}
}
}
return 0;	


}
