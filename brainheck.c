/*
brainheck by 0x3F

-------------------------- License --------------------------
	
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org/>

-------------------------- License --------------------------

TL;DR pretty much public domain
 */
#ifdef _WIN32
#define SDL_MAIN_HANDLED
#include <windows.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL2/SDL.h>

#define color2pix(a,r,g,b) ( (((unsigned char)a) << 8 * 3) | (((unsigned char)r) << 8 * 2) | (((unsigned char)g) << 8 * 1) | ((unsigned char)b) )

enum operations
{
	OPERATION_NULL,
	OPERATION_PRINT,
	OPERATION_INPUT,
	OPERATION_PIXEL,
	OPERATION_PRESENT,
	OPERATION_WINDOW_OPEN,
	OPERATION_WINDOW_RESOLUTION_FACTOR,
	OPERATION_DELAY,
	OPERATION_EXIT,
	OPERATION_PRINT_NUMBER,
	OPERATION_HAS_EVENTS,
	OPERATION_GET_EVENT_VALUE,
	OPERATION_GET_EVENT_TYPE,
	OPERATION_POP_EVENT,
	OPERATION_BEGIN_EVENT
};

typedef struct
{
	unsigned char op;
	union
	{
		unsigned long long matched_bracket_pos;
		unsigned long long amount;
	};
	
} bf_op_t;

typedef struct
{
	SDL_Renderer *renderer;
	SDL_Window *window;
	SDL_Texture *target;
	unsigned char *frame;
	int scale;
	SDL_Event event;
} bf_extended_t;

