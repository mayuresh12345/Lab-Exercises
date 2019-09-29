%{
	#include <stdio.h>
	int pos_int = 0;
	int neg_int = 0;
	int pos_flt = 0;
	int neg_flt = 0;
%}

%%
[0-9]*\.[0-9]+ {pos_flt++;}
-[0-9]*\.[0-9]+ {neg_flt++;}
[1-9][0-9]* {pos_int++;}
-[1-9][0-9]* {neg_int++;}
%%

int main(int argc, char** argv)
{
	yylex();
	printf("Pos_int = %d\tNeg_int = %d\tPos_flt = %d\tNeg_flt = %d\n", pos_int, neg_int, pos_flt, neg_flt);
}

int yywrap()
{
	return 1;
}