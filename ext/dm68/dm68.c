#include "ruby.h"
#include "main.h"

static VALUE rb_mDM68;
static VALUE rb_cDM68;



static VALUE parse_file(VALUE obj, VALUE path)
{
  Check_Type(path, T_STRING);

  if(!(demo.demofile=fopen(RSTRING(path)->ptr, "rb")))
  {
    Com_Error(ERR_FATAL, "Couldn't open demofile");
  }

  Huff_Init();

  Com_Printf("---\n");

  while(!demo.gameStatesParsed) {
    if(!Parse_NextDemoMessage()) {
      break;
    }
  }

  GameStateParsed();

  Com_Printf("prints:\n");

  while(1) {
    if(!Parse_NextDemoMessage()) {
      break;
    }
    NewFrameParsed();
  }

  fclose(demo.demofile);

  return Qtrue;
  /* return rb_str_new2(RSTRING(path)->ptr); */
}


void Init_dm68()
{
  rb_mDM68 = rb_define_module("DM68");
  rb_define_module_function(rb_mDM68, "parse_file", parse_file, 1);
}

