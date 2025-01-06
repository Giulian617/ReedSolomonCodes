// Ilie Dumitru

#ifndef RS_PRECALC_FIELD_MULT_TABLE
#define RS_PRECALC_FIELD_MULT_TABLE

int ff_times[SIGMA][SIGMA];
int ff_inv[SIGMA];

void ff_precalc()
{
	const int MOD=285;

	int i, j;
	auto multiply = [](int x, int y)
	{
		int total=0;

		while(y)
		{
			total^=x<<(__builtin_ctz(y));
			y&=y-1;
		}

		while(total>255)
			total^=MOD<<(23-__builtin_clz(total));

		return total;
	};

	for(i=1;i<SIGMA;++i)
	{
		for(j=1;j<SIGMA;++j)
			ff_times[i][j]=multiply(i, j);
		for(j=1;j<SIGMA;++j)
			if(ff_times[i][j]==1)
				ff_inv[i]=j;
	}
}

#endif // RS_PRECALC_FIELD_MULT_TABLE
