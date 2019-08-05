int quit = 0;
show_window();


while(quit != 1)
{
	/* events */
	begin_event();
	while(has_events() > 0)
	{
		int type = get_event_type();
		
		if(type == 1)
		{
			int message_quit[] = "exiting program\n";
			print(message_quit, 1);

			quit = 1;
		}
		if(type == 2) /* keydown */
		{

		}
		if(type == 3) /* keyup */
		{

		}

		pop_event();
	}
	/* ====== */
	/* logic */



	/* ====== */
	delay(14);
}