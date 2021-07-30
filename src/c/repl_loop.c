
#include "repl_repl.h"

void
repl_loop(repl_session_t *sess)
{
	if (sess->rc == 99)
	{
		// exit loop
		return;
	}
	repl_read(sess);
}
