# hello-rest-c

This is the skeleton of a REST-based webservice, implemented in C, and
using GNU microhttpd as the HTTP server. It comes from a discussion 
with colleagues about what consitutes a "microservice" in modern practice.
The ability of GraalVM to create a native binary from Java is impressive, but I 
find it hard to think of a 27Mb (stripped) binary size as a "microservice". 

This C version has a compiled code size of 23kB, and a total memory footprint
of about 4Mb. That's including all the SSL support, which isn't used in the
example, and code to parse the headers and URI arguments which, again, isn't used
here.

Run the service like this:

    $ ./hello-rest-c --debug 

Then invoke it like this:

    $ curl http://localhost:8080/greet/fred
    {"hello": "fred"}

The actual implementation of the service, such as it is, is in
request\_handler.c. The rest of the code just starts the HTTP server, parses
the command line, handles signals, and does logging.