unsigned char command_parse(bf_extended_t *ctx, int operation)
{
	static unsigned char progress = 0, current_operation = OPERATION_NULL;
	unsigned char ret = 0;
	static unsigned char data[64]; /* workspace for commands */
	int temp = 0;

	/*
	if(!current_operation)
		printf("running command %u\n", operation);
	else
		printf("operation currently %d and progress %d\n", operation, progress);
	//*/

	if(!current_operation)
		current_operation = operation;
	else
	{
		switch(current_operation)
		{
			case OPERATION_PRINT:
				fprintf(stdout, "%c", operation);
				progress = 0;
				current_operation = OPERATION_NULL;
			break;
			case OPERATION_INPUT:
				/* just return the typed character */
				fscanf(stdin, "%c", &ret);
				current_operation = OPERATION_NULL;
				progress = 0;


			break;
			case OPERATION_PIXEL:
				switch(progress)
				{
					case 1: /* x coord */
						data[0] = operation;
					break;
					case 2: /* y coord */
						data[1] = operation;
					break;
					case 3: /* color r */
						data[2] = operation;
					break;
					case 4: /* color g */
						data[3] = operation;
					break;
					case 5: /* color b */
						data[4] = operation;
						//for(int i = 0; i < 256 * 256; i++)
						//{
							//ctx->frame[i] = rand();
						//}
						/* and finally write */
						ctx->frame[(data[1] * 255) + data[0]] = rand();//color2pix(255, data[2], data[3], data[4]);
						//SDL_SetRenderDrawColor(ctx->renderer, data[2], data[3], data[4], 255);
						//SDL_RenderDrawPoint(ctx->renderer, data[0], data[1]);
						current_operation = OPERATION_NULL;
						progress = 0;
					break;
				}
			break;
			case OPERATION_PRESENT:
				SDL_UpdateTexture(ctx->target, NULL, ctx->frame, 256);
				SDL_RenderCopy(ctx->renderer, ctx->target, NULL, NULL);
				SDL_RenderPresent(ctx->renderer);
				current_operation = OPERATION_NULL;
				progress = 0;
			break;
			case OPERATION_WINDOW_OPEN:
				if(operation)
					SDL_ShowWindow(ctx->window);
				else
					SDL_HideWindow(ctx->window);
				
				current_operation = OPERATION_NULL;
				progress = 0;
			break;

			case OPERATION_DELAY:
				SDL_Delay(operation);
				current_operation = OPERATION_NULL;
				progress = 0;
			break;

			case OPERATION_PRINT_NUMBER:
				fprintf(stdout, "%u", operation);
				current_operation = OPERATION_NULL;
				progress = 0;
			break;
			case OPERATION_HAS_EVENTS:
				if((temp = SDL_PeepEvents(&ctx->event, 255, SDL_PEEKEVENT, SDL_FIRSTEVENT, SDL_LASTEVENT)) != -1)
					ret = (unsigned char)temp;
				else
					ret = 0;
				current_operation = OPERATION_NULL;
				progress = 0;
			break;
			case OPERATION_GET_EVENT_VALUE:
				if(SDL_PeepEvents(&ctx->event, 255, SDL_PEEKEVENT, SDL_FIRSTEVENT, SDL_LASTEVENT))
				{
					switch(ctx->event.type)
					{
						case SDL_KEYDOWN:
						case SDL_KEYUP:
							switch(ctx->event.key.keysym.scancode)
							{
								case SDL_SCANCODE_UNKNOWN:
									ret = 0;
								break;
								case SDL_SCANCODE_0:
									ret = 1;
								break;
								case SDL_SCANCODE_1:
									ret = 2;
								break;
								case SDL_SCANCODE_2:
									ret = 3;
								break;
								case SDL_SCANCODE_3:
									ret = 4;
								break;
								case SDL_SCANCODE_4:
									ret = 5;
								break;
								case SDL_SCANCODE_5:
									ret = 6;
								break;
								case SDL_SCANCODE_6:
									ret = 7;
								break;
								case SDL_SCANCODE_7:
									ret = 8;
								break;
								case SDL_SCANCODE_8:
									ret = 9;
								break;
								case SDL_SCANCODE_9:
									ret = 10;
								break;
								case SDL_SCANCODE_A:
									ret = 11;
								break;
								case SDL_SCANCODE_B:
									ret = 12;
								break;
								case SDL_SCANCODE_C:
									ret = 13;
								break;
								case SDL_SCANCODE_D:
									ret = 14;
								break;
								case SDL_SCANCODE_E:
									ret = 15;
								break;
								case SDL_SCANCODE_F:
									ret = 16;
								break;
								case SDL_SCANCODE_G:
									ret = 17;
								break;
								case SDL_SCANCODE_H:
									ret = 18;
								break;
								case SDL_SCANCODE_I:
									ret = 19;
								break;
								case SDL_SCANCODE_J:
									ret = 20;
								break;
								case SDL_SCANCODE_K:
									ret = 21;
								break;
								case SDL_SCANCODE_L:
									ret = 22;
								break;
								case SDL_SCANCODE_M:
									ret = 23;
								break;
								case SDL_SCANCODE_N:
									ret = 24;
								break;
								case SDL_SCANCODE_O:
									ret = 25;
								break;
								case SDL_SCANCODE_P:
									ret = 26;
								break;
								case SDL_SCANCODE_Q:
									ret = 27;
								break;
								case SDL_SCANCODE_R:
									ret = 28;
								break;
								case SDL_SCANCODE_S:
									ret = 29;
								break;
								case SDL_SCANCODE_T:
									ret = 30;
								break;
								case SDL_SCANCODE_U:
									ret = 31;
								break;
								case SDL_SCANCODE_V:
									ret = 32;
								break;
								case SDL_SCANCODE_W:
									ret = 33;
								break;
								case SDL_SCANCODE_X:
									ret = 34;
								break;
								case SDL_SCANCODE_Y:
									ret = 35;
								break;
								case SDL_SCANCODE_Z:
									ret = 36;
								break;
								case SDL_SCANCODE_SPACE:
									ret = 37;
								break;
								case SDL_SCANCODE_BACKSPACE:
									ret = 38;
								break;
								case SDL_SCANCODE_LSHIFT:
									ret = 39;
								break;
								case SDL_SCANCODE_RSHIFT:
									ret = 40;
								break;
								case SDL_SCANCODE_UP:
									ret = 41;
								break;
								case SDL_SCANCODE_DOWN:
									ret = 42;
								break;
								case SDL_SCANCODE_LEFT:
									ret = 43;
								break;
								case SDL_SCANCODE_RIGHT:
									ret = 44;
								break;
								case SDL_SCANCODE_LCTRL:
									ret = 45;
								break;
								case SDL_SCANCODE_RCTRL:
									ret = 46;
								break;
								case SDL_SCANCODE_TAB:
									ret = 47;
								break;
							}
						break;
						case SDL_MOUSEBUTTONDOWN:
						case SDL_MOUSEBUTTONUP:
							switch(ctx->event.button.button)
							{
								case SDL_BUTTON_LEFT:
									ret = 1;
								break;
								case SDL_BUTTON_MIDDLE:
									ret = 2;
								break;
								case SDL_BUTTON_RIGHT:
									ret = 3;
								break;
							}
						break;
					}
				}
				else
					ret = 0;
				
				current_operation = OPERATION_NULL;
				progress = 0;
			break;
			case OPERATION_GET_EVENT_TYPE:
				if(SDL_PeepEvents(&ctx->event, 255, SDL_PEEKEVENT, SDL_FIRSTEVENT, SDL_LASTEVENT))
				{
					switch(ctx->event.type)
					{
						case SDL_QUIT:
							ret = 1;
						break;
						case SDL_KEYDOWN:
							ret = 2;
						break;
						case SDL_KEYUP:
							ret = 3;
						break;
						case SDL_MOUSEBUTTONDOWN:
							ret = 4;
						break;
						case SDL_MOUSEBUTTONUP:
							ret = 5;
						break;
						case SDL_MOUSEMOTION:
							ret = 6;
						break;
					}
				}
				else
					ret = 0;
				
				current_operation = OPERATION_NULL;
				progress = 0;
			break;
			case OPERATION_POP_EVENT:
				SDL_PeepEvents(&ctx->event, 255, SDL_GETEVENT, SDL_FIRSTEVENT, SDL_LASTEVENT);
				current_operation = OPERATION_NULL;
				progress = 0;
			break;
			case OPERATION_BEGIN_EVENT:
				SDL_PumpEvents();
				current_operation = OPERATION_NULL;
				progress = 0;
			break;
			default:
				fprintf(stderr, "uncaught command\n");
		}
	}

	if(current_operation)
		progress++;
	
	return ret;
}

