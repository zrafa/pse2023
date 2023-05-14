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
            xdotool keydown a
            ;;
        2)
            xdotool keydown d
            ;;
        3)
            xdotool key f
            xdotool keydown a
            ;;
        4)
            xdotool key f
            xdotool keydown d
            ;;
        5)
            xdotool keyup a
            xdotool keyup d
            xdotool key f
            ;;
        *)
            echo "invalid option received"
            ;;
        esac
    done
