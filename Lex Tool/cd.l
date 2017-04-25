%{
	int floats=0,octal=0,hex=0,digit=0,chars=0,suffix=0;
	char arr_octal[512][64];
	char arr_digit[512][64];
	char arr_floats[512][64];
	char arr_chars[512][64];
	char arr_hex[512][64];
	char arr_suffix[512][64];
%}
Digit [0-9]+
Char [a-zA-Z]
Float[0-9]+\.[0-9]+
Octal 0([0-7])+
HexaDec 0x[0-9A-F]+
Suffix [0-9]+(l|u|ul|lu)
%%

{Octal} {yytext; strcpy(arr_octal[octal], yytext); octal++;}
{Float} {yytext; strcpy(arr_floats[floats], yytext); floats++;}
{HexaDec} {yytext; strcpy(arr_hex[hex], yytext); hex++;}
{Digit} {yytext; strcpy(arr_digit[digit], yytext); digit++;}
\'{Char}\'|\"{Char}\" {yytext; strcpy(arr_chars[chars], yytext); chars++;}
{Suffix} {yytext; strcpy(arr_suffix[suffix], yytext); suffix++;}
\n ;
. ;
%%

int main()
{
yyin = fopen("text.txt", "r");
 yylex();

FILE *file = fopen("output.txt", "w");
	int i;
	fprintf(file, "Number of octals is %d.\n", octal);
	for(i=0; i<octal; i++)
		fprintf(file, "%s ", arr_octal[i]);
	fprintf(file, "\n\n");
	
	fprintf(file, "Number of floats is %d.\n", floats);
	for(i=0; i<floats; i++)
		fprintf(file, "%s ", arr_floats[i]);
	fprintf(file, "\n\n");
	
	fprintf(file, "Number of chars is %d.\n", chars);
	for(i=0; i<chars; i++)
		fprintf(file, "%s ", arr_chars[i]);
	fprintf(file, "\n\n");
	
	fprintf(file, "Number of integers is %d.\n", digit);
	for(i=0; i<digit; i++)
		fprintf(file, "%s ", arr_digit[i]);
	fprintf(file, "\n\n");
	
	fprintf(file, "Number of hexadecimal numbers is %d.\n", hex);
	for(i=0; i<hex; i++)
		fprintf(file, "%s ", arr_hex[i]);
	fprintf(file, "\n\n");
	
	fprintf(file, "Number of suffix is %d.\n", suffix);
	for(i=0; i<suffix; i++)
		fprintf(file, "%s ", arr_suffix[i]);
	fprintf(file, "\n\n");
	fclose(file);
}
