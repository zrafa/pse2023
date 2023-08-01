stty -F /dev/ttyACM0 speed 9600
xdotool windowfocus OpenTyrian
cat /dev/ttyACM0 |
    while read tecla; do
        case $tecla in
        0)
            xdotool keyup a
            xdotool keyup d
            ;;
        1)
            xdotool key -d 0 a
            ;;
        2)
            xdotool key -d 0 d
            ;;
        3)
            xdotool key -d 0 "f+a"
            ;;
        4)
            xdotool key -d 0 "f+d"
            ;;
        5)
            xdotool key -d 0 "f"
            ;;
        *)
            echo "invalid option received"
            ;;
        esac
    done
