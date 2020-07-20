package main

import (
	"testing"
)

func TestProcess(t *testing.T){
	dir_name := process("/proc/")
	if dir_name == "/proc/"{
		t.Log("/proc/ is a directory name you can put into program")
	} else {
		t.Errorf("Received unexpected input: %s", dir_name)
	}
}


