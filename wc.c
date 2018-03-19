#include <stdio.h>
#include <unistd.h>
#include <string.h>

int charNum = 0;  //�ַ��� 
int wordNum = 0;  //������ 
int lineNum = 0;  //���� 
int o=0;          //�Ƿ���� 
int l=0;
int w=0;
int c=0;          //����С����ʻ����ַ� 
int countChar(char *file) {	  //ͳ���ַ��� 
	FILE *fp = fopen(file,"r");   //���ļ� 
	char a;
	while (!feof(fp))  //���������ļ���ÿ��һ���ַ����ַ���+1 
	{
		a = fgetc(fp);
		charNum++;
	}
	fclose(fp);  //�ر��ļ� 
}
int countWord(char *file) {	  //ͳ�Ƶ����� 
	FILE *fp = fopen(file,"r");
	char a,b;
	while (!feof(fp))  //�����ļ� 
	{
		a = fgetc(fp);   //a�洢�����ļ��ַ� 
		if ((a==' '||a==','||a==';'||a==':'||a=='\n'||a=='\t'||a=='('||a==')')&&((b>'A'&&b<'Z')||(b>'a'&&b<'z')))  //�ָ����� 
		{
			wordNum++;
		}
		b=a;    //��b�洢��һ���ַ� 

	}
	fclose(fp);
}
int countLine(char *file) {	  //ͳ������ 
	FILE *fp = fopen(file,"r");
	char a;
	while (!feof(fp))     //ÿ����һ��'\n'��������+1 
	{
		a = fgetc(fp);
		if(a=='\n')
			lineNum++;
	}
	fclose(fp);  
}
int writeOutput(char *filename)  //�����Ϣ��ָ���ĵ� 
{
    FILE *fpWrite = fopen(filename,"w");
    if (fpWrite == NULL)    //���ļ�ʧ�ܣ�����-1 
    {		  
		return -1;
	}
	if (l)     //����l��w��c��ֵ�����ָ���ļ����С����ʡ��ַ���Ŀ 
    {
        fprintf(fpWrite, "Lines: %d\n", lineNum);
    }
    if (w)
    {
        fprintf(fpWrite, "Words: %d\n", wordNum);
    }
    if (c)
    {
        fprintf(fpWrite, "Chars: %d\n", charNum);
    }
    //fprintf(fpWrite, "Lines: %d\n", lineNum);
    //fprintf(fpWrite, "Words: %d\n", wordNum);   
    //fprintf(fpWrite, "Chars: %d\n", charNum);
    fclose(fpWrite);
}

int main(int argc,char *argv[])
{
 
    int opt=0;
    char inFile[20];   //������ļ� 
    char outFile[20];   //������ļ� 

	//printf("%d\n",argc);
	while((opt=getopt(argc,argv,"l:w:c:o:")) != -1)  //��ȡ����̨���� 
    {
        switch(opt)
        {

            case 'l':    //��ȡ����Ϊl��l=1����������� 
            	l=1;
				strcpy(inFile,optarg); 
           		countLine(inFile);
				printf("Lines: %d\n", lineNum);  
           		break;  
    		case 'w':   //��ȡ����Ϊw��w=1������������� 
        		w=1;
           	 	strcpy(inFile,optarg);
				countWord(inFile);
				printf("Words: %d\n", wordNum); 
     		    break;  
           	case 'c':   //��ȡ����Ϊc��c=1��������ַ��� 
            	c=1;
				strcpy(inFile,optarg);
				countChar(inFile);
             	printf("Chars: %d\n", charNum-1);
            	break;
            case 'o':  //��ȡ����Ϊo��oΪ1������ĵ� 
            	o = 1;
             	strcpy(outFile,optarg);  
        }
	}		
    
    
    if (o)
        writeOutput(outFile); 
	else
	{
		char *fp="result.txt";
		
		//FILE *fp=fopen("result.txt","w");
		//strcpy(fp,optarg);
		writeOutput(fp);
	}

    return 0;
}
