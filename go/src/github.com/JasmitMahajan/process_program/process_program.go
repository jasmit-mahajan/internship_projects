package main

import (
	"fmt"
	"os/user"
	"io/ioutil"
	"log"
	"strconv"
	"syscall"
)

func main(){
	process("/proc/")
}

func process (dir_name string) string{
	files, err := ioutil.ReadDir(dir_name)

	if err != nil{
		log.Fatal(err)
	}

	for _, file := range files{

		i := 0
		i++
		var stat syscall.Stat_t
		var uid int
		syscall.Stat(dir_name + file.Name(), &stat)
		uid = int(stat.Uid)
		u, err_3 := user.LookupId(strconv.Itoa(uid))
		if err_3 != nil{
			log.Fatal(err_3)
		}
		var id int64
		id, err_2 := strconv.ParseInt(file.Name(), 10, 64)
		if err_2 == nil{
			fmt.Println("uid:", uid)
			fmt.Println("pid", id)
			fmt.Println("hostname:", u.Username)
//			fmt.Println("\n")
		}
	}
	return dir_name
}

