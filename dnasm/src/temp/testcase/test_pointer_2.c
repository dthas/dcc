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

	struct ttt *p;

	p = &mec;

	c = 1;
	d = 4;

	p->cc = c;

	a = p->cc + d;

	r11(a);
	

	return;
}



