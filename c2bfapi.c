/*
OPERATION_NULL, 0
OPERATION_PRINT, 1
OPERATION_INPUT, 2
OPERATION_PIXEL, 3
OPERATION_PRESENT, 4
OPERATION_WINDOW_OPEN, 5
OPERATION_WINDOW_RESOLUTIN_FACTOR, 6
OPERATION_DELAY, 7
OPERATION_EXIT 8,
OPERATION_PRINT_NUMBER 9
*/

void print(int []string, int extended)
{
	int i = 0;

	while(string[i] != 0)
	{
		if(extended == 1)
		{
			write_char(1);
		}
		write_char(string[i]);
		i = i + 1;
	}
}

int read_input_raw(int extended)
{
	int ret = 0;

	if(extended == 1)
	{
		write_char(2);
		ret = read_char();
	}
	else
	{
		ret = read_char();
	}

	return ret;
}

int read_input_single(int extended)
{
	int ret = 0;
	int unused = 0;

	ret = read_input_raw(1);
	unused = read_input_raw(1);

	return ret;
}

/* the following have to be run in extended mode */

void begin_event()
{
	write_char(14);
	write_char(0);
}

int has_events()
{
	write_char(10);
	return read_char();
}

int get_event_value()
{
	write_char(11);
	return read_char();
}

int get_event_type()
{
	write_char(12);
	return read_char();
}

void pop_event()
{
	write_char(13);
	write_char(0);
}

void delay(int amount)
{
	write_char(7);
	write_char(amount);
}

void print_number(int number)
{
	write_char(9);
	write_char(number);
}

void draw_pixel(int x, int y, int r, int g, int b)
{
	write_char(3);
	write_char(x);
	write_char(y);
	write_char(r);
	write_char(g);
	write_char(b);
}

void present_screen()
{
	write_char(4);
	write_char(0); /* every command with no arguments needs at least 1 null */
}

void show_window()
{
	write_char(5);
	write_char(1);
}

void hide_window()
{
	write_char(5);
	write_char(0);
}

void pause_key()
{
	int val = read_input_single(1);
}

/* =============== end of utils =============== */

/* NOTE; THE FOLLOWING WILL BE DELETED ONCE I VERIFY ALL OF THE COMMAND FUNCTIONS */


void draw_rect(int x, int y, int w, int d, int r, int g, int b)
{

	int i = x;
	int j = y;

	while(i < (y + d))
	{
		j = x;
		while(j < (x + w))
		{
			draw_pixel(j,i,r,g,b);

			j = j + 1;
		}

		i = i + 1;
	}
}



int square_x = 0;
int square_y = 0;

int x_vel = 0;
int y_vel = 0;

int quit = 0;
show_window();


while(quit != 1)
{
	/* events */
	begin_event();
	while(has_events() > 0)
	{
		int type = get_event_type();
		int key = get_event_value();
		
		if(type == 1)
		{
			int message_quit[] = "exiting program\n";
			print(message_quit, 1);

			quit = 1;
		}
		if(type == 2) /* keydown */
		{
			
			/* 1 neg 2 pos 0 nothing */
			if(key == 41)
			{
				y_vel = 1;
			}
			if(key == 42)
			{
				y_vel = 2;
			}
			if(key == 43)
			{
				x_vel = 1;
			}
			if(key == 44)
			{
				x_vel = 2;
			}
		}
		if(type == 3) /* keyup */
		{
			if(key == 41)
			{
				y_vel = 0;
			}
			if(key == 42)
			{
				y_vel = 0;
			}
			if(key == 43)
			{
				x_vel = 0;
			}
			if(key == 44)
			{
				x_vel = 0;
			}
		}

		pop_event();
	}
	/* ====== */
	/* logic */


	if(x_vel == 1)
	{
		int mess[] = "left\n";
		print(mess, 1);
		square_x = square_x - 1;
	}
	if(x_vel == 2)
	{
		int mess[] = "right\n";
		print(mess, 1);
		square_x = square_x + 1;
	}
	if(y_vel == 1)
	{
		int mess[] = "up\n";
		print(mess, 1);
		square_y = square_y - 1;
	}
	if(y_vel == 2)
	{
		int mess[] = "down\n";
		print(mess, 1);
		square_y = square_y + 1;
	}

	draw_pixel(square_x, square_y, 255, square_x, square_y);
	//draw_rect(square_x, square_y, 20, 20, 255, 12 * square_x, 34 * square_y);

	/* ====== */
	present_screen();
	delay(14);
}

/* start of test program */

/*
show_window();

int mess01[] = "drawing things\n";
print(mess01, 1);

int i = 0;
int j = 0;
while(i < 250)
{
	j = 0;
	while(j < 250)
	{
		draw_pixel(j,i,255,0,0);
		j = j + 1;
	}
	draw_pixel(j,i,0,255,0);

	i = i + 1;
}

present_screen();
pause_key();

print_number(42);

int mess02[] = "other things\n";
print(mess02, 1);

int selection = read_input_single(1);

if(selection == 63)
{
	int message[] = "hey\n";
	print(message, 1);
}
else
{
	int message[] = "heynt\n";
	print(message, 1);
}

selection = read_input_single(1);

if(selection == 63)
{
	int message[] = "hey2\n";
	print(message, 1);
}
else
{
	int message[] = "heynt2\n";
	print(message, 1);
}
*/