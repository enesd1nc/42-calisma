#include <stdio.h>
#include <stddef.h>

int main()
{
	char	*p = NULL;
	void	*s = NULL;
	//printf("%s\n",p);
	//printf("%x\n",16);
	printf("%p\n",s);

}
/* printf("%s", NULL) neden çalışmaz?
%s, bellekte geçerli bir karakter dizisi adresine gitmeye çalışır ve bu adresi okumaya başlar.
 Ancak, NULL geçerli bir bellek adresi olmadığı için: çalışmaz. */ 