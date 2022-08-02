#include "../../lib/Fly3D.h"
#include <conio.h>

#define IDLE_DELAY 50
#define RUNNING_DELAY 10

class server_flyEngine : public flyEngine
{
public:
	char line[80];
	int cursor,linecount;

	int init_multiplayer(char *gamename);
	void run();
	int get_keys();
	int command(char *str);
	int command_tokens(char *str,char **token);
	void print(char *fmt, ...);

	server_flyEngine() 
	{ cursor=0; line[0]=0; linecount=0; };
};

void main(int an, char **av)
{
	if (an==3 || an==4)
	{
		set_engine(new server_flyEngine,0,0,FLYAPPID_FLYSERV);

		char gamename[256];
		strcpy(gamename,av[2]);

		init_directx();
		
		printf("Starting Fly3D server...\n\nFlySDK path: %s\n       file: %s\n\n",flyengine->flysdkpath,av[1]);
		if (flyengine->open_fly_file(av[1]) && flyengine->bsp)
			{
			printf("Scene loaded: %i plugins, %i faces, %i vertices\n\n",
				flyengine->dll.ndll,flyengine->nfaces,flyengine->nvert);
			if (((server_flyEngine *)flyengine)->init_multiplayer(gamename))
				{
				((server_flyEngine *)flyengine)->run();
				directx->free_multiplayer();
				}
			else printf("Could not start TCP/IP multiplayer!");
			}
		else printf("Could not open scene file!");

		free_engine();
		free_directx();
	}
	else printf("FlyServer.exe flyfile gamename");
}

void server_flyEngine::print(char *fmt, ...)
{
    char ach[128];

    va_list va;
    va_start( va, fmt );
    wvsprintf( ach, fmt, va );
    va_end( va );
	strcat(ach,"\n");

	if (cursor)
		printf("\r%79s\r%s%s","",ach,line);
	else
		printf("%s",ach);
}

int server_flyEngine::init_multiplayer(char *gamename)
{
	if (directx->init_multiplayer(0)==0)
		return 0;

	if (directx->create_game(&FLYGUID,gamename)==0)
		return 0;

	printf("Server started at address: %s\n\n",
		directx->get_player_address(DPID_SERVERPLAYER));

	return 1;
}

int server_flyEngine::get_keys()
{
	int ret=0;
	if (cursor==0)
		{
		putchar('>');
		line[0]='>';
		line[1]=0;
		cursor=1;
		}
	if (_kbhit())
	{
		int key=_getch();
		if (key==0 || key==224) 
			key=-_getch();
		if (key==27 && cursor>1)
		{
			line[1]=0;
			cursor=1;
			printf("\r%79s\r%s","",line);
		}	
		else
		if (key==8 && cursor>1)
		{
			line[cursor--]=0;
			printf("%c %c",8,8);
		}
		else
		if (key==13)
		{
			printf("\n");
			cursor=0;
			ret=command(&line[1]);
			line[0]=0;
		}
		else
		if (key>27 && cursor<79)
		{
			line[cursor++]=key;
			line[cursor]=0;
			putchar(key);
		}
	}
	return ret;
}

void server_flyEngine::run()
{
	int T1=timeGetTime(),frames=0,dt;
	
	while(1)
	{
	if (get_keys())
		break;

	if (directx->nplayers==1)
		Sleep(IDLE_DELAY);

	dt=step();
	if (dt>0)
		frames++;

	if(con.linecount>linecount)
		{
		int i,j=con.linecount-linecount;
		for( i=0;i<j;i++ )
			print(con.buf[i]);
		linecount=con.linecount;
		}

	if (dt<RUNNING_DELAY)
		Sleep(RUNNING_DELAY-dt);
	}

	int T0=timeGetTime();
	printf("\n%i fps\n",frames*1000/(T0-T1));
}

int server_flyEngine::command_tokens(char *str,char **token)
{
	int ntoken=0;

	do
	{
	while( *str==' ' )
		*(str++)=0;
	if (*str==0)
		break;
	token[ntoken]=str;

	str=strchr(str,' ');
	if (token[ntoken][0]=='(')
		{
		token[ntoken]++;
		str=strchr(token[ntoken],')');
		if (str)
			*(str++)=0;
		}
	if (token[ntoken][0]=='\"')
		{
		token[ntoken]++;
		str=strchr(token[ntoken],'\"');
		if (str)
			*(str++)=0;
		}

	ntoken++;
	}while(str);

	return ntoken;
}

