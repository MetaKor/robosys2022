#!/bin/bash

ip=$(hostname -I)
ip=${ip::-1}

name=$(hostname)

# ---- Slack API ----
A="text=SSH into \`"
B="\` using \`ssh ubuntu@\""
C="\"\`"
msg="$A$name$B$ip$C"

# You will need to source own channel ID and API token
# See the README for details

curl https://slack.com/api/chat.postMessage \
-d "$msg" \
-d "channel=????????????" \
-H "Authorization: Bearer xoxb-??????????" \
-X POST
