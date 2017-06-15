#include <stdio.h>
unsigned int row=0;
/*Check if any move is possible*/
void print_field(char field[][row])
{
    unsigned int i,j;
    for (i=0; i<row; ++i)
    {
        for (j=0; j<i; ++j)
        {
            printf(" ");
        }
        for (j=0; j<(row-i); ++j)
        {
            printf("%c ", field[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
void copy(char c[][row],char f[][row],int row)
{
    unsigned int i,j;
    for(i=0; i<row; i++)
    {
        for(j=0; j<(row-i); j++)
        {
            c[i][j]=f[i][j];
        }
    }

}
int ul_diag(char f[][row],int i, int j, int row)/*Up-Left Diagonal*/
{
    if(i>=2 && f[i-1][j]=='s'&& f[i-2][j]=='e')
        return 1;
    else
        return 0;
}
int ur_diag(char f[][row],int i, int j, int row)/*Up-Right Diagonal*/
{
    if(i>=2 && f[i-1][j+1]=='s' && f[i-2][j+2]=='e')
        return 1;
    else
        return 0;
}
int left(char f[][row],int i, int j, int row)/*Left*/
{
    if(j>=2 && f[i][j-1]=='s' && f[i][j-2]=='e')
        return 1;
    else
        return 0;
}
int right(char f[][row],int i, int j, int row)/*Right*/
{
    if((j+2)<(row-i) && f[i][j+1]=='s' && f[i][j+2]=='e' )
        return 1;
    else
        return 0;
}
int dl_diag(char f[][row],int i, int j, int row)/*Down-Left Diagonal*/
{
    if((i+2)<row && j>=2 && f[i+1][j-1]=='s' && f[i+2][j-2]=='e')
        return 1;
    else
        return 0;
}
int dr_diag(char f[][row],int i, int j, int row)/*Down-Right Diagonal*/
{
    if((i+2)<row && f[i+1][j]=='s' && f[i+2][j]=='e')
        return 1;
    else
        return 0;
}
/*Make a move*/
void apply_uld(char f[][row],int i, int j)/*Up-Left Diagonal*/
{
    f[i-2][j]='s';
    f[i-1][j]='e';
    f[i][j]='e';
}
void apply_urd(char f[][row],int i, int j)/*Up-Right Diagonal*/
{
    f[i-2][j+2]='s';
    f[i-1][j+1]='e';
    f[i][j]='e';
}
void apply_l(char f[][row],int i, int j)/*Left*/
{
    f[i][j-2]='s';
    f[i][j-1]='e';
    f[i][j]='e';
}
void apply_r(char f[][row],int i, int j)/*Right*/
{
    f[i][j+2]='s';
    f[i][j+1]='e';
    f[i][j]='e';
}
void apply_dld(char f[][row],int i, int j)/*Down-Left Diagonal*/
{
    f[i+2][j-2]='s';
    f[i+1][j-1]='e';
    f[i][j]='e';
}
void apply_drd(char f[][row],int i, int j)/*Down-Right Diagonal*/
{
    f[i+2][j]='s';
    f[i+1][j]='e';
    f[i][j]='e';
}

/*Count no of "s" in field, Analyse locations and Determine whether ideal or not*/
int is_ideal(char f[][row], int row)
{
    int i,j,check=0,s_count=0;
    for(i=0; i<row; i++)
    {
        for(j=0; j<(row-i); j++)
        {
            if(f[i][j]=='s')
            {
                s_count++;
                check=check||ul_diag(f,i,j,row)||ur_diag(f,i,j,row)||left(f,i,j,row)||right(f,i,j,row)||dl_diag(f,i,j,row)||dr_diag(f,i,j,row);
                /*Check whether any move is possible*/
            }
        }
    }
    if (check==0 && s_count!=1)/*leaf case*/
    {
        return 2;/*True, no solution.*/
    }
    else if(s_count==1)/*leaf case-goal node*/
    {
        return 1;/*True, it is already solved*/
    }
    else
    {
        return 0;/*False, possible solution*/
    }
}
/*Main code*/
int solve(char f[][row], int row)
{
    unsigned int i,j,boolean;
    boolean=is_ideal(f,row);
    if(boolean)
    {
		if(boolean==1)/*Solved*/
		{
		        return 1;
		}
    }
    for(i=0; i<row; i++)
    {
		for(j=0; j<(row-i); j++)
		{
		    int uld=ul_diag(f,i,j,row), urd=ur_diag(f,i,j,row), l=left(f,i,j,row), r=right(f,i,j,row), dld=dl_diag(f,i,j,row), drd=dr_diag(f,i,j,row);
		    if(f[i][j]=='s' && (uld||urd||l||r||dld||drd))/*Can move*/
		    {
			/*Check directions*/
		        if(uld)
		        {
		            char copy1[row][row];
			    copy(copy1,f,row);
		            apply_uld(copy1,i,j);
				
		            if (solve(copy1,row))
		            {
		                print_field(copy1);
		                return 1;
		            }
		        }
		        if(urd)
		        {
		            char copy2[row][row];
		            copy(copy2,f,row);
		            apply_urd(copy2,i,j);

		            if (solve(copy2,row))
		            {
		                print_field(copy2);
		                return 1;
		            }
		        }
		        if(l)
		        {
		            char copy3[row][row];
		            copy(copy3,f,row);				
		            apply_l(copy3,i,j);

		            if(solve(copy3,row))
		            {
		                print_field(copy3);
		                return 1;
		            }
		        }
		        if(r)
		        {
		            char copy4[row][row];
		            copy(copy4,f,row);
		            apply_r(copy4,i,j);

		            if(solve(copy4,row))
		            {
		                print_field(copy4);
		                return 1;
		            }
		        }
		        if(dld)
		        {
		            char copy5[row][row];
		            copy(copy5,f,row);
		            apply_dld(copy5,i,j);
				
		            if(solve(copy5,row))
		            {
		                print_field(copy5);
		                return 1;
		            }
		        }
		        if(drd)
		        {
		            char copy6[row][row];
		            copy(copy6,f,row);
		            apply_drd(copy6,i,j);

		            if(solve(copy6,row))
		            {
		                print_field(copy6);
		                return 1;
		            }
		        }
		    }
		}
    }
    return 0;
}
int main(void)
{
    unsigned int i,j,value;
    scanf("%d",&row);/*Row number*/
    char field[row][row];

    for(i=0; i<row; i++) /*Get pattern*/
    {
        for(j=0; j<(row-i); j++)
        {
            scanf(" %c", &field[i][j]);
        }
    }
    value=solve(field,row);
   
    if(value==0)
		printf("No ideal field!\n");
   
    else
		print_field(field);

    return 0;
}