/* useful for debugging */
void brainheck_decompile_print(bf_op_t *operations, unsigned long long op_amount)
{
	unsigned long long i, j;

	for(i = 0; i < op_amount; i++)
	{
		if(operations[i].op == '[' || operations[i].op == ']')
			printf("%c", operations[i].op);
		else
			for(j = 0; j < operations[i].amount; j++)
			{
				printf("%c", operations[i].op);
			}
	}

	printf("\n");
}

unsigned char *brainheck_compile(unsigned char *program, bf_op_t **operations, unsigned long long *op_amount)
{
	unsigned char last_op = 0, *pc = program, has_start_bracket = 0;
	unsigned long long start_bracket = 0;
	

	if(*op_amount > 0 && (*operations)[*op_amount - 1].op == '[')
	{
		start_bracket = *op_amount - 1;
		has_start_bracket = 1;

		pc++;
	}

	for(; *pc; pc++)
	{
		switch(*pc)
		{
			case '>':
			case '<':
			case '+':
			case '-':
			case '.':
			case ',':
			case '@':
			case '[':
			case ']':
				if(last_op == *pc && last_op != '[' && last_op != ']' && last_op != '.' && last_op != ',')
					(*operations)[*op_amount - 1].amount++;
				else
				{
					if(!(*operations = realloc(*operations, (*op_amount + 1) * sizeof(bf_op_t))))
					{
						fprintf(stderr, "error reallocating\n");
						return NULL;
					}
					memset(&(*operations)[*op_amount], 0, sizeof(bf_op_t));

					(*operations)[*op_amount].op = *pc;
					(*operations)[*op_amount].amount++;

					(*op_amount)++;
				}
			break;
		}

		if(*pc == '[')
		{
			if(!(pc = brainheck_compile(pc, operations, op_amount)))
				return NULL;
		}
		else if(*pc == ']')
		{
			if(has_start_bracket)
			{
				(*operations)[start_bracket].matched_bracket_pos = *op_amount - 1;
				(*operations)[*op_amount - 1].matched_bracket_pos = start_bracket;

				return pc;
			}
			else
			{
				fprintf(stderr, "unmatched bracket\n");
				return 0;
			}
		}

		last_op = *pc;
	}

	return pc;
}

