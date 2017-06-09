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

	c  = 3;
	d  = 5;

	a  = d + c;

	if(d>=c)
		r11(d); 
	else
		r11(c);

	

	return;
}



