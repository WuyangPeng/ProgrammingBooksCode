#include "../Fly3D.h"

console::console()
{
	memset(buf,0,sizeof(char *)*CONSOLE_MAX_LINES);
	nlines=0;
	cmd_line[0]=0;
	cmd_pos=0;
	mode=0;
	winlines=0;
	time=0;
	linecount=0;
}

console::~console()
{
	int i;
	for( i=0;i<nlines;i++ )
		if (buf[i])
			delete buf[i];
}

void console::step(int dt)
{
	time-=dt;
	if (time<0)
	{
		time=20;
		if (mode>0)
		{
			if (winlines<CONSOLE_LIN/3)
				winlines++;
		}
		else if (mode<0)
		{
			if (winlines>0)
				winlines--;
			if (winlines==0)
			{
				mode=0;
				flyengine->noinput=0;
			}
		}
	}
}

void console::show()
{
	mode=1;
	flyengine->noinput=1;
	cmd_line[cmd_pos=0]=0;
}

void console::hide()
{
	mode=-1;
	cmd_line[cmd_pos=0]=0;
}

void console::add_string(char *fmt, ...)
{
    static char str[256];

    va_list va;
    va_start( va, fmt );
    wvsprintf( str, fmt, va );
    va_end( va );
	strupr( str );

	if (nlines==CONSOLE_MAX_LINES)
		delete buf[--nlines];
	memmove(&buf[1],&buf[0],sizeof(char *)*nlines);
	int len=strlen(str);
	buf[0]=new char[len+1];
	memcpy(buf[0],str,len+1);
	nlines++;
	linecount++;
}

void console::draw()
{
	int i;
	float f1,f2;

	dx=(float)screen_sx/CONSOLE_COL;
	dy=(float)screen_sy/CONSOLE_LIN;

	f1=CONSOLE_LIN/3*dy;
	f2=winlines*dy;

	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	tc->use(flyengine->consolepic);
	glBegin(GL_QUADS);
		glTexCoord2f(1,0);
		glVertex2f((float)screen_sx,screen_sy+(f1-f2));
		glTexCoord2f(0,0);
		glVertex2f(0,screen_sy+(f1-f2));
		glTexCoord2f(0,1);
		glVertex2f(0,screen_sy-f2-4);
		glTexCoord2f(1,1);
		glVertex2f((float)screen_sx,screen_sy-f2-4);
	glEnd();

	glBlendFunc(GL_ONE,GL_ONE);
	tc->use(flyengine->fontspic);
	for( i=0;i<winlines-1;i++ )
		if (winlines-i-2<nlines)
			draw_text(dx,i*dy,buf[winlines-i-2]);

	f1=(float)draw_text(dx,i*dy,cmd_line)+1;

	tc->use(-1);
	unsigned char uc=abs((flyengine->cur_time%500)-250);
	glColor3ub(uc,uc,uc);
	glBegin(GL_QUADS);
		glVertex2f(f1,screen_sy-i*dy-dy);
		glVertex2f(f1+dx/8,screen_sy-i*dy-dy);
		glVertex2f(f1+dx/8,screen_sy-i*dy);
		glVertex2f(f1,screen_sy-i*dy);
	glEnd();
}

float console::draw_text(float x,float y,char *text)
{
	int len=strlen(text),i;
	float xx,yy,xy=1.0f/FONTS_NUM;

	y=screen_sy-y-dy;

	for( i=0;i<len;i++ )
		if (text[i]>=32 && text[i]<96)
		{
		xx=((text[i]-32)%FONTS_NUM)*xy;
		yy=((text[i]-32)/FONTS_NUM)*xy;

		glBegin(GL_QUADS);
		glTexCoord2f(xx+xy,yy+xy);
		glVertex2f(x+dx,y);

		glTexCoord2f(xx+xy,yy);
		glVertex2f(x+dx,y+dy);

		glTexCoord2f(xx,yy);
		glVertex2f(x,y+dy);

		glTexCoord2f(xx,yy+xy);
		glVertex2f(x,y);
		glEnd();

		x+=flyengine->fonts_width[text[i]-32]*dx/FONTS_SIZE;
		}
	
	return x;
}

