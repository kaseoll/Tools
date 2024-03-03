#include <stdio.h>
// #include "../libs/stropt.c" //What needs to be repeated is for you

#define HELP "在所有文件换行后添加\"\\\"符号\n\n-h ,--help\t显示此帮助\n%s \t\t <file> [outfile] \n如果没有输出名称，则输出在屏幕上\n"
#define ADDC '\\'
#define DETE '\n' 
#define DETE2 '\r'
//determine 
char *msgs[] = {
	"文件不存在\n", // 0  
	"无法移动文件指针\n", //    1
	"无法写入\n", //2
};
// #define CBEF ''
int mallocstr(char* s1, char *s2);

void  addchar(char *s1, char *s2);

int main(int c, char *args[]){
	
	if(c == 1){
		printf(HELP, args[0]);
		return 0;
	}
	if(mallocstr(args[1],"-h")||mallocstr(args[1],"--help")){
		
		printf(HELP, args[0]);
		return 0;
	}
	if(*args[1] == '-'){
		printf(HELP, args[0]);
		return 0;
	}
	FILE *FP =fopen(args[1],"r+");
	
	if(FP==NULL){
		printf(msgs[1]);
		return -1;
	}
	char chs;
	long result =0;
	int fleng = 0; //文件长度
	
	result = fseek(FP, 0L, SEEK_END); //移动文件指针到文件尾部
	if(result != 0){
		printf(msgs[1]);
		return -2;
	}
	
	fleng = ftell(FP);
	// printf("%d leng\n",fleng);
	char strs[fleng+1];
	result = fseek(FP, 0L, SEEK_SET); //移动文件指针到文件头部
	
	if(result != 0){
		printf(msgs[1]);
		return -1;
	}
	
	char *cp = strs;
	
	while((chs=fgetc(FP))!=EOF){
		*cp++ = chs;
	}
	*cp = '\0';
	
	// printf("%s",strs);
	
	fclose(FP);
	char newstr[sizeof(strs)*2+1]; 
	
	/*
	例子 . ====>>.\
	*/
	addchar(strs,newstr);
	
	if(c <= 2){// 没有输出的选项
		printf("%s\n",newstr);
		return 0;
	}
	
	FILE *WRT = fopen(args[2], "w+");
	if(WRT == NULL){
		printf(msgs[2]);
		return -3;
	}
	cp = newstr;
	while(*cp!='\0'){
		fputc(*cp,WRT);
		cp++;
	}
	fclose(WRT);
	
	
	return 0;
	
}

void addchar(char *s1, char *s2){
	while(*s1!='\0'){
		if(*s1==DETE|| *s1==DETE2){
			*s2 = ADDC;
			s2++;
			
		}
		*s2=*s1;
		s2++;
		s1++;
	}
	*s2++=ADDC;
	
	*s2='\0';
}


int mallocstr(char *s1, char *s2){
	while(*s1!=0||*s2!=0){
		if(*s1++!=*s2++){
			return 0;
		}
	}
	return 1;
}