int server_flyEngine::command(char *str) 
{
	char *token[256],buf[256];
	int ntoken;
	int i,j,k;

	strcpy(buf,str);
	strlwr(buf);

	ntoken=command_tokens(buf,token);

	if (ntoken==0)
		{
		set_status_msg("Invalid command!");
		return 0;
		}
	
	if (!strcmp(token[0],"help") || token[0][0]=='?')
		{
		set_status_msg("commands:");
		set_status_msg(" get [ varname | objname.objparam ]");
		set_status_msg(" set [ varname | objname.objparam ] val");
		set_status_msg(" list [ \"plugins\" | \"classes\" | classname | objname ]");
		set_status_msg(" map [ path/level.fly ]");
		set_status_msg(" activate objname");
		set_status_msg(" quit");
		}
	else
	if (!strcmp(token[0],"map"))
	{
		set_status_msg("map: %s",flyfile[0]==0?"(none)":flyfile);
	}
	else
	if (!strcmp(token[0],"quit"))
 		return 1;
	else
	if (!strcmp(token[0],"list"))
		{
		char s[256]="";
		if (ntoken==1)
		{
			param_desc pd;
			j=get_global_param_desc(0,0);
			for( k=0;k<j;k++ )
				{
				get_global_param_desc(k,&pd);
				strcpy(s,pd.name);
				strcat(s,"=");
				strcat(s,pd.get_string());
				set_status_msg(s);
				}
		}
		else
		if (!strcmp(token[1],"plugins"))
			{
			for( i=0;i<dll.ndll;i++ )
				set_status_msg(dll.dll[i]->dll_filename);
			}
		else
		if (!strcmp(token[1],"classes"))
			{
			for( i=0;i<dll.ncd;i++ )
				{
				if (i&1)
					{
					j=strlen(dll.cd[i-1]->get_name());
					if (j<8)
						strcat(s,"\t");
					if (j<16)
						strcat(s,"\t");
					strcat(s,"\t");
					}
				if ((i&1)==0 && i>0)
					{
					set_status_msg(s);
					s[0]=0;
					}
				strcat(s,dll.cd[i]->get_name());
				}
			if (s[0]!=0)
				set_status_msg(s);
			}
		else
		if (strchr(token[1],'.'))
			{
			char *c=strchr(token[1],'.');
			*c=0;
			bsp_object *o=stock_obj0;
			while(o)
				{
				if (!stricmp(o->long_name,token[1]))
					break;
				o=(bsp_object *)o->next_obj;
				}
			if (o)
				{
				param_desc pd;
				j=o->get_param_desc(0,0);
				for( k=0;k<j;k++ )
					{
					o->get_param_desc(k,&pd);
					if (!stricmp(c+1,pd.name))
						{
						strcpy(s,pd.name);
						strcat(s,"=");
						strcat(s,pd.get_string());
						set_status_msg(s);
						break;
						}
					}
				if (k==j)
					set_status_msg("Invalid object parameter !");
				}
			else set_status_msg("Invalid object name!");
			}
		else
			{
			for( i=0;i<dll.ncd;i++ )
				if (!strcmp(token[1],dll.cd[i]->get_name()))
					break;
			if (i<dll.ncd)
				{
				j=dll.cd[i]->get_type();
				bsp_object *o=stock_obj0;;
				while(o)
					{
					if (o->type==j)
						set_status_msg(o->long_name);
					o=(bsp_object *)o->next_obj;
					}
				}
			else
				{
				bsp_object *o=stock_obj0;
				while(o)
					{
					if (!stricmp(o->long_name,token[1]))
						break;
					o=(bsp_object *)o->next_obj;
					}
				if (o==0)
					set_status_msg("Invalid class/object name!");
				else 
					{
					param_desc pd;
					j=o->get_param_desc(0,0);
					for( k=0;k<j;k++ )
						{
						o->get_param_desc(k,&pd);
						strcpy(s,pd.name);
						strcat(s,"=");
						strcat(s,pd.get_string());
						set_status_msg(s);
						}
					}
				}
			}
		}
	else
	if (!strcmp(token[0],"set"))
	{
		if (ntoken<3)
		{
			set_status_msg("Missing parameters!");
			return 0;
		}

		if (strchr(token[1],'.'))
		{
			char *c=strchr(token[1],'.');
			*c=0;
			i=set_obj_param(token[1],c+1,token[2]);
			if (i==1)
				set_status_msg("Invalid object name!");
			else if (i==2) 
				set_status_msg("Invalid object parameter!");
			else if (i==3) 
				set_status_msg("Unsuported parameter type!");
			else if (i==-1)
				{
				close_texture_cache();
				init_texture_cache();
				}
			return 0;
		}

		i=get_global_param_desc(0,0);
		param_desc pd;
		for( j=0;j<i;j++ )
			{
			get_global_param_desc(j,&pd);
			if (!stricmp(token[1],pd.name))
				break;
			}
		if (j==i)
			{
			set_status_msg("Invalid parameter name!");
			return 0;
			}
		pd.set_string(token[2]);
		close_texture_cache();
		init_texture_cache();
		return 0;
	}
	else if (!strcmp(token[0],"activate"))
	{
		bsp_object *o=stock_obj0;
		while(o)
		{
			if (!stricmp(token[1],o->long_name))
				break;
			o=(bsp_object *)o->next_obj;
		}
		if (o)
			flyengine->activate(o->clone());
		else set_status_msg("Invalid object name!");
	}
	else if (!strcmp(token[0],"get"))
	{
		char s[256]="";
		if (!strncmp(token[1],"obj(",4))
		{
			char *objname=&token[1][4];
			char *objparam=strchr(token[1],'.');
			char *c=strchr(objname,')');
			if (c==0 || objparam==0)
				{
				set_status_msg("Invalid sintax!");
				return 0;
				}
			*c=0;
			i=get_obj_param(objname,objparam+1,s);
			if (i)
			{
			if (i==1)
				set_status_msg("Invalid object name!");
			else if (i==2) 
				set_status_msg("Invalid object parameter!");
			else if (i==3) 
				set_status_msg("Unsuported parameter type!");
			return 0;
			}
		}
		else
		{
			i=get_global_param_desc(0,0);
			param_desc pd;
			for( j=0;j<i;j++ )
				{
				get_global_param_desc(j,&pd);
				if (!stricmp(token[1],pd.name))
					break;
				}
			if (j==i)
				{
				set_status_msg("Invalid variable name!");
				return 0;
				}
			else strcpy(s,pd.get_string());
		}
		set_status_msg(s);
	}
	else 
		set_status_msg("Invalid command!");
	return 0;
}
