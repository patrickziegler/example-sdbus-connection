## Notes

- Start the bus with `dbus-daemon --config-file dbus.conf`
- Watch the bus with `dbus-monitor --address unix:path=/tmp/bus.socket`

## Test

- With bus running, start server and client, the latter will continuously call the server interface
- Test 1: see what happens to the client if you stop and then restart the server -> `... .service not provided` error will appear, but operation resumes as soon as the server is back
- Test 2: see what happens to the client if you stop the bus (dbus-daemon) -> the client will coredump because the eventqueue will raise an uncatched exception from the newly spawned thread that is used by sbus-cpp

## References

- https://github.com/Kistler-Group/sdbus-cpp/blob/master/docs/using-sdbus-c++.md
