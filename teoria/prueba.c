#include <stdio.h>
#include "Libft/libft.h"

int main()
{
	char *new_order;
	char *order = "<infile comando <infile2 >outfile";
	char *infile;
	char **outfile;
	int i;
	int j;
	int k;
	int h;

	i = 0;
	j = 0;
	k = 0;
	h = -1;

	while (order[i])
	{
		//los espacios que?
		while(order[i] == ' ')
			i++;
		if(order[i] == '<') //INFILE
		{
			i++;
			if (order[i] == '<') //como se luego que es here_doc?
			{
				printf("append\n");
			}
			while(order[i] == ' ')
				i++;
			j = i;
			while(order[i] != ' ')
				i++;
			infile = ft_substr(order, j, i - j);
		}	
		else if(order[i] == '>') //OUTFILE
		{
		 	i++;
			if (order[i] == '>') //como se luego que es append?
			
				printf("append\n");
 			while(order[i] == ' ')
			   i++;
  			while(order[i] == ' ')
              i++;
   		outfile[k] = ft_substr(order, j, i - j);
		}
		/*else //COMMAND 
		{
			while(order[i] == ' ')
				i++;
            j = i;
            while(ft_isascii(order[i]))
				i++;
			new_order = ft_strjoin(new_order, ft_substr(order, j, i - j));
		}*/
		i++;
	}
	printf("infile = %s\n", infile);
	printf("outfile 1 = %s\n", outfile[0]);
	printf("outfile 2 = %s\n", outfile[1]);
	printf("new_order = %s\n", new_order);
	return (0);
}
