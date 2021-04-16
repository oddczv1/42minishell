#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <termcap.h>

# define BACKSPACE 127
# define LEFT_ARROW 4479771
# define RIGHT_ARROW 4414235


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
/*
int main()
{
	struct termios ti;
	tcgetattr(0, &ti);
	ti.c_lflag &= ~ICANON;//캐노니컬 입력 모드를 사용
	ti.c_lflag &= ~ECHO;//입력을 다시 출력
	ti.c_cc[VMIN] = 1;
	ti.c_cc[VTIME] = 0;
}
*/
/*
#include <stdlib.h>
#include <stdio.h>

#include <termios.h>
#include <string.h>

static struct termios stored_settings;
void echo_off(void)
{
    struct termios new_settings;
    tcgetattr(0, &stored_settings);
    new_settings = stored_settings;
    new_settings.c_lflag &= (~ECHO);
    new_settings.c_lflag &= (~ICANON);
    tcsetattr(0,TCSANOW, &new_settings);

    return ;
}

void echo_on(void)
{
    tcsetattr(0, TCSANOW, &stored_settings);
    return ;
}

void get_pass(char *pass)
{
    char buf;
    int i=0;

    printf("Passwd : ");
    echo_off();
    while ((buf=getc(stdin)) != '\n')
    {
        pass[i] = buf;
        printf("%s", "*");
        i ++;
    }
    echo_on();
}

int main()
{
    char pass[16];
    memset(pass, 0x00, 16);
    get_pass(pass);
    printf("\nYour input : %s\n", pass);
    return 1;
}
*/
/*
#include <stdio.h>
#include <termios.h>

struct termios old_settings;
int main()
{
    struct termios new_settings;
    char buf[80];
    tcgetattr(0, &old_settings);
    new_settings = old_settings;
    new_settings.c_lflag &= (~ISIG); // 특수문자 무시
    tcsetattr(0, TCSANOW, &new_settings);

    fgets(buf, 80, stdin);
    fputs(buf, stdout);
    tcsetattr(0, TCSANOW, &old_settings);
}
*/
#include <stdio.h>
#include <termios.h>

struct termios old_settings;
int main()
{
    struct termios new_settings;
    char buf;

    tcgetattr(0, &old_settings);
    new_settings = old_settings;
	new_settings.c_lflag &= (~ICANON);
    tcsetattr(0, TCSANOW, &new_settings);

    printf("youre OK (Y/N)? ");
    buf=getc(stdin);
	printf("\nyour input is %c\n", buf);
    tcsetattr(0, TCSANOW, &old_settings);
}



