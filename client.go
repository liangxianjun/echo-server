//go:build ignore

package main

import (
	"fmt"
	"math/rand"
	"strconv"
	"time"

	"net"
)

func main() {
	for i := 0; i < 100; i++ {
		go func(i int) {
			conn, err := net.Dial("tcp", "127.0.0.1:14514")
			if err != nil {
				fmt.Println("dial failed", err)
				return
			}
			fmt.Println("dial success", conn)
			go func() {
				for {
					buffer := make([]byte, 512)
					n, err := conn.Read(buffer)
					if err != nil || n == 0 {
						fmt.Println("read buffer failed", err)
						break
					}
					fmt.Println("received:", string(buffer[0:n]))
				}
			}()

			for {
				_, err = conn.Write([]byte("i am client" + strconv.Itoa(i)))
				if err != nil {
					fmt.Println(err)
				}
				time.Sleep(time.Second * time.Duration(rand.Intn(10)+1))
			}
			// conn.Close()

		}(i)
	}
	for {
	}
}
