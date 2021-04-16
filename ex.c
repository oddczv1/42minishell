#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <termcap.h>

#include <string.h>
#include "./libft/libft.h"

//struct termios
//{
//    tcflag_t c_iflag;    /* input flags */
//    tcflag_t c_oflag;    /* output flags */
//    tcflag_t c_cflag;    /* control flags */
//    tcflag_t c_lflag;    /* local flags */
//    cc_t     c_cc[NCCS]; /* control chars */
//    speed_t  c_ispeed;   /* input speed */
//    speed_t  c_ospeed;   /* output speed */
//};

int	nbr_length(int n)
{
	int	i = 0;

	if (n <= 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

int		putchar_tc(int tc)
{
	write(1, &tc, 1);
	return (0);
}

int main()
{
	int c;
	struct termios ti;
	int col;
	int max;
	char *old_cmd;
	
	tcgetattr(0, &ti);
	ti.c_lflag &= (~ECHO);//입력을 다시 출력
	ti.c_lflag &= (~ICANON);//캐노니컬 입력 모드를 사용
	//ti.c_lflag &= (~ISIG); // 특수문자 무시
	ti.c_cc[VMIN] = 1;
	ti.c_cc[VTIME] = 0;
	old_cmd = 0;
	tcsetattr(0, TCSANOW, &ti);
	tgetent(NULL, "xterm");
	char *buffer = (char *)malloc(1024);
	while (1)
	{
  	  	write(1, ">>> ~% ", 7);
		c = 0;
		col = 0;
		max = 0;
    	while (read(0, &c, sizeof(c)) > 0)
    	{
			if (c ==  4479771) //left
			{		
				if (col > 0)
				{
					--col;
					//tputs(tgoto(cm, col, row), 1, putchar_tc);
					tputs(tgetstr("le", &buffer), 1, putchar_tc);				
				}
			}
			else if(c ==  4414235)//right
			{
				if (col < max)
				{
					++col;
					tputs(tgetstr("nd", &buffer), 1, putchar_tc);
				}
			}
			else if (c == 127) //backspace
			{	
				if (col > 0)
				{
					--col;
					--max;
					tputs(tgetstr("le", &buffer), 1, putchar_tc);
					tputs(tgetstr("dc", &buffer), 1, putchar_tc);
				}
			}
			else if (c == 2117294875)
			{
				if (max > col && col >= 0)
				{
					--max;
					tputs(tgetstr("dc", &buffer), 1, putchar_tc);
				}
			}
			else if (c == 4348699 || c == 4283163)
			{
			}
			else if (c == 9)
			{
			}
			else if (c == 10)
			{
			//	tputs(tgoto(tgetstr("nd", &old_cmd), 7 + max, 0), 1, putchar_tc);			
				break;
			//	ft_putstr_fd(old_cmd[0],2);
			}
			else
			{ 
				//ft_putstr_fd(ft_itoa(c),2);
				++col;
				++max;
				tputs(tgetstr("im", &buffer), 1, putchar_tc);
				write(0, &c, 1);				
			}
			tputs(tgetstr("ei", &buffer), 1, putchar_tc);
			c = 0;
  		}
		tputs(buffer, 1, putchar_tc);
		write(1, "\n", 1);
	}
    return 1;
}
