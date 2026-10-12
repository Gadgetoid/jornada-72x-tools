#!/bin/sh
set -e
cd "$(dirname "$0")"
if ! command -v pppd >/dev/null 2>&1 && [ ! -x /usr/sbin/pppd ]; then
    echo "install.sh: install ppp first (apt install ppp)" >&2
    exit 1
fi
install -d /usr/local/lib/jornada-bridge
install -m 755 jornada-handshake jornada-desktop /usr/local/lib/jornada-bridge/
install -m 644 jornada-link@.service jornada-desktop.service /etc/systemd/system/
install -m 644 90-jornada-bridge.rules /etc/udev/rules.d/
systemctl daemon-reload
systemctl enable --now jornada-desktop.service
udevadm control --reload
echo "install.sh: installed; connect the device and start PC Link"
