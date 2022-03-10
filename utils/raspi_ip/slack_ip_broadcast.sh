#!/bin/bash

ip=$(hostname -I)
ip=${ip::-1}


# ---- Slack API ----
A="text=SSH into the RasPi using \`ssh ubuntu@\""
B="\"\`"
msg="$A$ip$B"

# You will need to source own channel ID and API token
# See the README for details

curl https://slack.com/api/chat.postMessage \
-d "$msg" \
-d "channel=??????_CHANNEL_ID_??????" \
-H "Authorization: Bearer xoxb-??????_API_TOKEN??????" \
-X POST
