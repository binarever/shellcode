void main()
{
	int i=0;
	char stuffing[60];

	for (i=0;i<56;i+=4)
	{
		*(long *) &stuffing[i]=0x0040057f;
	}
	puts(stuffing);
	
}
