#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//нахождение части слова в тексте(ВО ВСЁМ ТЕКСТЕ, НЕСАМОСТОЯТЕЛЬНАЯ ФУНКЦИЯ, МОЖЕТ НАЙТИ В ИНОЙ ПОСЛ-ТИ)
int find(const char* strPart, const char* word)//требует слово (именно слово) как аргумент, но может работать и на весь текст
{
	int i,count;
	i=0;
	count=0;
	while (i!=strlen(strPart))
	{
		if (strncmp(strPart + i,word,strlen(word))==0)
		{
			count++;
		}
		i++;
	}
	return count;
}

//явдяется ли знак разделителем
int IsRazdel(char ch)
{
	if ((ch == '.') || (ch == '!') || (ch == '?') || (ch == '\0') || (ch == ' ') || (ch == ','))
		return ch;//возврат false
	else 
		return 0;//возврат true
}

//является ли словом последовательность символов word
int IsWord(const char* word, int n)
{
	int i = 0;
	int t = 0;
	while (i!=n)/*перебор всего слова*/
	{
		if (isalpha(word[i]) == 0)/*если встречена не буква*/
		{
			t = 0;/*возврат false*/
			break;
		}
		else
		{
			t = 1;/*возврат true*/
		}
		i++;
	}
	
	return t;
}

//число вхождений части слова в слова текста (задание 1)
int info(const char* text, const char* word)
{
	int i = 0;//параметр цикла
	int j;
	int n = 0;//счётчик длины слова
	int count = 0;//счётчик вхождений части слова в текст
	char* DefinatelyWord = (char*) malloc(sizeof(char));//создаём массив чаров (слово как часть текста)
	while (i<strlen(text))//перебираем весь текст по символу
	{
		
		if (!IsRazdel(text[i]))//если не нашли разделитель
		{
			n = 0;//обнуляем длину слова
			j = i;//запоминаем позицию
			while (IsRazdel(text[j]) == 0 && j<strlen(text))//и двигаемся от неё вправо до разделителя/конца текста
			{
				j++;// перемещаемся на 1 вправо
				n++;//увеличиваем длину слова
			}
			DefinatelyWord = realloc(DefinatelyWord,n*sizeof(char));//изменяем длину слова до нужной
			DefinatelyWord = memcpy(DefinatelyWord,text + i,n * sizeof(char));//переносим часть текста в слово
			if (!DefinatelyWord) exit;
			if (IsWord(DefinatelyWord,n))//если в слове нет цифр (слово по заданию)
			{
				count+=find(DefinatelyWord,word);//ищем в нём число вхождений части слова
			}
		}
		i=i+n+1;//переход сразу к другому слову в тексте (с учётом того, что между ними лишь один знак)
	}
	free(DefinatelyWord);
	return count;
}

//является ли символ концом предложения
int IsEnd(char ch)
{
	if ((ch == '.') || (ch == '!') || (ch == '?') || (ch == '\0'))
		return 0;
	else
		return ch;
}

//создание массива из всех первых слов предложения (задание 2)
char** firsts(char* text)
{
	int WordCount = 0;
	char* FirstWord = (char*) malloc(sizeof(char));
	char** F = (char**) malloc(sizeof(char*));
	int i = 0;
	int j = 0;
	int n = 0;
	int flag = 0;
	while (i<strlen(text))//перебор всех символов текста
	{
		if ((i==0) || (IsEnd(text[i-1])==0) || (flag == 1))//если сейчас в начале текста или на букве после знака конца предложения или на следующум слове (flag = 1)
		{
			n = 0;
			j = i;
			while (IsRazdel(text[j]) == 0 && j<strlen(text))//и двигаемся от неё вправо до разделителя/конца текста
			{
				j++;// перемещаемся на 1 вправо
				n++;//увеличиваем длину слова
			}
			FirstWord = (char*)realloc((char*)FirstWord,(n)*sizeof(char));//изменяем размер слова
			if (!FirstWord) puts("Out of mem"), exit(1);
			memcpy(FirstWord,text + i,(n) * sizeof(char));//переносим часть текста в слово
			//printf("n = %d and word = (%s)\n",n,FirstWord);
			if (IsWord(FirstWord,n))//если найденная последовательность это слово
			{
				if (n!=strlen(FirstWord))//если памяти выделилось больше чем надо, то выделяем заново (со 2 раза ОБЫЧНО работает)
					FirstWord = (char*)realloc((char*)FirstWord,(n)*sizeof(char));
				FirstWord[n] = '\0';
				//printf("n = %d and word = (%s)\n",strlen(FirstWord),FirstWord);
				WordCount++;//увеличиваем количество слов
				F = realloc(F,(WordCount+1)*sizeof(char*));//расширяем массив под новое число слов
				F[WordCount] = (char*)malloc((n)*sizeof(char));//задаём размер слова
				
				strcpy(F[WordCount],FirstWord);//копируем слово из текста в массив
				flag = 0;
			}
			else
			{
				i=i+n;
				flag = 1;
			}	
		}
		i++;
	}
	
	F[0] = WordCount;//целочисленное значение количества первых слов
	
	return F;
}

