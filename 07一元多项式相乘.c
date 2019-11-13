	/* PRESET CODE BEGIN - NEVER TOUCH CODE BELOW */  
     
    #include <stdio.h>  
    #include <stdlib.h>  
      
    typedef struct node  
    {   int    coef, exp;  
        struct node  *next;  
    } NODE;  
      
    void multiplication( NODE *, NODE * , NODE * );  
    void input( NODE * );  
    void output( NODE * );  
      
    void input( NODE * head )  
    {   int flag, sign, sum, x;  
        char c;  
      
        NODE * p = head;  
      
        while ( (c=getchar()) !='\n' )  
        {  
            if ( c == '<' )  
            {    sum = 0;  
                 sign = 1;  
                 flag = 1;  
            }  
            else if ( c =='-' )  
                 sign = -1;  
            else if( c >='0'&& c <='9' )  
            {    sum = sum*10 + c - '0';  
            }  
            else if ( c == ',' )  
            {    if ( flag == 1 )  
                 {    x = sign * sum;  
                      sum = 0;  
                      flag = 2;  
              sign = 1;  
                 }  
            }  
            else if ( c == '>' )  
            {    p->next = ( NODE * ) malloc( sizeof(NODE) );  
                 p->next->coef = x;  
                 p->next->exp  = sign * sum;  
                 p = p->next;  
                 p->next = NULL;  
                 flag = 0;  
            }  
        }  
    }  
      
    void output( NODE * head )  
    {  
        while ( head->next != NULL )  
        {   head = head->next;  
            printf("<%d,%d>,", head->coef, head->exp );  
        }  
        printf("\n");  
    }  
      
    int main()  
    {   NODE * head1, * head2, * head3;  
      
        head1 = ( NODE * ) malloc( sizeof(NODE) );  
        input( head1 );  
      
        head2 = ( NODE * ) malloc( sizeof(NODE) );  
        input( head2 );  
      
        head3 = ( NODE * ) malloc( sizeof(NODE) );  
        head3->next = NULL;  
        multiplication( head1, head2, head3 );  
      
        output( head3 );  
        return 0;  
    }  
      
    /* PRESET CODE END - NEVER TOUCH CODE ABOVE */  
    
    void multiplication( NODE * head1, NODE * head2, NODE * head3)
    {
		NODE * x, *y, *z, *temp, *maxz;
		int a, b;
		z = head3;
		maxz = z;
		for(x = head1->next; x != NULL; x = x->next)
		{
			for(y = head2->next; y != NULL; y = y->next)
			{
				z = head3;
				int flag = 0;		//0:none till end	&&	none between two	1:exist
				a = x->coef * y->coef;
				b = x->exp + y->exp;
				if(b > maxz->exp) z = maxz;
				
				while(z->next != NULL)
				{
					z = z->next;
					if(z->exp == b)
					{
						flag = 1;
						break;
					}
					if(z->next != NULL &&(b > z->exp && b < z->next->exp))
					{
						flag = 0;
						break;
					}
				}
				
				if(flag == 0)
				{
					temp = (NODE *)malloc(sizeof(NODE));
					temp->coef = a;
					temp->exp = b;
					temp->next = z->next;
					z->next = temp;
					z = temp;
					if(b > maxz->exp)
						maxz = z;
				}
				else
				{
					z->coef += a;
				}
			}
		}
		
		z = head3;
		while(z->next != NULL)
		{
			temp = z->next;
			if(temp->coef == 0)	
			{
				z->next = temp->next;
				free(temp);
			}
			else
				z = z->next;
		}
		z = head3;
		if(z->next == NULL)
		{
			temp = (NODE *)malloc(sizeof(NODE));
			temp->coef = 0;
			temp->exp = 0;
			temp->next = NULL;
			z->next = temp;
		}
 	}
