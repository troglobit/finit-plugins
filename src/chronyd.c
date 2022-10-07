/* Setup and start system time service chronyd
 *
 * Portions Copyright (c) 2012-2022 Joachim Wiberg <troglobit@gmail.com>
 * Portions Copyright (c) 2022 Andy Savage <andy@savage.hk>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <sys/types.h>
#ifndef _LIBITE_LITE
# include <lite/lite.h>
#else
# include <libite/lite.h>
#endif

#include "finit/finit.h"
#include "finit/helpers.h"
#include "finit/plugin.h"
#include "finit/service.h"
#include "finit/conf.h"

#define CHRONYD_DAEMON "chronyd"
#define CHRONYD_ARGS   "-n -4 -f /etc/chrony.conf"
#define CHRONYD_DESC   "Chrony Time Daemon"

#ifndef CHRONYD_DAEMONUSER
#define CHRONYD_DAEMONUSER "root"
#endif

#ifndef CHRONYD_DAEMONGROUP
#define CHRONYD_DAEMONGROUP "root"
#endif

#ifndef CHRONYD_DAEMONPIDFILE
#define CHRONYD_DAEMONPIDFILE "/var/run/chronyd.pid"
#endif

static void setup(void *arg)
{
	char line[256];
	mode_t prev;
	char *cmd;

	if (rescue) {
		dbg("Skipping %s plugin in rescue mode.", __FILE__);
		return;
	}

	cmd = which(CHRONYD_DAEMON);
	if (!cmd) {
		dbg("Skipping plugin, %s is not installed.", CHRONYD_DAEMON);
		return;
	}

	prev =umask(0);

	dbg("Creating Chrony Daemon Required Directories ...");

	mksubsys("/var/run/chrony", 0770, CHRONYD_DAEMONUSER, CHRONYD_DAEMONGROUP);
	mksubsys("/var/run/chrony/dhcp", 0770, CHRONYD_DAEMONUSER, CHRONYD_DAEMONGROUP);
	mksubsys("/var/lib/chrony", 0770, CHRONYD_DAEMONUSER, CHRONYD_DAEMONGROUP);

	/* Clean up from any previous pre-bootstrap run */
	remove(CHRONYD_DAEMONPIDFILE);

	/* Register service with Finit */
	snprintf(line, sizeof(line), "[S12345789] cgroup.system pid:!%s @%s:%s %s %s -- %s",
		 CHRONYD_DAEMONPIDFILE, CHRONYD_DAEMONUSER, CHRONYD_DAEMONGROUP,
		 cmd, CHRONYD_ARGS, CHRONYD_DESC);

	if (service_register(SVC_TYPE_SERVICE, line, global_rlimit, NULL))
		err("Failed registering %s", CHRONYD_DAEMON);
	free(cmd);

	umask(prev);
}

static plugin_t plugin = {
	.name = __FILE__,
	.hook[HOOK_BASEFS_UP] = {
		.cb  = setup
	},
	.depends = { "bootmisc", "mdevd" },
};

PLUGIN_INIT(plugin_init)
{
	plugin_register(&plugin);
}

PLUGIN_EXIT(plugin_exit)
{
	plugin_unregister(&plugin);
}

/**
 * Local Variables:
 *  indent-tabs-mode: t
 *  c-file-style: "linux"
 * End:
 */
