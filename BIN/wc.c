#include <stdio.h>
#include <unistd.h>
#include <string.h>

int charNum = 0;  //字符数 
int wordNum = 0;  //单词数 
int lineNum = 0;  //行数 
int o=0;          //是否输出 
int l=0;
int w=0;
int c=0;          //输出行、单词或者字符 
int countChar(char *file) {	  //统计字符数 
	FILE *fp = fopen(file,"r");   //打开文件 
	char a;
	while (!feof(fp))  //遍历整个文件，每有一个字符，字符数+1 
	{
		a = fgetc(fp);
		charNum++;
	}
	fclose(fp);  //关闭文件 
}
int countWord(char *file) {	  //统计单词数 
	FILE *fp = fopen(file,"r");
	char a,b;
	while (!feof(fp))  //遍历文件 
	{
		a = fgetc(fp);   //a存储所得文件字符 
		if ((a==' '||a==','||a==';'||a==':'||a=='\n'||a=='\t'||a=='('||a==')')&&((b>'A'&&b<'Z')||(b>'a'&&b<'z')))  //分隔单词 
		{
			wordNum++;
		}
		b=a;    //用b存储上一个字符 

	}
	fclose(fp);
}
int countLine(char *file) {	  //统计行数 
	FILE *fp = fopen(file,"r");
	char a;
	while (!feof(fp))     //每遇到一个'\n'，行数就+1 
	{
		a = fgetc(fp);
		if(a=='\n')
			lineNum++;
	}
	fclose(fp);  
}
int writeOutput(char *filename)  //输出信息到指定文档 
{
    FILE *fpWrite = fopen(filename,"w");
    if (fpWrite == NULL)    //打开文件失败，返回-1 
    {		  
		return -1;
	}
	if (l)     //根据l、w、c的值来输出指定文件的行、单词、字符数目 
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
    char inFile[20];   //输入的文件 
    char outFile[20];   //输出的文件 

	//printf("%d\n",argc);
	while((opt=getopt(argc,argv,"l:w:c:o:")) != -1)  //获取控制台命令 
    {
        switch(opt)
        {

            case 'l':    //获取命令为l，l=1，且输出行数 
            	l=1;
				strcpy(inFile,optarg); 
           		countLine(inFile);
				printf("Lines: %d\n", lineNum);  
           		break;  
    		case 'w':   //获取命令为w，w=1，且输出单词数 
        		w=1;
           	 	strcpy(inFile,optarg);
				countWord(inFile);
				printf("Words: %d\n", wordNum); 
     		    break;  
           	case 'c':   //获取命令为c，c=1，且输出字符数 
            	c=1;
				strcpy(inFile,optarg);
				countChar(inFile);
             	printf("Chars: %d\n", charNum-1);
            	break;
            case 'o':  //获取命令为o，o为1，输出文档 
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
