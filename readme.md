## [ec2-udp](https://github.com/Un1Gfn-network/ec2-udp)

https://console.aws.amazon.com/ec2

```bash
# https://superuser.com/a/576558
# openssl-rsautl(1ssl)
echo "<IP_ADDRESS>" \
  | openssl rsautl -inkey <(ssh-keygen -f ~/.ssh/id_rsa.pub -e -m PKCS8) -pubin -encrypt -ssl \
  | base64 -w0
```

https://superuser.com/q/1615110

```bash
pacman -Qo nc | grep -q openbsd \
  && env TERM=xterm-256color \
       ssh \
         -i ~/.ssh/id_rsa \
         -l ubuntu \
         -o PasswordAuthentication=no \
         -o PreferredAuthentications=publickey \
         -o "ProxyCommand=nc -X 5 -x 127.0.0.1:1080 %h %p" \
         -p 22 \
         "$(base64 -d <<<"VRWpWW62O933SkC2phvilOoTPnQFceTTsvfB6kacnJc41RyQ7C1PKgGv8wk6R7xzWfnc94KbXF/lCe8lBcHVEFMuI/YimS/OKF3ZZy8tXz/k2r9Mt2vP95tnqeEho/vDnP/uQq35Ipv3w1mg6/mkXeyp/K22n0Bkq9ikMak4H5LjPuQyv4vYKib6XIuzTgS2SXGhn6v0J49SDg7yzt2G3C7Vr6IJhNPAputwVCkDDpEJCBjqHeIX6Sp6VoW8oyu5ZB7SXMpUjypDGSpy/XVY1wtqVaywjqUrqiAX9f6X0btEMRAC7PZqhj7HYOAonrwE800ZNo7FgFKiOrdyIcH8wA==" \
              | openssl rsautl -inkey ~/.ssh/id_rsa -decrypt)"
```

https://github.com/Un1Gfn-network/cm-mailman/blob/master/main.c (tcp http srv) \
https://github.com/Un1Gfn-network/cm-exp02/blob/master/server.c (udp srv) \
https://github.com/Un1Gfn-nt/ntexec/blob/master/win_server.c (udp srv)
