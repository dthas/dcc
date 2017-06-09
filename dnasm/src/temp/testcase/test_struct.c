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
		int dd;	
				
	} mec;

	a = c;

	c = 1;
	d = 4;

	mec.cc = c + d;
	mec.dd = d;

	c = mec.cc;
	a = mec.dd;

	

	r11(a);

	return;
}



