#!/dev/null

source ~/erinnern/secret.bashrc || echo "${BASH_SOURCE[0]}:$LINENO:${FUNCNAME[0]}: err"

[ -n "$IP" ] || echo "${BASH_SOURCE[0]}:$LINENO:${FUNCNAME[0]}: err"
[ -n "$LC_UDPORT" ] || echo "${BASH_SOURCE[0]}:$LINENO:${FUNCNAME[0]}: err"
[ -n "$LC_TCPORT" ] || echo "${BASH_SOURCE[0]}:$LINENO:${FUNCNAME[0]}: err"

function ssh {
  pacman -Qo nc | grep -q openbsd && \
    env TERM=xterm-256color /usr/bin/ssh \
      -i ~/.ssh/id_rsa \
      -l ubuntu \
      -o PasswordAuthentication=no \
      -o PreferredAuthentications=publickey \
      -o "ProxyCommand=nc -X 5 -x 127.0.0.1:1080 %h %p" \
      -o "SendEnv LC_UDPORT" \
      "$IP" \
      "$@"
}

function scp {
  [ "$#" -ge 1 ] || { echo "${BASH_SOURCE[0]}:$LINENO:${FUNCNAME[0]}: err"; return 1; }
  pacman -Qo nc | grep -q openbsd && \
    /usr/bin/scp \
      -i ~/.ssh/id_rsa \
      -o PasswordAuthentication=no \
      -o PreferredAuthentications=publickey \
      -o "ProxyCommand=nc -X 5 -x 127.0.0.1:1080 %h %p" \
      "$@" \
      "ubuntu@$IP:/home/ubuntu/"
  # -v \
  echo "$* sent"
}

export -f scp # For xargs

# echo_var(){
#     echo "\$0 $0 \$1 $1"
#     return 0
# }

# export -f echo_var

# function rsync {
#   [ "$#" -ge 1 ] || { echo "${BASH_SOURCE[0]}:$LINENO:${FUNCNAME[0]}: err"; return 1; }
#   # -a # -rlptgoD
#   /usr/bin/rsync \
#     --daemon \
#     -v \
#     -e "ssh -o 'ProxyCommand=nc -X 5 -x 127.0.0.1:1080 %h %p'" \
#     -h \
#     --progress \
#     "$@" \
#     "ubuntu@$IP:/home/ubuntu/"
# }

# function esync {
#   [ "$#" -eq 0 ] || { echo "${BASH_SOURCE[0]}:$LINENO:${FUNCNAME[0]}: err"; return 1; }
#   entr echo /_ is modified
# }

printf "\e]0;erinnern\007"
