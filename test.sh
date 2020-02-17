osascript -e 'tell app "Terminal" 
do script "cd /Users/gaefourn/42/circle3/Minishell && clear && ./Minishell"
end tell' > /dev/null
osascript -e 'tell app "Terminal" to activate' > /dev/null 
osascript -e 'tell application "Terminal" to set bounds of front window to {598, 153, 1778, 882}' > /dev/null