//является ли числом последовательность символов word
int IsChislo(const char* word, int n)
{
	int i = 0;
	int t = 0;
	while (i!=n)/*перебор всего числа*/
	{
		if (isdigit(word[i]) == 0)/*если встречена не цифра*/
		{
			t = 0;/*возврат false*/
			break;
		}
		else
		{
			t = 1;/*возврат true*/
		}
		i++;
	}
	
	return t;
}

char* Delete(char* text)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int firstchar = 0;
	int lastchar = 0;
	int n;
	int predlen;
	char* number = (char*) malloc(sizeof(char));
	while (i<strlen(text)-1)//пока не дошли до конца текста
	{
		if (IsEnd(text[i])==0 /*&& i<strlen(text)*/)//если на символе конца предложения, то начало предложения на следующем символе
			firstchar = i+1;
		if (IsRazdel(text[i]))//если на разделителе, то перемещаемся от него правее
			i++;
		//printf("firstchar = %d\n",firstchar);
		n = 0;//обнуляем длину числа
		j = i;//смещаем первый индекс для поиска числа
		while (IsRazdel(text[j]) == 0 && j<strlen(text))//пока не дошли до разделителя после числа или конца всего текста
		{
			n++;//увеличиваем длину числа
			j++;//смещаемся вправо на 1
		}
		number = (char*)realloc((char*)number,(n)*sizeof(char));//изменяем размер числа
		memcpy(number,text + i,(n) * sizeof(char));//переносим часть текста в число
		number[n] = '\0';
		if (IsChislo(number,n))//если нашли именно число
		{
			lastchar = j;//начинаем перебор от его конца
			while (IsEnd(text[lastchar])!=0)//пока не дошли до конца данного предложения
			{
				lastchar++;//переходим к следующему символу
			}
			predlen = lastchar - firstchar;//нашли длину предложения, что надо удалить (сдвиг влево)
			memcpy(text+firstchar - 0,text+lastchar+1,(strlen(text))*sizeof(char));//переносим влево нужное число символов
			i= firstchar;//после удаления смещаться не надо (анализируем уже это предложение)
			firstchar = lastchar - predlen;//запомнили индекс первого символа предложения после удаления
			printf("number = %s\n",number);
			printf("firstchar = %d\n",firstchar);
			puts(text);
		}
		else
		{
//			printf("firstchar = %d\n",firstchar);
			i=i+n;//если ничего не удаляли, то перемещаемся вправо на длину "числа"
			printf("i = %d\n",i);
		}
	}
	return text;
}

int main(int argc, char** argv)
{
	system("chcp 1251");
	setlocale(LC_ALL, "rus");
	setlocale(LC_ALL,"Russian");
	
	if ((argc>2) && (strlen(argv[1])>0))
	{
		puts("You wrote this:");
		puts(argv[1]);
		
		if (strcmp(argv[2],"-info") == 0)
		{
			if (IsWord(argv[3],strlen(argv[3])))
				printf("Count of word (%s) is %d\n",argv[3],info(argv[1],argv[3]));//функция 1
			else
				{
					printf("The info function argument (%s) is not a word!\n",argv[3]);
				}
		}
		
		else if (strcmp(argv[2],"-create") == 0)
		{
			char**FirstWords;
			FirstWords = firsts(argv[1]);//функция 2 (БУКВА "Я" МАЛАЯ НЕ СЧИТАЕТСЯ ЗА БУКВУ Ф-ЕЙ isalpha!!!!!!!!!!!!!)
			for (int i=1;i<=FirstWords[0];i++)
				printf("%d word is (%s)\n",i,FirstWords[i]);
		
			int erase = FirstWords[0];//число элементов, что надо будет очистить
			for (int i=1;i<=erase;i++)//очистка массива задания 2
				free(FirstWords[i]);
			free(FirstWords);
		}
		
		else if (strcmp(argv[2],"-delete") == 0)
		{
			char* Deleted;
			Deleted = Delete(argv[1]);
			printf("Changed string is (%s)",Deleted);//функция 3
//			free(Deleted);
		}
		
		else
			printf("Wrong second argument!");
	}
	else
		printf("Wrong arguments!");
}