int t_main(int c, char d);
int r11(int a);
extern int printi(int w);
extern int printcr(int w);

int r11(int a)
{
	int x, y;

	x = a;

	x = x + 7;

	y = x + 3;

	printi(y);

	printcr(x);

	return;
}

int t_main(int c, char d)
{
	int a;
	struct ttt
	{
		int cc;
		char dd;	
				
	} mec;

	int dd[3];

	c = 1;
	d = 4;
		
	dd[2] = c + d;

	c = dd[2];

	r11(c);

	return;
}



