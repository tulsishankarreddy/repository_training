#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#if 0
//22
void *squezz(char *);
int main()
{
char s[30];
printf("enter the string\n");
scanf("%[^\n]",s);
squezz(s);
printf("%s\n",s);
}
void *squezz(char *p)
{
int i,j;
for(i=0;p[i];i++)
{
if(p[i]==' ')
for(j=i;p[j];j++)
p[j]=p[j+1];
}
}
#endif
#if 0 
//26(i)
void *mymemcpy(void *,void *,int);
int main()
{
int i,m=0,num;
printf("enter the number and no.of bytes to copy\n");
scanf("%d%d",&i,&num);
mymemcpy(&m,&i,num);
printf("%d\n",m);
}
void *mymemcpy(void *p,void *q,int n)
{
int i;
char *w=p;
char *x=q;
for(i=0;i<n;i++)
w[i]=x[i];
return w;
}
#endif
#if 0
//26(ii)
int mymemcmp(void *,void *,int);
int main()
{
int n,m,num;
printf("enter two numbers\n");
scanf("%d%d",&m,&n);
printf("enter no.of bytes campare\n");
scanf("%d",&num);
int r = mymemcmp(&m,&n,num);
printf("%d\n",r);
}
int mymemcmp(void *p,void *q,int n)
{
char *w=p;
char *x=q;
int i,j;
for(i=0;i<n;i++)
{
if(w[i]!=x[i])
return (w[i]-x[i])<<8*i;
}
return 0;
}
#endif
#if 1
//26(iii)
void *mymemset(void *,int,int);
int main()
{
int s,c,num;
printf("enter the number and set number\n");
scanf("%d%d",&s,&c);
printf("enter the no.of bytes\n");
scanf("%d",&num);
mymemset(&s,c,num);
printf("s-%d\n",s);
}
void *mymemset(void *p,int c,int n)
{
char *x=p;
int i;
for(i=0;i<n;i++)
x[i]=c;
}
#endif 
#if 0
//26(iv)
void *mymemmove(void *,void *,int);
int main()
{
int s,d=0,num;
printf("enter the src value\n");
scanf("%d",&s);
printf("enter the number of bytes moved\n");
scanf("%d",&num);
mymemmove(&d,&s,num);
printf("d-%d\n",d);
}
void *mymemmove(void *p,void *q,int n)
{
char *w=p;
char *x=q;
char *t=malloc(n);
int i;
for(i=0;i<n;i++)
t[i]=x[i];
for(i=0;i<n;i++)
w[i]=t[i];
}
#endif
#if 0
//28
int replcwrd(char *,char *,char *);
int main()
{
char s[60],w1[20],w2[20];
printf("enter the string\n");
scanf("%[^\n]",s);
printf("enter the word and replacement word\n");
scanf( "%s%s",w1,w2);
int m=replcwrd(s,w1,w2);
if(m==0)
{
printf("word is not found\n");
}
else printf("modified string %s\n",s);
}
int replcwrd(char *p,char *q,char *r)
{
int z,i,j=0,k,l=strlen(q),m=0;
char w[80];
for(z=0;p[z];z++)
{
char *a=strstr(p,q);
if(a)
{
for(i=0,k=0;a!=k+p;k++,i++)
w[i]=p[k];
for(j=0;r[j];j++,i++)
w[i]=r[j];
for(k=k+l;p[k];k++,i++)
w[i]=p[k];
w[i]='\0';
strcpy(p,w);
m++;
}
}
return m;
}
#endif
#if 0
//29
int myatoi(char *);
int main()
{
char s[30];
printf("enter the string\n");
scanf("%s",s);
int n = myatoi(s);
printf("the equelent integer n- %d\n",n);
}
int myatoi(char *p)
{
int sum=0,j,i;
for(i=0;p[i]!='\0';i++)
{
j = p[i]-48;
sum = sum*10+j;
}
return sum;
}
#endif
#if 0
//30
void lwrtoupr_uprtolwr(char *);
int main()
{
char s[30];
printf("enter the word\n");
scanf("%s",s);
lwrtoupr_uprtolwr(s);
printf("%s\n",s);
}
void lwrtoupr_uprtolwr(char *p)
{
int i;
for(i=0;p[i];i++)
{
if((97<=p[i])&&(p[i]<=122))
p[i]=p[i]-32;
else if((65<=p[i])&&(p[i]<=90))
p[i]=p[i]+32;
}
}
#endif
#if 0
//31
int wrdoccrans(char *,char *);
int main()
{
char s[50],w[20];
printf("enter the string\n");
scanf("%[^\n]",s);
printf("enter the word\n");
scanf( "%s",w);
int n = wrdoccrans(s,w);
if(n!=0)
printf("word occured %d times in string\n",n);
else
printf("word is not found\n");
}
int wrdoccrans(char *p,char *q)
{
int i,j,c=0;
for(i=0;p[i];i++)
{
if(p[i]==q[0])
for(j=1;q[j];j++)
{
if(p[i+j]!=q[j])
break;
else if(j==strlen(q)-1)
c++;
}
}
return c;
}
#endif
#if 0
//32
void insertstr(char *,char *,int);
int main()
{
char s[60],w[20];
int pos;
printf("enter the string\n");
scanf("%[^\n]",s);
printf("enter the word to insert\n");
scanf( "%s",w);
printf("enter the pos to insert\n");
scanf("%d",&pos);
insertstr(s,w,pos);
if(pos>strlen(s))
printf("give the pos less than the string length\n");
else
printf("the new string is s-%s\n",s);
}
void insertstr(char *p,char *q,int n)
{
int i,j,k;
char *t = malloc(strlen(p)+strlen(q)+1);
strncpy(t,p,n+1);
//for(i=0;i<n&&p[i];i++)
//t[i]=p[i];
for(j=0;q[j];j++)
t[n+j]=q[j];
for(k=0;p[k];k++)
t[n+j+k]=p[n+k];
t[n+j+k]='\0';
strcpy(p,t);
}
#endif
#if 0
//33
int removestr(char *,char *);
int main()
{
char s[60],w[20];
printf("enter the string\n");
scanf("%[^\n]",s);
printf("enter the word to remove\n");
scanf(" %s",w);
int r = removestr(s,w);
if(r!=0)
printf("string is s-%s\n",s);
else
printf("word is not found\n");
}
int removestr(char *p,char *q)
{
int i,j,l;
char *w=strstr(p,q);
char *t=malloc(strlen(p));
if(w==0)
return 0;
else 
{
l=strlen(q);
for(i=0;i<w-p;i++)
t[i]=p[i];
for(j=0;p[j];j++)
t[i+j]=p[i+j+l];
strcpy(p,t);
}
return 1;
}
#endif


