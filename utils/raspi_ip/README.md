# Slack IP broadcast script for RasPi
This is a quick script which we use to broadcast the Pi's IP address to a dedicated Slack channel.
Created via the following tutorial: https://api.slack.com/tutorials/tracks/posting-messages-with-curl

You will need to source the channel ID of the Slack channel in which you want the bot to post, along with your relevant Slack API token. The token can be aquired via the above linked tutorial.

## Set to run on boot
To make the script run on boot, open your crontab file in your default editor via
```
sudo crontab -e
```
and add the following line at the end of the file, with the appropriate path to the script substituted.

```
@reboot sleep 15 && /home/USER/PATH_TO_SCRIPT/slack_ip_broadcast.sh
```
The 15 second delay is meant to give the device enough time to connect to the network. This was chosen fairly arbitrarily but has been working well for us.