int init_extensions(bf_extended_t *ctx)
{
	ctx->window = SDL_CreateWindow("brainheck", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 256, 256, SDL_WINDOW_HIDDEN);
	ctx->renderer = SDL_CreateRenderer(ctx->window, -1, SDL_RENDERER_ACCELERATED);
	ctx->target = SDL_CreateTexture(ctx->renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, 256, 256);
	ctx->scale = 1;
	ctx->frame = calloc(1, 256 * 256 * (8 * 4));
	return 0;
}

int brainheck(unsigned char *program, unsigned char *cells, unsigned long long cell_max)
{
	unsigned char is_extended = 0, *cell_ptr = cells;
	bf_op_t *operations = NULL;
	unsigned long long op_amount = 0, i;
	bf_extended_t extension_ctx;


	if(!brainheck_compile(program, &operations, &op_amount))
	{
		fprintf(stderr, "problem optimizing input\n");
		return 1;
	}

	free(program);

	if(init_extensions(&extension_ctx))
	{
		fprintf(stderr, "problem initializing extensions\n");
		return 1;
	}

	for(i = 0; i < op_amount; i++)
	{

		switch(operations[i].op)
		{
			case '>':
				cell_ptr += operations[i].amount;

				if((cell_ptr - cells) > cell_max)
				{
					fprintf(stderr, "ran out of space\n");
					return 1;
				}
				
			break;
			case '<':
				cell_ptr -= operations[i].amount;

				if((cell_ptr - cells) < 0)
				{
					fprintf(stderr, "went out of bounds\n");
					return 1;
				}
			break;
			case '+': (*cell_ptr) += operations[i].amount; break;
			case '-': (*cell_ptr) -= operations[i].amount; break;
			case '.': is_extended ? command_parse(&extension_ctx, *cell_ptr) : fprintf(stdout, "%c", *cell_ptr); break;
			case ',': is_extended ? *cell_ptr = command_parse(&extension_ctx, *cell_ptr) : fscanf(stdin, "%c", cell_ptr); break;
			case '@': is_extended = 1; break;
			case '[':
				if(!*cell_ptr)
					i = operations[i].matched_bracket_pos;
			break;
			case ']':
				if(*cell_ptr)
					i = operations[i].matched_bracket_pos;
			break;
		}
	}



	return 0;
}

int brainheck_compatability(unsigned char *program, unsigned char *cells, unsigned long long cell_max)
{
	unsigned long long loop_depth = 0;
	unsigned char *cell_ptr = cells, *pc = program;

	for(; *pc; pc++)
	{
		switch(*pc)
		{
			case '>':
				if((++cell_ptr - cells) > cell_max)
				{
					fprintf(stderr, "ran out of space\n");
					return 1;
				}
			break;
			case '<':
				if((--cell_ptr - cells) < 0)
				{
					fprintf(stderr, "went out of bounds\n");
					return 1;
				}
			break;
			case '+': (*cell_ptr)++; break;
			case '-': (*cell_ptr)--; break;
			case '.': fprintf(stdout, "%c", *cell_ptr); break;
			case ',': fscanf(stdin, "%c", cell_ptr); break;
			case '[':
				if(!*cell_ptr)
				{
					for(; *pc; pc++)
					{
						switch(*pc)
						{
							case '[': loop_depth++; break;
							case ']': loop_depth--; break;
						}

						if(!loop_depth)
							break;
					}
				}
			break;
			case ']':
				if(*cell_ptr)
				{
					for(; pc >= program; pc--)
					{
						switch(*pc)
						{
							case '[': loop_depth--; break;
							case ']': loop_depth++; break;
						}

						if(!loop_depth)
							break;
					}
				}
			break;
		}
	}

	return 0;
}

