package main

import (
	"fmt"
	"os"
	"os/exec"
	"time"
)

const device string = "/dev/ttyACM0"

func lectura() {

}

func main() {
	var valor_lectura []byte = make([]byte, 1)
	var valor byte
	var keypress int
	exec.Command("stty", "-F", "/dev/ttyACM0", "speed", "9600").Run()
	time.Sleep(5 * time.Second)
	// open input file
	fi, err := os.Open(device)
	if err != nil {
		panic(err)
	}
	exec.Command("xdotool", "keydown", "s").Run()
	for {
		if _, err := fi.Read(valor_lectura); err != nil {
			panic(err)
		}
		valor = valor_lectura[0]
		defer func() {
			if err := fi.Close(); err != nil {
				panic(err)
			}
		}()
		switch valor {
		case 48:
			if keypress != 0 {
				exec.Command("xdotool", "keyup", "a").Run()
				exec.Command("xdotool", "keyup", "d").Run()
				exec.Command("xdotool", "keyup", "f").Run()
				keypress = 0
			}
		case 49:
			if keypress != 1 {
				exec.Command("xdotool", "keyup", "d").Run()
				exec.Command("xdotool", "keyup", "f").Run()
				exec.Command("xdotool", "keydown", "a").Run()
				keypress = 1
			}
		case 50:
			if keypress != 2 {
				exec.Command("xdotool", "keyup", "a").Run()
				exec.Command("xdotool", "keyup", "f").Run()
				exec.Command("xdotool", "keydown", "d").Run()
				keypress = 2
			}
		case 51:
			if keypress != 3 {
				exec.Command("xdotool", "keyup", "d").Run()
				exec.Command("xdotool", "keydown", "a+f").Run()
				keypress = 3
			}
		case 52:
			if keypress != 4 {
				exec.Command("xdotool", "keyup", "a").Run()
				exec.Command("xdotool", "keydown", "d+f").Run()
				keypress = 4
			}
		case 53:
			if keypress != 5 {
				exec.Command("xdotool", "keyup", "a").Run()
				exec.Command("xdotool", "keyup", "d").Run()
				exec.Command("xdotool", "keydown", "f").Run()
				keypress = 5
			}
		default:
			fmt.Println("Invalid option")
		}
		time.Sleep(5 * time.Millisecond)
		// time.Sleep(100 * time.Millisecond)
	}
}
