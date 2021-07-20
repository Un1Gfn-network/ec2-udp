# [erinnern](https://github.com/Un1Gfn-network/erinnern)

## Misc

[encrypt](https://superuser.com/a/576558) text with ssh-rsa public key

    # openssl-rsautl(1ssl)
    echo "<IP_ADDRESS>" \
      | openssl rsautl -inkey <(ssh-keygen -f ~/.ssh/id_rsa.pub -e -m PKCS8) -pubin -encrypt -ssl \
      | base64 -w0

random [repo name](https://www.bestrandoms.com/random-german-words)

rfc1928 - 7. [Procedure for UDP-based clients](https://datatracker.ietf.org/doc/html/rfc1928#section-7) \
comments in ss-libev [udprelay.c](https://github.com/shadowsocks/shadowsocks-libev/blob/e04b73d1b6ad04d047d0c81ac1291bc281429ba1/src/udprelay.c#L1020)

[SOCKS](https://en.wikipedia.org/wiki/SOCKS) on Wikipedia

[EC2](https://console.aws.amazon.com/ec2) Management Console

SOCKS5 ProxyCommand for ssh (nc from [openbsd-netcat](https://superuser.com/q/1615110#comment2539331_1615110))

    source ~/erinnern/secret.bashrc
    ssh

tcpdump

    sudo tcpdump -i eth0 "udp"

## UDP

sync source code

    cd ~/erinnern
    source erinnern.bashrc
    inotifywait -m -q -e close_write --format "%w" udp_server.c socket2.c socket2.h socks5.h secret.h | xargs -d '\n' -I{} -t bash -c 'scp "$@"' GARBAGE {}

udp_server.out

    cd ~/erinnern
    source erinnern.bashrc
    ssh
<!-- -->
    tmux attach || tmux
<!-- -->
    gcc -std=gnu11 -Wall -Wextra -o udp_server.out udp_server.c socket2.c && ./udp_server.out

udp_client_proxy.out

    cd ~/erinnern && gcc -std=gnu11 -Wall -Wextra -o udp_client_proxy.out udp_client_proxy.c socket2.c socks5.c && ./udp_client_proxy.out

<details><summary><del>nc server</del></summary>

    source ~/erinnern/secret.bashrc
    ssh
<!--  -->
    tmux attach || tmux
<!--  -->
    dpkg-query -S /bin/nc.openbsd
    nc.openbsd -4 -l -n -u -v 0.0.0.0 $LC_UDPORT

</details>

<details><summary><del>nc client</del></summary>

    source ~/erinnern/secret.bashrc
    pacman -Qo /usr/bin/nc
    nc -4 -N -n -u -v "$IP" $UDPORT
    # nc -4 -N -n -u -v -X 5 -x 127.0.0.1:1080 "$IP" $UDPORT # nc: no proxy support for UDP mode

</details>

## TCP

TCP server nc

    source ~/erinnern/secret.bashrc
    ssh dpkg-query -S /bin/nc.openbsd
    ssh nc.openbsd -4 -l -n -u -v 0.0.0.0 $TCPORT

TCP client ??

    ?

|protocol|type|example|
|-|-|-|
|http|server_unix|[heroku](https://github.com/Un1Gfn-network/cm-mailman/blob/master/main.c)|
| udp|server_unix|[cm](https://github.com/Un1Gfn-network/cm-exp02/blob/master/server.c)|
| udp|**client_unix**|[cm](https://github.com/Un1Gfn-network/cm-exp02/blob/master/client.c)|
| udp|client_win |[cm](https://github.com/Un1Gfn-network/cm-exp02/blob/master/client_win.c)|
| udp|server_win |[ntexec](https://github.com/Un1Gfn-nt/ntexec/blob/master/win_server.c)|
| udp|**client_unix**|[ntexec](https://github.com/Un1Gfn-nt/ntexec/blob/master/ntexec.c)|
<!--
|||||
-->
