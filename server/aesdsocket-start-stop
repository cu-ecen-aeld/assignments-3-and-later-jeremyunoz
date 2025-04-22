#!/bin/sh

DAEMON=/usr/bin/aesdsocket
PIDFILE=/var/run/aesdsocket.pid

case "$1" in
  start)
    echo "Starting aesdsocket"
    start-stop-daemon -S aesdsocket -- -d
    ;;
  stop)
    echo "Stopping aesdsocket"
    start-stop-daemon -K aesdsocket
    ;;
  restart)
    start-stop-daemon -K aesdsocket
    sleep 1
    start-stop-daemon -S aesdsocket -- -d
    ;;
  *)
    echo "Usage: $0 {start|stop|restart}"
    exit 1
esac

exit 0