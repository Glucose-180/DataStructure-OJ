#include <stdio.h>

typedef enum Bool { False,True } bool_t;

size_t remove_annotation(FILE* ifp, FILE* ofp);

int main(int argc, char* argv[])
{
	FILE* ifp = stdin, *ofp;
	if (argc < 2 || (ofp = fopen(argv[1], "w")) == NULL)
		ofp = stdout;
	remove_annotation(ifp, ofp);
	return 0;
}

/* Remove annotations in C code
*  Return count of bytes written */
size_t remove_annotation(FILE* ifp, FILE* ofp)
{
	/* Status */
	bool_t in_annotation = False, in_string = False, end_of_annotation = False;
	/* Flags of last char */
	bool_t slash = False, bslash = False, star = False, sqm = False;
	int c;
	size_t ymr = 0U;

	while ((c = fgetc(ifp)) != EOF)
	{
		if (in_annotation == False && in_string == False)
		{
			switch (c)
			{
			case '/':
				break;
			case '\\':
				if (slash == True && end_of_annotation == False)
					fputc('/', ofp), ++ymr;
				fputc(c, ofp), ++ymr;
				break;
			case '*':
				if (slash == True && end_of_annotation == False)
					in_annotation = True;
				else
					fputc(c, ofp), ++ymr;
				break;
			case '\"':
				if (bslash == False && sqm == False)
					in_string = True;
				if (slash == True && end_of_annotation == False)
					fputc('/', ofp), ++ymr;
				fputc(c, ofp), ++ymr;
				break;
			default:
				if (slash == True && end_of_annotation == False)
					fputc('/', ofp), ++ymr;
				fputc(c, ofp), ++ymr;
				break;
			}
			end_of_annotation = False;
		}
		else if (in_annotation == True)
		{
			end_of_annotation = True;
			if (c == '/' && star == True)
				in_annotation = False;
		}
		else if (in_string == True)
		{
			fputc(c, ofp), ++ymr;
			if (bslash == False && c == '\"')
				in_string = False;
			end_of_annotation = False;
		}

		/* Set flags */
		slash = (c == '/');
		sqm = (c == '\'' && bslash == False);
		/* Note that sqm is special	*/
		bslash = (c == '\\');
		star = (c == '*');
	}
	return ymr;
}