int main(int argc, char **argv)
{
	FILE *file = NULL;
	unsigned long size = 0, i, begin;
	char is_benchmark = 0, is_compatability = 0, is_argument = 0, *file_program = NULL, *program = NULL, *default_program = "--[----->+<]>----.[--->+<]>----.+++[->+++<]>++.++++++++.+++++.------.---.--.++++++++.-[++>---<]>+.-[--->++<]>--.---.+++++++.++++.>++++++++++..[------->+++<]>.+++.-------.-[->+++++<]>-.++[->+++<]>.++++++++++++.---.--.[->+++++<]>-.++[->+++<]>.+++.+++.-------.+++[->+++<]>++.>++++++++++.-[->+++++<]>+.+.++[->++<]>.[--->+<]>----.+++[->+++<]>++.++++++++.+++++.------.---.--.++++++++.-[++>---<]>+.[-->+++++++<]>.[----->++<]>+.--[--->+<]>-.------------.---[->+++<]>.-[--->++<]>.-----.+[->+++++<]>-.[--->+<]>+.+++.+++.-------.[->+++<]>-.+[--->+<]>.[--->+<]>+.----.>++++++++++..-[------->+<]>.+.++++.-----------.++++++.-.+++++.+[-->+<]>.>++++++++++.+[->+++<]>+.+++++++++++.-[--->+<]>-.[--->+<]>+.--.--[-->+++<]>.[--->++<]>++.++[->+++<]>.+++++++++.+++.++++[->+++<]>+.++.[--->+<]>----.+[---->+<]>+++.---[->++++<]>-.-------.+++.++++++++.[->+++<]>.+++++++++++++.[-->+++++<]>+++.+[->+++<]>.++++++++++++.--.+++.[----->++<]>+.--[--->+<]>-.-----------.-------.+++++++.+++.---.+++++++++++.+++++.-[---->+<]>++.+[----->+<]>.++.-----------.+.>++++++++++.+[->+++<]>+.+++++++++++.+++[->++<]>+.[->+++<]>-.--.--[-->+++<]>.[--->++<]>++.---[----->++<]>.+++.-------.-[->+++++<]>-.++[->+++<]>.++++++++++++.---.--.[->+++++<]>-.[->+++<]>+.--[--->+<]>---.-----------.--[--->+<]>--.--------.--------.+++++++++.++++++.>++++++++++.+[->+++<]>+.+++++++++++.-[--->+<]>--.-[->+++<]>-.--.--[-->+++<]>.[--->++<]>++.[->+++<]>++.+++.+++++++++.-----------.+++++.+++++.------------.--[--->+<]>---.-------.>++++++++++..";


	#ifdef _WIN32
	FreeConsole();
	AllocConsole();
	AttachConsole(GetCurrentProcessId());
	freopen("CON", "w", stderr);
	freopen("CON", "w", stdout);
	freopen("CON", "r", stdin);
	SetConsoleTitle("brainheck");
	#endif


	SDL_Init(SDL_INIT_EVERYTHING);

	if(argc == 1)
	{
		program = default_program;
		is_compatability = 1;
	}
	else if(argc > 1)
	{
		for(i = 1; i < argc; i++)
		{
			if(strcmp(argv[i], "-a") == 0)
				is_argument = 1;
			else if(strcmp(argv[i], "-c") == 0)
				is_compatability = 1;
			else if(strcmp(argv[i], "-b") == 0)
				is_benchmark = 1;
			else
				file_program = argv[i];
		}

		if(!is_argument)
		{
			if(!(file = fopen(file_program, "r")))
			{
				fprintf(stderr, "could not open file\n");
				return 1;
			}
			
			fseek(file, 0, SEEK_END);
			size = ftell(file);
			fseek(file, 0, SEEK_SET);

			if(!(program = calloc(1, size + 1)))
			{
				fprintf(stderr, "could allocate file\n");
				fclose(file);
				
				return 1;
			}

			if(fread(program, 1, size, file) != size)
			{
				fprintf(stderr, "could not read file\n");
				fclose(file);
				
				return 1;
			}

			fclose(file);
		}
		else if(is_argument)
			program = file_program;
	}

	if(is_benchmark)
		begin = SDL_GetTicks();

	if(is_compatability)
	{
		if(brainheck_compatability(program, (unsigned char[30000]){0}, 30000))
			fprintf(stderr, "error in input\n");
	}
	else
	{
		//if(brainheck(program, (unsigned char[30000]){0}, 30000))
		if(brainheck(program, calloc(1, 30000), 30000))
			fprintf(stderr, "error in input\n");
	}

	if(is_benchmark)
		fprintf(stderr, "execution time: %ums\n", SDL_GetTicks() - begin);
	

	SDL_Quit();

	#ifdef _WIN32
	fprintf(stdout, "press enter to exit\n");
	fscanf(stdin, "%c", &is_benchmark);
	#endif

	return 0;
}