void console::key_press(int key)
{
	if (key==VK_ESCAPE)
		if (mode==0)
			show();
		else hide();
	else 
	if (key==VK_RETURN)
		{
			command_exec(cmd_line);
			cmd_line[0]=0;
			cmd_pos=0;
		}
	else
	if (key==8)
		{
			if (cmd_pos>0)
				cmd_line[--cmd_pos]=0;
		}
	else
	if (mode)
	{
		if (key>='a' && key<='z')
			key-='a'-'A';
		if (key>=32 && key<96 && cmd_pos<80) 
		{
			cmd_line[cmd_pos++]=key;
			cmd_line[cmd_pos]=0;
		}
	}
}

int console::command_tokens(char *str,char **token)
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

void console::command_exec(char *str) 
{
	char *token[256],buf[256];
	int ntoken;
	int i,j,k;

	strcpy(buf,">");
	strcat(buf,str);
	add_string(buf);
	strlwr(buf);

	ntoken=command_tokens(&buf[1],token);

	if (ntoken==0)
		{
		add_string("Invalid command!");
		return;
		}

	if (!strcmp(token[0],"help") || token[0][0]=='?')
		{
		add_string("commands:");
		add_string(" get [ varname | objname.objparam ]");
		add_string(" set [ varname | objname.objparam ] val");
		add_string(" map [ path/level.fly ]");
		add_string(" connect");
		add_string(" save");
		add_string(" reinit");
		add_string(" list [ \"plugins\" | \"classes\" | classname | objname ]");
		add_string(" create classname objname");
		add_string(" destroy objname");
		add_string(" activate objname");
		add_string(" insert plugin.dll");
		add_string(" remove plugin.dll");
		add_string(" exec commandline");
		add_string(" quit");
		}
	else
	if (!strcmp(token[0],"map"))
	{
		if (ntoken==1)
			add_string("map: %s",flyengine->flyfile[0]==0?"(none)":flyengine->flyfile);
		else
			{
			flyengine->close_multiplayer();
			flyengine->open_fly_file(token[1]);
			add_string("map: %s",flyengine->flyfile[0]==0?"(none)":flyengine->flyfile);
			}
	}
	else
	if (!strcmp(token[0],"quit"))
		{
		DestroyWindow(hFlyWnd);
		}
	else
	if (!strcmp(token[0],"exec"))
		{
		char c[256];
		strcpy(c,flyengine->flysdkpath);
		strcat(c,token[1]);
		WinExec(c,SW_SHOW);
		}
	else
	if (!strcmp(token[0],"connect"))
		{
		flyengine->join_multiplayer();
		add_string("map: %s",flyengine->flyfile[0]==0?"(none)":flyengine->flyfile);
		}
	else
	if (!strcmp(token[0],"insert"))
		{
		if (ntoken==1)
			add_string("Missing parameters!");
		else
		{
			i=flyengine->dll.add_dll(token[1]);
			if (i==-1)
				add_string("Invalid plugin dll!");
			else flyengine->dll.load_classes(i,0);
		}
	}
	else
	if (!strcmp(token[0],"remove"))
		{
		if (ntoken==1)
			add_string("Missing parameters!");
		else
			if (flyengine->dll.delete_dll(token[1])==0)
				add_string("Invalid plugin dll!");
		}
	else
	if (!strcmp(token[0],"create"))
		{
		if (ntoken<3)
			add_string("Missing parameters!");
		else
			{
			bsp_object *obj=flyengine->dll.add_class(token[1]);
			if (obj==0)
				add_string("Invalid class name!");
			else
				{
				strcpy(obj->long_name,token[2]);
				obj->name[0]=0;
				}
			}
		}
	else
	if (!strcmp(token[0],"destroy"))
		{
		if (ntoken<2)
			add_string("Missing parameters!");
		else
			{
			bsp_object *o=flyengine->active_obj0;
			while(o)
				{
				if (!stricmp(o->long_name,token[1]))
					break;
				o=(bsp_object *)o->next_obj;
				}
			if (o==0)
				add_string("Invalid class name!");
			else 
				o->life=-1;
			}
		}
	else
	if (!strcmp(token[0],"list"))
		{
		char s[256]="";
		if (ntoken==1)
		{
			param_desc pd;
			j=flyengine->get_global_param_desc(0,0);
			for( k=0;k<j;k++ )
				{
				flyengine->get_global_param_desc(k,&pd);
				strcpy(s,pd.name);
				strcat(s,"=");
				strcat(s,pd.get_string());
				add_string(s);
				}
		}
		else
		if (!strcmp(token[1],"plugins"))
			{
			for( i=0;i<flyengine->dll.ndll;i++ )
				add_string(flyengine->dll.dll[i]->dll_filename);
			}
		else
		if (!strcmp(token[1],"classes"))
			{
			for( i=0;i<flyengine->dll.ncd;i++ )
				add_string(flyengine->dll.cd[i]->get_name());
			}
		else
		if (strchr(token[1],'.'))
			{
			char *c=strchr(token[1],'.');
			*c=0;
			bsp_object *o=flyengine->stock_obj0;
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
						add_string(s);
						break;
						}
					}
				if (k==j)
					add_string("Invalid object parameter!");
				}
			else add_string("Invalid object name!");
			}
		else
			{
			for( i=0;i<flyengine->dll.ncd;i++ )
				if (!strcmp(token[1],flyengine->dll.cd[i]->get_name()))
					break;
			if (i<flyengine->dll.ncd)
				{
				j=flyengine->dll.cd[i]->get_type();
				bsp_object *o=flyengine->stock_obj0;;
				while(o)
					{
					if (o->type==j)
						add_string(o->long_name);
					o=(bsp_object *)o->next_obj;
					}
				}
			else
				{
				bsp_object *o=flyengine->stock_obj0;
				while(o)
					{
					if (!stricmp(o->long_name,token[1]))
						break;
					o=(bsp_object *)o->next_obj;
					}
				if (o==0)
					add_string("Invalid class/object name!");
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
						add_string(s);
						}
					}
				}
			}
		}
	else
	if (!strcmp(token[0],"save"))
		{
		flyengine->save_fly_file(flyengine->flyfile);
		add_string("Saved!");
		return;
		}
	else
	if (!strcmp(token[0],"set"))
	{
		if (ntoken<3)
		{
			add_string("Missing parameters!");
			return;
		}

		if (strchr(token[1],'.'))
		{
			char *c=strchr(token[1],'.');
			*c=0;
			i=flyengine->set_obj_param(token[1],c+1,token[2]);
			if (i==1)
				add_string("Invalid object name!");
			else if (i==2) 
				add_string("Invalid object parameter!");
			else if (i==3) 
				add_string("Unsuported parameter type!");
			return;
		}

		if (flyengine->set_global_param(token[1],token[2])==0)
			add_string("Invalid parameter name!");
	}
	else if (!strcmp(token[0],"activate"))
	{
		bsp_object *o=flyengine->stock_obj0;
		while(o)
		{
			if (!stricmp(token[1],o->long_name))
				break;
			o=(bsp_object *)o->next_obj;
		}
		if (o)
			flyengine->activate(o->clone());
		else add_string("Invalid object name!");
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
				add_string("Invalid sintax!");
				return;
				}
			*c=0;
			i=flyengine->get_obj_param(objname,objparam+1,s);
			if (i)
			{
			if (i==1)
				add_string("Invalid object name!");
			else if (i==2) 
				add_string("Invalid object parameter!");
			else if (i==3) 
				add_string("Unsuported parameter type!!");
			return;
			}
		}
		else
		{
			i=flyengine->get_global_param_desc(0,0);
			param_desc pd;
			for( j=0;j<i;j++ )
				{
				flyengine->get_global_param_desc(j,&pd);
				if (!stricmp(token[1],pd.name))
					break;
				}
			if (j==i)
				{
				add_string("Invalid variable name!!");
				return;
				}
			else strcpy(s,pd.get_string());
		}
		add_string(s);
	}
	else 
		add_string("Invalid command!!");
}

