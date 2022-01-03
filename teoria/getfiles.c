
typedef struct s_prueba
{
	char *infile;//no es array porque omite pero no los modifica
    char **outfile;//es array porque bash los crea aunque los omita.
    int *infile;//
    int **outfile;//los fd de los archivos
}t_prueba


char *get_files(char *order, t_prueba *prueba)
{
    char *new_order;
    int i;
    int j;

    new_order = NULL; //(malloc???)
    while(order[i])
    {
        if (strchr(order[i], '<')) //Encuentra piquito infile. Guarda todo y avanza su len
 		{
            j = i;
			i++;
            while (strchr(order[i], ' '))
			   	i++;
            while (ft_isascii(order[i])
				i++;
            prueba->infile = substr(order, j, i);//lo coge
			printf("INFILE : %s");
        }
        if (strchr(order, '>'))//Encuentra piquito infile. Guarda todo y avanza su len
		{
        shell->my_pro->outfile = //avanza en la string desde piquito, (espacio), palabra ;
        order = //corta strlen de piquito + espacio si hay + palabra
        }
        else//es comando
        {
            new_order = strlcat(new_order, (cacho que lea ASCII) //O JOIN//
        }

        i++;
    }
    return (new_order);
}


int main()
{
	char *order; //churro que entra el hijo.
	t_prueba prueba;

	order = "<infile comando flag <infile >outfile";
	
	get files(order, &prueba);
	return (0);
}
