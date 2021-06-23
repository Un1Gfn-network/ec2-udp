## [erinnern](https://github.com/Un1Gfn-network/erinnern)

random [repo name](https://www.bestrandoms.com/random-german-words)

rfc1928 - 7. [Procedure for UDP-based clients](https://datatracker.ietf.org/doc/html/rfc1928#section-7)

[EC2](https://console.aws.amazon.com/ec2) Management Console

[encrypt](https://superuser.com/a/576558) text with ssh-rsa public key

    # openssl-rsautl(1ssl)
    echo "<IP_ADDRESS>" \
      | openssl rsautl -inkey <(ssh-keygen -f ~/.ssh/id_rsa.pub -e -m PKCS8) -pubin -encrypt -ssl \
      | base64 -w0

SOCKS5 ProxyCommand for ssh (nc from [openbsd-netcat](https://superuser.com/q/1615110#comment2539331_1615110))

    source ip.bashrc
    ssh

nc server

    source ip.bashrc
    ssh dpkg-query -S /bin/nc.openbsd
    ssh nc.openbsd -4 -l -n -u -v 0.0.0.0 $PORT

<details><summary>nc client</summary>

    source ip.bashrc
    pacman -Qo /usr/bin/nc
    nc -4 -N -n -u -v "$IP" $PORT
    # nc -4 -N -n -u -v -X 5 -x 127.0.0.1:1080 "$IP" $PORT # nc: no proxy support for UDP mode

</details>

|protocol|type|example|
|-|-|-|
|http|server_unix|[heroku](https://github.com/Un1Gfn-network/cm-mailman/blob/master/main.c)|
| udp|server_unix|[cm](https://github.com/Un1Gfn-network/cm-exp02/blob/master/server.c)|
| udp|**client_unix**|[cm](https://github.com/Un1Gfn-network/cm-exp02/blob/master/client.c)|
| udp|client_win |[cm](https://github.com/Un1Gfn-network/cm-exp02/blob/master/client_win.c)|
| udp|server_win |[ntexec](https://github.com/Un1Gfn-nt/ntexec/blob/master/win_server.c)|
| udp|**client_unix**|[ntexec](https://github.com/Un1Gfn-nt/ntexec/blob/master/ntexec.c)|

<!-- ||||| -->
