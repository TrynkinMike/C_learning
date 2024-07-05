#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mem.h>
#define rand_max 0x7fff

int* Delete(int* str)
{
	int i,j,n;
	n=str[0]-1;
	for(i=n;i>0;i--)//перебор всех элементов с конца (кроме нулевого)
	{	
		if (i%2==1)//если сейчас на нечётном индексе (на элементе который надо удалить)
		{
			if (i!=n)//если сейчас не на последнем элементе начального массива
			{        
				for (j=i;j<str[0];j++)//сдвигаем элементы справа от i-го на 1 влево (см циклический сдвиг)
				{
					str[j]=str[j+1];
				}
			} 
			str[0]--;//уменьшаем длину	
		}
	}
	str = (int*)realloc(str,(str[0])*sizeof(int));//обрезаем массив
	if (!str) return NULL;
	return str;
	free(str);
}

int* Add(int* str, int min, int max, int k)
{
	int i;
	
	//изменяем длину массива
	str = (int*)realloc(str,(str[0]+k)*sizeof(int));
	if (!str) return NULL;
	//изменяем нулевой элемент нового массива (увеличиваем длину до нужной)
	str[0] = str[0]+k;
	//добавляем k новых элементов
	for (i=str[0]-k;i<str[0];i++)
	{
		str[i] = (int)(((float)rand() / RAND_MAX) * (max - min) + min);
	}
	//если память не выделилась - возвращаем нулевой указатель
	if (!str) return NULL;
	return str;
	free(str);
}

void Shift(int* str, int m)
{
	int i,j,temp;
	//сдвиг
	j=0;
	do
	{
		temp = str[str[0]-1];//во временную переменную - последний элеимент изменяемой части строки
		for (i=str[0]-1;i>1;i--)
		{
			str[i] = str[i-1];//каждому элементу присваивается предыдущий (кроме первого, он меняется потом)
		}
		str[1] = temp;//первому элементу изменяемой строки присваивается временнная перем.(последний элемент)
		j++;
	} while (j<m);//повторяем столько раз, сколько ввёл пользователь
	
}

void Change(int* str)
{
	int i,s = 0;
	
	//считаем сумму эл-тов
	for (i=1;i<str[0];i++)
	{
		s+=str[i];
	}
	
	//присваиваем всем отрицательным эл-там целую часть среднего арифметического массива
	for (i=1;i<str[0];i++)
		if (str[i] < 0)
		{
			str[i] = s/(str[0]-1);
		}
}
int main() 
{
	int i, j,SIZEA,SIZESTR;
	int min,max;
	int k,m;
	system("color F0");
 	srand(time(0));
	
	printf("Input the size of array of pointers\n");
	scanf ("%d",&SIZEA);
	if (SIZEA<=0)
	{
		do
		{
			printf("Wrong value! Input the size of array of pointers again\n");
			scanf ("%d",&SIZEA);
		} while (SIZEA<=0);
	}
	
	printf("Input the size of string of array\n");
	scanf ("%d",&SIZESTR);
	if (SIZESTR<=0)
	{
		do
		{
			printf("Wrong value! Input it again\n");
			scanf ("%d",&SIZESTR);
		} while (SIZESTR<=0);
	}
	
	//создаём массив указателей размером SIZEA
    int** A = (int**) malloc(SIZEA * sizeof(int*));
	if (!A) return NULL;
	//для каждого элемента-указателя создаём свой массив
 	//размер которого SIZESTR
    for (i = 0; i < SIZEA; i++)
    {
    	A[i] = (int*) malloc(SIZESTR * sizeof(int));
    	if (!A[i]) return NULL;
	}
    
	
	//всем нулевым элементам строк присваиваем значение длин строк
	for (i=0;i<SIZEA;i++)
	{               
		A[i][0] = SIZESTR;
	}

	//заполнение случ числами в промежутке
	printf("Type the lowest and highest value (if with the particular part, this part will be removed)\n");
	scanf("%d %d",&min,&max);
	if (min>=max)
	{
		i=max;
		max=min;
		min=i;
	}
	if (max == 0) max++;
	if (min == 0) min++;
	for (i=0;i<SIZEA;i++)
	{
		for (j = 1; j < SIZESTR; j++)
		{
			A[i][j]= (int)(((float)rand() / RAND_MAX) * (max - min) + min);

		}
	}
	
	//ввод числа доп.элементов
	printf("Input the count of additional elements\n");
	scanf ("%d",&k);
	if (k<=0)
	{
		do
		{
			printf("Wrong value! Input the count of additional elements again\n");
			scanf ("%d",&k);
		} while (k<=0);
	}
	
	//ввод сдвига
	printf("Input the shift distance\n");
	scanf ("%d",&m);
	if (m<=0)
	{
		do
		{
			printf("Wrong value! Input the shift distance again\n");
			scanf ("%d",&m);
		} while (m<=0);
	}
	
	//выводим двумерный массив (изначальный)
	printf("First array:\n");
    for (i = 0; i < SIZEA; i++) 
    {
        for (j = 0; j < A[i][0]; j++)
        {
        	printf("\t%d", A[i][j]);
		}
        printf("\n");
    }
    
    //проводим операции над строками
	for (i = 0; i< SIZEA;i++)
	{
		switch(i%4+1)
		{
			case 1:
				A[i]=Delete(A[i]);
				break;
			case 2:
				A[i]=Add(A[i],min,max,k);
				break;
			case 3:
				Shift(A[i],m);
				break;
			case 4:
				Change(A[i]);
				break;
		}
	}
    
    //выводим конечный массив
  	printf("Second array:\n");
    for (i=0;i<SIZEA;i++)    
    {          
    	printf("%d - string: ",i);
    	for (j=0;j<A[i][0];j++)
    		printf("%d ",A[i][j]);
		printf("\n");
	}

	//очищаем сначала под-массивы
    for (i = 0; i < SIZEA; i++)
    {
    	free(A[i]);
	}
    //потом очищаем основной массив
	free(A);
	A = NULL;

	return 0;
}
