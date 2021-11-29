while true
do
date
display_system_usage | grep -e '----CPU' -e 'CPU Core'
sleep 60
done

