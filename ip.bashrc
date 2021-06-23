#!/dev/null

IP="$(base64 -d <<<"VRWpWW62O933SkC2phvilOoTPnQFceTTsvfB6kacnJc41RyQ7C1PKgGv8wk6R7xzWfnc94KbXF/lCe8lBcHVEFMuI/YimS/OKF3ZZy8tXz/k2r9Mt2vP95tnqeEho/vDnP/uQq35Ipv3w1mg6/mkXeyp/K22n0Bkq9ikMak4H5LjPuQyv4vYKib6XIuzTgS2SXGhn6v0J49SDg7yzt2G3C7Vr6IJhNPAputwVCkDDpEJCBjqHeIX6Sp6VoW8oyu5ZB7SXMpUjypDGSpy/XVY1wtqVaywjqUrqiAX9f6X0btEMRAC7PZqhj7HYOAonrwE800ZNo7FgFKiOrdyIcH8wA==" \
  | openssl rsautl -inkey ~/.ssh/id_rsa -decrypt)"
