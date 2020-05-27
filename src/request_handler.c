/*============================================================================

  hello-ws-c
  request_handler.c
  Copyright (c)2020 Kevin Boone
  Distributed under the terms of the GPL v3.0

============================================================================*/

#define  _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <wchar.h>
#include <time.h>
#include <fcntl.h>
#include <ctype.h>
#include <microhttpd.h>
#include "defs.h" 
#include "log.h" 
#include "request_handler.h" 


struct _RequestHandler
  {
  BOOL shutdown_requested;
  const ProgramContext *context;
  }; 


/*============================================================================

  request_handler_create

============================================================================*/
RequestHandler *request_handler_create (const ProgramContext *context)
  {
  LOG_IN
  RequestHandler *self = malloc (sizeof (RequestHandler)); 
  self->shutdown_requested = FALSE;
  self->context = context;
  LOG_OUT 
  return self;
  }

/*============================================================================

  request_handler_destroy

============================================================================*/
void request_handler_destroy (RequestHandler *self)
  {
  LOG_IN
  if (self)
    {
    free (self);
    }
  LOG_OUT 
  }


/*============================================================================

  request_handler_api

============================================================================*/
void request_handler_api (RequestHandler *self, const char *uri, 
       const Props* arguments, int *code, char **page)
  {
  LOG_IN
  log_debug ("API request: %s", uri);
  char *api = "/greet/";
  int l = strlen (api);
  if (strncmp (uri, api, l) == 0)
    {
    const char *name = uri + l; 
    asprintf (page, "{\"hello\": \"%s\"}\n", name);
    *code = 200;
    }
  // TOOD Other APIs here :)
  else
    {
    asprintf (page, "Not found");
    *code = 404;
    }
  LOG_OUT
  }

/*============================================================================

  request_handler_shutdown_requested

============================================================================*/
BOOL request_handler_shutdown_requested (const RequestHandler *self) 
  {
  LOG_IN
  BOOL ret = self->shutdown_requested;
  LOG_OUT
  return ret;
  }

/*============================================================================

  request_handler_request_shutdown

============================================================================*/
void request_handler_request_shutdown (RequestHandler *self)
  {
  LOG_IN
  log_info ("Shutdown requested");
  self->shutdown_requested = TRUE;
  LOG_OUT
  }


/*============================================================================

  request_handler_get_program_context

============================================================================*/
const ProgramContext *request_handler_get_program_context 
      (const RequestHandler *self)
  {
  LOG_IN
  const ProgramContext *ret = self->context;
  LOG_OUT
  return ret;
  }

