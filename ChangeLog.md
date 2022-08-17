Change Log
==========

All relevant changes are documented in this file.

[v1.0][] - 2022-08-17
---------------------

Initial public release.  Plugins from Andy Savage.

### Changes

* New plugin, `chronyd`: ensure the system clock is synced as early as
  possible.  Running chronyd early in place of the native RTC plugin.
* New plugin, `qmi-proxy`: this plugin is for libqmi, or specifically
  the qmicli cli tool for qmi_wwan.ko module so you can run multiple
  commands using the same LTE device at once without worrying about
  allocating/releasing IDs.

### Fixes

* N/A

[v1.0]: https://github.com/troglobit/finit/compare/TAIL...v1.0
